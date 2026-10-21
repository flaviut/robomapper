#define _GNU_SOURCE
#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define LIBDIR "/opt/rockrobo/cleaner/lib/"
#define NAME "map-maint"

enum peer { APP_PROXY = 3, WATCH_DOG = 7 };
enum status { READY = 0, REFUSED = 1 };

struct packet {
    uint32_t id;
    uint32_t seq;
    uint32_t size;
    char data[64];
};

_Static_assert(sizeof(struct packet) == 76, "vendor Packet_t must be 76 bytes");
_Static_assert(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__, "little-endian target required");
_Static_assert(sizeof(void *) == 4, "32-bit target required");

static int refuse(const char *reason)
{
    fprintf(stderr, "%s\n", reason);
    return REFUSED;
}

static void usage(void)
{
    puts("Usage: map-maint exclusions ORIGINAL_FILE CONTENT_FILE\n"
         "       map-maint mcu-disable\n"
         "       map-maint --help\n\n"
         "No operation is selected by default. Vendor libraries load only for an explicit operation.\n"
         "Preserve the current original exclusions independently before sending anything.\n"
         "CONTENT_FILE must preserve ORIGINAL_FILE byte-for-byte at the start, with new targets on new lines.\n"
         "Exclusion delivery can kill supervised hosts; it does not confirm their exit.\n"
         "mcu-disable requires the loader and all UART owners to be absent. It stops no services.\n"
         "Do not deploy or run either operation without the separate maintenance decision.");
}

static const char *base(const char *path)
{
    const char *slash = strrchr(path, '/');
    return slash ? slash + 1 : path;
}

/* DllInit derives its identity from /proc/self/cmdline, not our channel arguments. */
static int identity(void)
{
    char text[256] = {0};
    int fd = open("/proc/self/cmdline", O_RDONLY | O_CLOEXEC);
    ssize_t n;
    char *end;

    if (fd < 0)
        return refuse("Cannot read helper identity; no vendor library loaded.");
    n = read(fd, text, sizeof(text));
    close(fd);
    if (n <= 0 || !(end = memchr(text, '\0', (size_t)n)) ||
        strcmp(base(text), NAME) != 0 || strpbrk(text, " \t\r\n"))
        return refuse("Run under the unique map-maint name; no vendor library loaded.");
    /* Leave room for the vendor reader's fixed 256-byte first-argument buffer. */
    if (end - text > 200)
        return refuse("Helper launch path is too long for the vendor identity reader.");
    fd = open("/proc/self/comm", O_RDONLY | O_CLOEXEC);
    if (fd < 0)
        return refuse("Cannot read helper process name.");
    n = read(fd, text, sizeof(text) - 1);
    close(fd);
    if (n <= 0)
        return refuse("Cannot read helper process name.");
    text[n] = '\0';
    if (strcmp(text, NAME "\n") != 0)
        return refuse("Executable process name must be map-maint.");
    return READY;
}

static int read_content(const char *path, char text[64], size_t *len)
{
    struct stat st;
    int fd = open(path, O_RDONLY | O_NONBLOCK | O_NOFOLLOW | O_CLOEXEC);
    size_t used = 0;
    ssize_t n;

    if (fd < 0)
        return refuse("Cannot open exclusion input as a nonsymlink regular file.");
    if (fstat(fd, &st) < 0 || !S_ISREG(st.st_mode)) {
        close(fd);
        return refuse("Exclusion input must be a regular file.");
    }
    while (used < 64) {
        n = read(fd, text + used, 64 - used);
        if (n < 0 && errno == EINTR)
            continue;
        if (n < 0) {
            close(fd);
            return refuse("Cannot read exclusion input.");
        }
        if (n == 0)
            break;
        used += (size_t)n;
    }
    close(fd);
    if (used > 63 || memchr(text, '\0', used))
        return refuse("Exclusion input must contain at most 63 bytes and no NUL.");
    text[used] = '\0';
    *len = used;
    return READY;
}

static int content_ok(const char *text, size_t len)
{
    size_t start = 0;
    unsigned fields = 0;

    if (len <= 2)
        return refuse("Exclusion content must exceed two bytes; short content selects destructive event 9.");
    for (size_t i = 0; i <= len; ++i) {
        if (i < len && text[i] != ',' && text[i] != '\n')
            continue;
        if (i < len && text[i] == ',') {
            if (i == start)
                return refuse("Empty comma fields can exclude every process; refusing content.");
            if (++fields >= 3)
                return refuse("WatchDoge reads at most three fields per line; use new lines.");
        } else {
            if (fields && i == start)
                return refuse("Empty comma fields can exclude every process; refusing content.");
            if (i > start && i - start <= 3)
                return refuse("A final token on a line must exceed three bytes or WatchDoge ignores it.");
            fields = 0;
        }
        start = i + 1;
    }
    return READY;
}

static void *load(const char *path)
{
    void *lib = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    if (!lib)
        refuse("Cannot load the matching vendor library and dependencies.");
    return lib;
}

/* The private reverse descriptor is never read or registered in g_Channels. */
static int send_exclusions(const char *text, size_t len)
{
    struct packet msg = { .id = 0x07030342, .size = (uint32_t)len + 1 };
    struct sigaction action = { .sa_handler = SIG_IGN };
    void *lib;
    void *channel;
    void *(*open_channel)(enum peer, enum peer);
    ssize_t (*write_channel)(void *, void *, unsigned, int);
    void (*close_channel)(void *);
    uint32_t (*next_seq)(struct packet *);
    ssize_t sent;

    sigemptyset(&action.sa_mask);
    if (sigaction(SIGPIPE, &action, NULL) < 0)
        return refuse("Cannot ignore SIGPIPE; nothing sent.");
    lib = load(LIBDIR "libroboipc.so");
    if (!lib)
        return REFUSED;
    open_channel = (void *(*)(enum peer, enum peer))dlsym(lib, "_Z12pChannelOpen16ProcessAbbrIndexS_");
    write_channel = (ssize_t (*)(void *, void *, unsigned, int))dlsym(lib, "_Z13pChannelWritePvS_ji");
    close_channel = (void (*)(void *))dlsym(lib, "_Z13pChannelClosePv");
    next_seq = (uint32_t (*)(struct packet *))dlsym(lib, "_Z21GetNextSequenceNumberP8Packet_t");
    if (!open_channel || !write_channel || !close_channel || !next_seq) {
        dlclose(lib);
        return refuse("Matching IPC exports are unavailable; nothing sent.");
    }
    channel = open_channel(APP_PROXY, WATCH_DOG);
    if (!channel) {
        dlclose(lib);
        return refuse("Cannot open private exclusion channel; nothing sent.");
    }
    memcpy(msg.data, text, len);
    next_seq(&msg);
    sent = write_channel(channel, &msg, 76, 0x800);
    close_channel(channel);
    dlclose(lib);
    if (sent != 76)
        return refuse("Exclusion write was not exactly 76 bytes. Do not retry blindly or assume hosts stopped.");
    puts("Exclusion packet written. This does not acknowledge event handling, host exit or storage flush.");
    return READY;
}

static int number(const char *s)
{
    if (!*s)
        return 0;
    for (; *s; ++s)
        if (*s < '0' || *s > '9')
            return 0;
    return 1;
}

static int loader_absent(int proc)
{
    char text[512];
    ssize_t n = readlinkat(proc, "exe", text, sizeof(text) - 1);
    int fd;

    if (n >= (ssize_t)sizeof(text) - 1)
        return refuse("Cannot identify a process executable completely.");
    if (n >= 0) {
        text[n] = '\0';
        if (!strcmp(base(text), "rr_loader") || !strcmp(base(text), "rr_loader (deleted)"))
            return refuse("Loader still exists; MCU disable refused.");
    } else if (errno != ENOENT && errno != ESRCH) {
        return refuse("Cannot inspect a process executable; MCU disable refused.");
    }
    fd = openat(proc, "comm", O_RDONLY | O_CLOEXEC);
    if (fd < 0) {
        if (errno == ENOENT || errno == ESRCH)
            return READY;
        return refuse("Cannot inspect a process name; MCU disable refused.");
    }
    n = read(fd, text, sizeof(text) - 1);
    close(fd);
    if (n <= 0)
        return refuse("Cannot read a process name; MCU disable refused.");
    text[n] = '\0';
    if (!strcmp(text, "rr_loader\n"))
        return refuse("Loader still exists; MCU disable refused.");
    return READY;
}

static int uart_absent(int proc, const struct stat nodes[2])
{
    int fd = openat(proc, "fd", O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    DIR *fds;
    struct dirent *entry;
    struct stat st;
    int result = READY;

    if (fd < 0) {
        if (errno == ENOENT || errno == ESRCH)
            return READY;
        return refuse("Cannot inspect process descriptors; MCU disable refused.");
    }
    fds = fdopendir(fd);
    if (!fds) {
        close(fd);
        return refuse("Cannot inspect process descriptors; MCU disable refused.");
    }
    for (;;) {
        errno = 0;
        entry = readdir(fds);
        if (!entry) {
            if (errno)
                result = refuse("Incomplete descriptor scan; MCU disable refused.");
            break;
        }
        if (!number(entry->d_name))
            continue;
        if (fstatat(fd, entry->d_name, &st, 0) < 0) {
            if (errno == ENOENT || errno == ESRCH)
                continue;
            result = refuse("Cannot identify a descriptor; MCU disable refused.");
            break;
        }
        if (S_ISCHR(st.st_mode) && (st.st_rdev == nodes[0].st_rdev || st.st_rdev == nodes[1].st_rdev)) {
            result = refuse("An existing descriptor owns the MCU UART; MCU disable refused.");
            break;
        }
    }
    closedir(fds);
    return result;
}

/* Metadata only: no UART open, ioctl or packet send belongs in this check. */
static int owners_absent(void)
{
    struct stat nodes[2];
    DIR *procs;
    struct dirent *entry;
    int proc;
    int result = READY;

    if (stat("/dev/ttyS2", &nodes[0]) < 0 || stat("/dev/uart_mcu", &nodes[1]) < 0 ||
        !S_ISCHR(nodes[0].st_mode) || !S_ISCHR(nodes[1].st_mode))
        return refuse("Expected UART device metadata is unavailable; MCU disable refused.");
    procs = opendir("/proc");
    if (!procs)
        return refuse("Cannot inspect process ownership; MCU disable refused.");
    for (;;) {
        errno = 0;
        entry = readdir(procs);
        if (!entry) {
            if (errno)
                result = refuse("Incomplete process scan; MCU disable refused.");
            break;
        }
        if (!number(entry->d_name))
            continue;
        proc = openat(dirfd(procs), entry->d_name, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
        if (proc < 0) {
            if (errno == ENOENT || errno == ESRCH)
                continue;
            result = refuse("Cannot inspect a process; MCU disable refused.");
            break;
        }
        result = loader_absent(proc);
        if (result == READY)
            result = uart_absent(proc, nodes);
        close(proc);
        if (result != READY)
            break;
    }
    closedir(procs);
    return result;
}

static int disable_mcu(void)
{
    void *lib;
    int (*heartbeat)(int);
    int result;

    if (owners_absent() != READY)
        return REFUSED;
    lib = load(LIBDIR "libuart_api.so.4.0.2");
    if (!lib)
        return REFUSED;
    heartbeat = (int (*)(int))dlsym(lib, "rua_keep_mcu_heartbeat");
    if (!heartbeat) {
        dlclose(lib);
        return refuse("Matching heartbeat export is unavailable; no request made.");
    }
    /* Recheck after loading; the native API's nonblocking lock is the final ownership check. */
    if (owners_absent() != READY) {
        dlclose(lib);
        return REFUSED;
    }
    result = heartbeat(-1);
    dlclose(lib);
    if (result != 0) {
        fprintf(stderr, "MCU disable init/ack failed (result %d). Do not start file maintenance.\n", result);
        return REFUSED;
    }
    puts("MCU disable acknowledged. Keep the loader absent; normal chassis startup replaces this request.");
    return READY;
}

int main(int argc, char **argv)
{
    char original[64], text[64];
    size_t old_len, len;

    if (argc == 1 || (argc == 2 && !strcmp(argv[1], "--help"))) {
        usage();
        return argc == 1 ? REFUSED : READY;
    }
    if (!((argc == 2 && !strcmp(argv[1], "mcu-disable")) ||
          (argc == 4 && !strcmp(argv[1], "exclusions")))) {
        usage();
        return REFUSED;
    }
    if (geteuid() != 0)
        return refuse("Explicit maintenance operations require root for complete process visibility.");
    if (identity() != READY)
        return REFUSED;
    if (!strcmp(argv[1], "mcu-disable"))
        return disable_mcu();
    if (read_content(argv[2], original, &old_len) != READY ||
        read_content(argv[3], text, &len) != READY || content_ok(text, len) != READY)
        return REFUSED;
    if (old_len > len || memcmp(original, text, old_len) ||
        (old_len && old_len < len && original[old_len - 1] != '\n' && text[old_len] != '\n'))
        return refuse("Preserve original exclusions byte-for-byte; append targets on new lines. Nothing sent.");
    fputs("Preserve the independent original exclusion copy. Sending event 8 may kill tracked hosts.\n", stderr);
    return send_exclusions(text, len);
}
