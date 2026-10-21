//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/shared/utils.js
var e = Array.isArray, t = Array.prototype.indexOf, n = Array.prototype.includes, r = Array.from, i = Object.defineProperty, a = Object.getOwnPropertyDescriptor, o = Object.getOwnPropertyDescriptors, s = Object.prototype, c = Array.prototype, l = Object.getPrototypeOf, u = Object.isExtensible, d = () => {};
function f(e) {
	for (var t = 0; t < e.length; t++) e[t]();
}
function p() {
	var e, t;
	return {
		promise: new Promise((n, r) => {
			e = n, t = r;
		}),
		resolve: e,
		reject: t
	};
}
var m = 1024, h = 2048, g = 4096, _ = 8192, v = 16384, y = 32768, b = 1 << 25, x = 65536, S = 1 << 19, ee = 1 << 20, te = 1 << 25, C = 1 << 21, ne = 1 << 22, re = 1 << 23, w = Symbol("$state"), ie = Symbol("component"), ae = Symbol(""), oe = Symbol("attributes"), se = Symbol("class"), ce = Symbol("style"), le = Symbol("text"), ue = Symbol("form reset"), de = new class extends Error {
	name = "StaleReactionError";
	message = "The reaction that called `getAbortSignal()` was re-run or destroyed";
}(), fe = !!globalThis.document?.contentType && /* @__PURE__ */ globalThis.document.contentType.includes("xml"), T = {}, E = Symbol("uninitialized"), pe = "http://www.w3.org/1999/xhtml";
function me() {
	console.warn("https://svelte.dev/e/derived_inert");
}
function he(e) {
	console.warn("https://svelte.dev/e/hydration_mismatch");
}
function ge() {
	console.warn("https://svelte.dev/e/select_multiple_invalid_value");
}
function _e() {
	console.warn("https://svelte.dev/e/svelte_boundary_reset_noop");
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/hydration.js
var D = !1;
function ve(e) {
	D = e;
}
var O;
function k(e) {
	if (e === null) throw he(), T;
	return O = e;
}
function ye() {
	return k(/* @__PURE__ */ Xt(O));
}
function A(e) {
	if (D) {
		if (/* @__PURE__ */ Xt(O) !== null) throw he(), T;
		O = e;
	}
}
function j(e = 1) {
	if (D) {
		for (var t = e, n = O; t--;) n = /* @__PURE__ */ Xt(n);
		O = n;
	}
}
function be(e = !0) {
	for (var t = 0, n = O;;) {
		if (n.nodeType === 8) {
			var r = n.data;
			if (r === "]") {
				if (t === 0) return n;
				--t;
			} else (r === "[" || r === "[!" || r[0] === "[" && !isNaN(Number(r.slice(1)))) && (t += 1);
		}
		var i = /* @__PURE__ */ Xt(n);
		e && n.remove(), n = i;
	}
}
function xe(e) {
	if (!e || e.nodeType !== 8) throw he(), T;
	return e.data;
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/reactivity/equality.js
function Se(e) {
	return e === this.v;
}
function Ce(e, t) {
	return e == e ? e !== t || typeof e == "object" && !!e || typeof e == "function" : t == t;
}
function we(e) {
	return !Ce(e, this.v);
}
function Te(e) {
	throw Error("https://svelte.dev/e/lifecycle_outside_component");
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/errors.js
function Ee() {
	throw Error("https://svelte.dev/e/async_derived_orphan");
}
function De(e, t, n) {
	throw Error("https://svelte.dev/e/each_key_duplicate");
}
function Oe(e) {
	throw Error("https://svelte.dev/e/effect_in_teardown");
}
function ke() {
	throw Error("https://svelte.dev/e/effect_in_unowned_derived");
}
function Ae(e) {
	throw Error("https://svelte.dev/e/effect_orphan");
}
function je() {
	throw Error("https://svelte.dev/e/effect_update_depth_exceeded");
}
function Me() {
	throw Error("https://svelte.dev/e/state_descriptors_fixed");
}
function Ne() {
	throw Error("https://svelte.dev/e/state_prototype_fixed");
}
function Pe() {
	throw Error("https://svelte.dev/e/state_unsafe_mutation");
}
function Fe() {
	throw Error("https://svelte.dev/e/svelte_boundary_reset_onerror");
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/context.js
var M = null;
function Ie(e) {
	M = e;
}
function Le(e, t = !1, n) {
	M = {
		p: M,
		i: !1,
		c: null,
		e: null,
		s: e,
		x: null,
		r: K,
		l: null
	};
}
function Re(e) {
	var t = M, n = t.e;
	if (n !== null) {
		t.e = null;
		for (var r of n) fn(r);
	}
	return e !== void 0 && (t.x = e), t.i = !0, M = t.p, ze(e);
}
function ze(e = {}) {
	return i(e, ie, { value: !0 }), e;
}
function Be() {
	return !0;
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/task.js
var Ve = [];
function He() {
	var e = Ve;
	Ve = [], f(e);
}
function N(e) {
	if (Ve.length === 0 && !ht) {
		var t = Ve;
		queueMicrotask(() => {
			t === Ve && He();
		});
	}
	Ve.push(e);
}
function Ue() {
	for (; Ve.length > 0;) He();
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/reactivity/status.js
var We = ~(h | g | m);
function P(e, t) {
	e.f = e.f & We | t;
}
function Ge(e) {
	e.f & 512 || e.deps === null ? P(e, m) : P(e, g);
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/reactivity/utils.js
function Ke(e, t, n) {
	e.f & 2048 ? t.add(e) : e.f & 4096 && n.add(e), P(e, m);
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/elements/misc.js
var qe = !1;
function Je() {
	qe || (qe = !0, document.addEventListener("reset", (e) => {
		Promise.resolve().then(() => {
			if (!e.defaultPrevented) for (let t of e.target.elements) t[ue]?.();
		});
	}, { capture: !0 }));
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/elements/bindings/shared.js
function Ye(e) {
	var t = W, n = K;
	G(null), Mn(null);
	try {
		return e();
	} finally {
		G(t), Mn(n);
	}
}
function Xe(e, t, n, r = n) {
	e.addEventListener(t, () => Ye(n));
	let i = e[ue];
	e[ue] = i ? () => {
		i(), r(!0);
	} : () => r(!0), Je();
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/reactivity/async.js
function Ze(e, t, n, r) {
	let i = Be() ? tt : at;
	var a = e.filter((e) => !e.settled), o = t.map(i);
	if (n.length === 0 && a.length === 0) {
		r(o);
		return;
	}
	var s = K, c = Qe(), l = a.length === 1 ? a[0].promise : a.length > 1 ? Promise.all(a.map((e) => e.promise)) : null;
	function u(e) {
		if (!(s.f & 16384)) {
			c();
			try {
				r([...o, ...e]);
			} catch (e) {
				an(e, s);
			}
			$e();
		}
	}
	var d = et();
	if (n.length === 0) {
		l.then(() => u([])).finally(d);
		return;
	}
	function f() {
		Promise.all(n.map((e) => /* @__PURE__ */ rt(e))).then(u).catch((e) => an(e, s)).finally(d);
	}
	l ? l.then(() => {
		s.f & 16384 ? d() : (c(), f(), $e());
	}) : f();
}
function Qe() {
	var e = K, t = W, n = M, r = F;
	return function(i = !0) {
		Mn(e), G(t), Ie(n), i && !(e.f & 16384) && (r?.activate(), r?.apply());
	};
}
function $e(e = !0) {
	Mn(null), G(null), Ie(null), e && F?.deactivate();
}
function et() {
	var e = K, t = e.b, n = F, r = !!t?.is_rendered();
	return t?.update_pending_count(1, n), n.increment(r, e), () => {
		t?.update_pending_count(-1, n), n.decrement(r, e);
	};
}
/*#__NO_SIDE_EFFECTS__*/
function tt(e) {
	var t = 2 | h;
	return K !== null && (K.f |= S), {
		ctx: M,
		deps: null,
		effects: null,
		equals: Se,
		f: t,
		fn: e,
		reactions: null,
		rv: 0,
		v: E,
		wv: 0,
		parent: K,
		ac: null
	};
}
var nt = Symbol("obsolete");
/*#__NO_SIDE_EFFECTS__*/
function rt(e, t, n) {
	let r = K;
	r === null && Ee();
	var i = void 0, a = Mt(E), o = !W, s = /* @__PURE__ */ new Set();
	return hn(() => {
		var t = K, n = p();
		i = n.promise;
		try {
			Promise.resolve(e()).then(n.resolve, (e) => {
				e !== de && n.reject(e);
			}).finally($e);
		} catch (e) {
			n.reject(e), $e();
		}
		var c = F;
		if (o) {
			if (t.f & 32768) var l = et();
			if (r.b?.is_rendered()) c.async_deriveds.get(t)?.reject(nt);
			else for (let e of s.values()) e.reject(nt);
			s.add(n), c.async_deriveds.set(t, n);
		}
		let u = (e, t = void 0) => {
			l?.(), s.delete(n), t !== nt && (c.activate(), t ? (a.f |= re, It(a, t)) : (a.f & 8388608 && (a.f ^= re), It(a, e)), c.deactivate());
		};
		n.promise.then(u, (e) => u(null, e || "unknown"));
	}), un(() => {
		for (let e of s) e.reject(nt);
	}), new Promise((e) => {
		function t(n) {
			function r() {
				n === i ? e(a) : t(i);
			}
			n.then(r, r);
		}
		t(i);
	});
}
/*#__NO_SIDE_EFFECTS__*/
function it(e) {
	let t = /* @__PURE__ */ tt(e);
	return Pn(t), t;
}
/*#__NO_SIDE_EFFECTS__*/
function at(e) {
	let t = /* @__PURE__ */ tt(e);
	return t.equals = we, t;
}
function ot(e) {
	var t = e.effects;
	if (t !== null) {
		e.effects = null;
		for (var n = 0; n < t.length; n += 1) U(t[n]);
	}
}
function st(e) {
	var t, n = K, r = e.parent;
	if (!kn && r !== null && e.v !== E && r.f & 24576) return me(), e.v;
	Mn(r);
	try {
		ot(e), t = Un(e);
	} finally {
		Mn(n);
	}
	return t;
}
function ct(e) {
	var t = st(e);
	!e.equals(t) && (e.wv = Bn(), (!F?.is_fork || e.deps === null) && (F === null ? e.v = t : (F.capture(e, t, !0), ft?.capture(e, t, !0)), e.deps === null)) ? P(e, m) : kn || (pt === null ? Ge(e) : (ln() || F?.is_fork) && pt.set(e, t));
}
function lt(e) {
	if (e.effects !== null) for (let t of e.effects) (t.teardown || t.ac) && (t.teardown?.(), t.ac !== null && Ye(() => {
		t.ac.abort(de), t.ac = null;
	}), t.fn !== null && (t.teardown = d), Kn(t, 0), yn(t));
}
function ut(e) {
	if (e.effects !== null) for (let t of e.effects) t.teardown && t.fn !== null && qn(t);
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/reactivity/batch.js
var dt = null, F = null, ft = null, pt = null, mt = null, ht = !1, gt = !1, _t = null, vt = null, yt = 0, bt = 1, xt = class e {
	id = bt++;
	#e = !1;
	linked = !0;
	#t = null;
	#n = null;
	async_deriveds = /* @__PURE__ */ new Map();
	current = /* @__PURE__ */ new Map();
	previous = /* @__PURE__ */ new Map();
	#r = /* @__PURE__ */ new Set();
	#i = /* @__PURE__ */ new Set();
	#a = 0;
	#o = /* @__PURE__ */ new Map();
	#s = null;
	#c = [];
	#l = [];
	#u = /* @__PURE__ */ new Set();
	#d = /* @__PURE__ */ new Set();
	#f = /* @__PURE__ */ new Map();
	#p = /* @__PURE__ */ new Set();
	is_fork = !1;
	#m = !1;
	constructor() {
		dt === null ? dt = this : (dt.#n = this, this.#t = dt), dt = this;
	}
	#h() {
		if (this.is_fork) return !0;
		for (let n of this.#o.keys()) {
			for (var e = n, t = !1; e.parent !== null;) {
				if (this.#f.has(e)) {
					t = !0;
					break;
				}
				e = e.parent;
			}
			if (!t) return !0;
		}
		return !1;
	}
	skip_effect(e) {
		this.#f.has(e) || this.#f.set(e, {
			d: [],
			m: []
		}), this.#p.delete(e);
	}
	unskip_effect(e, t = (e) => this.schedule(e)) {
		var n = this.#f.get(e);
		if (n) {
			this.#f.delete(e);
			for (var r of n.d) P(r, h), t(r);
			for (r of n.m) P(r, g), t(r);
		}
		this.#p.add(e);
	}
	#g() {
		var e = [];
		for (let i of this.#c) if (!(i.f & 16384 || !(i.f & 6144))) {
			for (var t = i, n = !1; t.parent !== null;) {
				t = t.parent;
				var r = t.f;
				if (r & 96) {
					if (!(r & 1024)) {
						n = !0;
						break;
					}
					t.f ^= m;
				}
			}
			n || e.push(t);
		}
		return this.#c = [], e;
	}
	#_() {
		this.#e = !0;
		for (let e of this.#u) this.#d.delete(e), P(e, h), this.schedule(e);
		for (let e of this.#d) P(e, g), this.schedule(e);
		this.apply();
		for (var t = _t = [], n = [], r = vt = []; this.#c.length > 0;) {
			yt++ > 1e3 && (this.#S(), Ct());
			for (let e of this.#g()) try {
				this.#v(e, t, n);
			} catch (t) {
				throw Ot(e), this.#h() || this.discard(), t;
			}
		}
		if (F = null, r.length > 0) {
			var i = e.ensure();
			for (let e of r) i.schedule(e);
		}
		if (_t = null, vt = null, this.#h()) {
			this.#x(n), this.#x(t);
			for (let [e, t] of this.#f) Dt(e, t);
			r.length > 0 && F.#_();
			return;
		}
		let a = this.#y();
		if (a) this.#x(n), this.#x(t), a.#b(this);
		else {
			this.#u.clear(), this.#d.clear();
			for (let e of this.#r) e(this);
			this.#r.clear(), ft = this, Tt(n), Tt(t), ft = null, this.#s?.resolve();
			var o = F;
			if (this.#a === 0 && (this.#c.length === 0 || o !== null) && this.#S(), this.#c.length > 0) {
				if (o !== null) {
					for (let e of this.#c) o.#c.push(e);
					this.#c = [];
				} else o = this;
			}
			o !== null && (At.clear(), o.#_());
		}
	}
	#v(e, t, n) {
		e.f ^= m;
		for (var r = e.first; r !== null;) {
			var i = r.f, a = !!(i & 96);
			if (!(a && i & 1024 || i & 8192 || this.#f.has(r)) && r.fn !== null) {
				a ? r.f ^= m : i & 4 ? t.push(r) : Vn(r) && (i & 16 && this.#d.add(r), qn(r));
				var o = r.first;
				if (o !== null) {
					r = o;
					continue;
				}
			}
			for (; r !== null;) {
				var s = r.next;
				if (s !== null) {
					r = s;
					break;
				}
				r = r.parent;
			}
		}
	}
	#y() {
		for (var e = this.#t; e !== null;) {
			if (!e.is_fork) {
				for (let [t, [, n]] of this.current) if (e.current.has(t) && !n) return e;
			}
			e = e.#t;
		}
		return null;
	}
	#b(e) {
		for (let [t, n] of e.current) !this.previous.has(t) && e.previous.has(t) && this.previous.set(t, e.previous.get(t)), this.current.set(t, n);
		for (let [t, n] of e.async_deriveds) {
			let e = this.async_deriveds.get(t);
			e && n.promise.then(e.resolve).catch(e.reject);
		}
		e.async_deriveds.clear(), this.transfer_effects(e.#u, e.#d);
		let t = (e) => {
			var n = e.reactions;
			if (n !== null && !(e.f & 2 && !(e.f & 6144))) for (let e of n) {
				var r = e.f;
				if (r & 2) t(e);
				else {
					var i = e;
					r & 4194320 && !this.async_deriveds.has(i) && (this.#d.delete(i), P(i, h), this.schedule(i));
				}
			}
		};
		for (let e of this.current.keys()) t(e);
		this.oncommit(() => e.discard()), e.#S(), F = this, this.#_();
	}
	#x(e) {
		for (var t = 0; t < e.length; t += 1) Ke(e[t], this.#u, this.#d);
	}
	capture(e, t, n = !1) {
		e.v !== E && !this.previous.has(e) && this.previous.set(e, e.v), e.f & 8388608 || (this.current.set(e, [t, n]), pt?.set(e, t)), this.is_fork || (e.v = t);
	}
	activate() {
		F = this;
	}
	deactivate() {
		F = null, pt = null;
	}
	flush() {
		try {
			gt = !0, F = this, this.#_();
		} finally {
			yt = 0, mt = null, _t = null, vt = null, gt = !1, F = null, pt = null, At.clear();
		}
	}
	discard() {
		for (let e of this.#i) e(this);
		this.#i.clear();
		for (let e of this.async_deriveds.values()) e.reject(nt);
		this.#S(), this.#s?.resolve();
	}
	register_created_effect(e) {
		this.#l.push(e);
	}
	increment(e, t) {
		if (this.#a += 1, e) {
			let e = this.#o.get(t) ?? 0;
			this.#o.set(t, e + 1);
		}
	}
	decrement(e, t) {
		if (--this.#a, e) {
			let e = this.#o.get(t) ?? 0;
			e === 1 ? this.#o.delete(t) : this.#o.set(t, e - 1);
		}
		this.#m || (this.#m = !0, N(() => {
			this.#m = !1, this.linked && this.flush();
		}));
	}
	transfer_effects(e, t) {
		for (let t of e) this.#u.add(t);
		for (let e of t) this.#d.add(e);
		e.clear(), t.clear();
	}
	oncommit(e) {
		this.#r.add(e);
	}
	ondiscard(e) {
		this.#i.add(e);
	}
	settled() {
		return (this.#s ??= p()).promise;
	}
	static ensure() {
		if (F === null) {
			let t = F = new e();
			!gt && !ht && N(() => {
				t.#e || t.flush();
			});
		}
		return F;
	}
	apply() {
		pt = null;
	}
	schedule(e) {
		mt = e, e.b?.is_pending && e.f & 16777228 && !(e.f & 32768) ? e.b.defer_effect(e) : this.#c.push(e);
	}
	#S() {
		if (this.linked) {
			var e = this.#t, t = this.#n;
			e === null || (e.#n = t), t === null ? dt = e : t.#t = e, this.linked = !1;
		}
	}
};
function St(e) {
	var t = ht, n = ft;
	ft = null, ht = !0;
	try {
		var r;
		for (e && (St(), r = e());;) {
			if (Ue(), F === null) return r;
			F.flush();
		}
	} finally {
		ht = t, ft = n;
	}
}
function Ct() {
	try {
		je();
	} catch (e) {
		an(e, mt);
	}
}
var wt = null;
function Tt(e) {
	var t = e.length;
	if (t !== 0) {
		for (var n = 0; n < t;) {
			var r = e[n++];
			if (!(r.f & 24576) && Vn(r) && (wt = /* @__PURE__ */ new Set(), qn(r), r.deps === null && r.first === null && r.nodes === null && r.teardown === null && r.ac === null && Sn(r), wt?.size > 0)) {
				At.clear();
				for (let e of wt) {
					if (e.f & 24576) continue;
					let t = [e], n = e.parent;
					for (; n !== null;) wt.has(n) && (wt.delete(n), t.push(n)), n = n.parent;
					for (let e = t.length - 1; e >= 0; e--) {
						let n = t[e];
						n.f & 24576 || qn(n);
					}
				}
				wt.clear();
			}
		}
		wt = null;
	}
}
function Et(e) {
	F.schedule(e);
}
function Dt(e, t) {
	if (!(e.f & 32 && e.f & 1024)) {
		e.f & 2048 ? t.d.push(e) : e.f & 4096 && t.m.push(e), P(e, m);
		for (var n = e.first; n !== null;) Dt(n, t), n = n.next;
	}
}
function Ot(e) {
	P(e, m);
	for (var t = e.first; t !== null;) Ot(t), t = t.next;
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/reactivity/sources.js
var kt = /* @__PURE__ */ new Set(), At = /* @__PURE__ */ new Map(), jt = !1;
function Mt(e, t) {
	return {
		f: 0,
		v: e,
		reactions: null,
		equals: Se,
		rv: 0,
		wv: 0
	};
}
/*#__NO_SIDE_EFFECTS__*/
function I(e, t) {
	let n = Mt(e, t);
	return Pn(n), n;
}
/*#__NO_SIDE_EFFECTS__*/
function Nt(e, t = !1, n = !0) {
	let r = Mt(e);
	return t || (r.equals = we), r;
}
function L(e, t, n = !1) {
	return W !== null && (!jn || W.f & 131072) && Be() && W.f & 4325394 && (Nn === null || !Nn.has(e)) && Pe(), It(e, n ? Vt(t) : t, vt);
}
var Pt = null, Ft = 0;
function It(e, t, n = null) {
	if (!e.equals(t)) {
		kn ? At.set(e, t) : At.has(e) || At.set(e, e.v);
		var r = xt.ensure();
		if (r.capture(e, t), e.f & 2) {
			let t = e;
			e.f & 2048 && st(t), pt === null && Ge(t);
		}
		e.wv = Bn(), Pt = null, Ft = 0, Bt(e, h, n), Pt = null, Be() && K !== null && K.f & 1024 && !(K.f & 96) && (Y === null ? Fn([e]) : Y.push(e)), !r.is_fork && kt.size > 0 && !jt && Lt();
	}
	return t;
}
function Lt() {
	jt = !1;
	for (let e of kt) {
		e.f & 1024 && P(e, g);
		let t;
		try {
			t = Vn(e);
		} catch {
			t = !0;
		}
		t && qn(e);
	}
	kt.clear();
}
function Rt(e, t = 1) {
	var n = X(e), r = t === 1 ? n++ : n--;
	return L(e, n), r;
}
function zt(e) {
	L(e, e.v + 1);
}
function Bt(e, t, n) {
	var r = e.reactions;
	if (r !== null) {
		var i = Be(), a = r.length;
		if (Ft += a, Ft > 1e5 && Pt === null && (Pt = /* @__PURE__ */ new Set()), Pt !== null) {
			if (Pt.has(e)) return;
			Pt.add(e);
		}
		for (var o = 0; o < a; o++) {
			var s = r[o], c = s.f;
			if (i || s !== K) {
				var l = (c & h) === 0;
				if (l && P(s, t), c & 131072) kt.add(s);
				else if (c & 2) {
					var u = s;
					pt?.delete(u), Bt(u, g, n);
				} else if (l) {
					var d = s;
					c & 16 && wt !== null && wt.add(d), n === null ? Et(d) : n.push(d);
				}
			}
		}
	}
}
function Vt(t) {
	if (typeof t != "object" || !t || w in t || ie in t) return t;
	let n = l(t);
	if (n !== s && n !== c) return t;
	var r = /* @__PURE__ */ new Map(), i = e(t), o = /* @__PURE__ */ I(0), u = null, d = Rn, f = (e) => {
		if (Rn === d) return e();
		var t = W, n = Rn;
		G(null), zn(d);
		var r = e();
		return G(t), zn(n), r;
	};
	return i && r.set("length", /* @__PURE__ */ I(t.length, u)), new Proxy(t, {
		defineProperty(e, t, n) {
			(!("value" in n) || n.configurable === !1 || n.enumerable === !1 || n.writable === !1) && Me();
			var i = r.get(t);
			return i === void 0 ? f(() => {
				var e = /* @__PURE__ */ I(n.value, u);
				return r.set(t, e), e;
			}) : L(i, n.value, !0), !0;
		},
		deleteProperty(e, t) {
			var n = r.get(t);
			if (n === void 0) {
				if (t in e) {
					let e = f(() => /* @__PURE__ */ I(E, u));
					r.set(t, e), zt(o);
				}
			} else L(n, E), zt(o);
			return !0;
		},
		get(e, n, i) {
			if (n === w) return t;
			var o = r.get(n), s = n in e;
			if (o === void 0 && (!s || a(e, n)?.writable) && (o = f(() => /* @__PURE__ */ I(Vt(s ? e[n] : E), u)), r.set(n, o)), o !== void 0) {
				var c = X(o);
				return c === E ? void 0 : c;
			}
			return Reflect.get(e, n, i);
		},
		getOwnPropertyDescriptor(e, t) {
			this.has?.(e, t);
			var n = Reflect.getOwnPropertyDescriptor(e, t), i = r.get(t);
			if (i !== void 0) {
				var a = X(i);
				if (a === E) return;
				if (n && "value" in n) n.value = a;
				else return {
					enumerable: !0,
					configurable: !0,
					value: a,
					writable: !0
				};
			}
			return n;
		},
		has(e, t) {
			if (t === w) return !0;
			var n = r.get(t), i = n !== void 0 && n.v !== E || Reflect.has(e, t);
			return (n !== void 0 || K !== null && (!i || a(e, t)?.writable)) && (n === void 0 && (n = f(() => /* @__PURE__ */ I(i ? Vt(e[t]) : E, u)), r.set(t, n)), X(n) === E) ? !1 : i;
		},
		set(e, t, n, s) {
			var c = r.get(t), l = t in e;
			if (i && t === "length") for (var d = n; d < c.v; d += 1) {
				var p = r.get(d + "");
				p === void 0 ? d in e && (p = f(() => /* @__PURE__ */ I(E, u)), r.set(d + "", p)) : L(p, E);
			}
			if (c === void 0) (!l || a(e, t)?.writable) && (c = f(() => /* @__PURE__ */ I(void 0, u)), L(c, Vt(n)), r.set(t, c));
			else {
				l = c.v !== E;
				var m = f(() => Vt(n));
				L(c, m);
			}
			var h = Reflect.getOwnPropertyDescriptor(e, t);
			if (h?.set && h.set.call(s, n), !l) {
				if (i && typeof t == "string") {
					var g = r.get("length"), _ = Number(t);
					Number.isInteger(_) && _ >= g.v && L(g, _ + 1);
				}
				zt(o);
			}
			return !0;
		},
		ownKeys(e) {
			X(o);
			var t = Reflect.ownKeys(e).filter((e) => {
				var t = r.get(e);
				return t === void 0 || t.v !== E;
			});
			for (var [n, i] of r) i.v !== E && !(n in e) && t.push(n);
			return t;
		},
		setPrototypeOf() {
			Ne();
		}
	});
}
function Ht(e) {
	try {
		if (typeof e == "object" && e && w in e) return e[w];
	} catch {}
	return e;
}
function Ut(e, t) {
	return Object.is(Ht(e), Ht(t));
}
var Wt, Gt, Kt, qt;
function Jt() {
	if (Wt === void 0) {
		Wt = window, Gt = /Firefox/.test(navigator.userAgent);
		var e = Element.prototype, t = Node.prototype, n = Text.prototype;
		Kt = a(t, "firstChild").get, qt = a(t, "nextSibling").get, u(e) && (e[se] = void 0, e[oe] = null, e[ce] = void 0, e.__e = void 0), u(n) && (n[le] = void 0);
	}
}
function R(e = "") {
	return document.createTextNode(e);
}
/*@__NO_SIDE_EFFECTS__*/
function Yt(e) {
	return Kt.call(e);
}
/*@__NO_SIDE_EFFECTS__*/
function Xt(e) {
	return qt.call(e);
}
function z(e, t) {
	if (!D) return /* @__PURE__ */ Yt(e);
	var n = /* @__PURE__ */ Yt(O);
	if (n === null) n = O.appendChild(R());
	else if (t && n.nodeType !== 3) {
		var r = R();
		return n?.before(r), k(r), r;
	}
	return t && nn(n), k(n), n;
}
function Zt(e, t = !1) {
	if (!D) {
		var n = /* @__PURE__ */ Yt(e);
		return n instanceof Comment && n.data === "" ? /* @__PURE__ */ Xt(n) : n;
	}
	if (t) {
		if (O?.nodeType !== 3) {
			var r = R();
			return O?.before(r), k(r), r;
		}
		nn(O);
	}
	return O;
}
function Qt(e, t = !1) {
	if (!D) return /* @__PURE__ */ Yt(e);
	var n = z(e, t);
	return A(e), n;
}
function B(e, t = 1, n = !1) {
	let r = D ? O : e;
	for (var i; t--;) i = r, r = /* @__PURE__ */ Xt(r);
	if (!D) return r;
	if (n) {
		if (r?.nodeType !== 3) {
			var a = R();
			return r === null ? i?.after(a) : r.before(a), k(a), a;
		}
		nn(r);
	}
	return k(r), r;
}
function $t(e) {
	e.textContent = "";
}
function en() {
	return !1;
}
function tn(e, t, n) {
	return t == null || t === "http://www.w3.org/1999/xhtml" ? n ? document.createElement(e, { is: n }) : document.createElement(e) : n ? document.createElementNS(t, e, { is: n }) : document.createElementNS(t, e);
}
function nn(e) {
	if (e.nodeValue.length < 65536) return;
	let t = e.nextSibling;
	for (; t !== null && t.nodeType === 3;) t.remove(), e.nodeValue += t.nodeValue, t = e.nextSibling;
}
function rn(e) {
	var t = K;
	if (t === null) return W.f |= re, e;
	if (!(t.f & 32768) && !(t.f & 4)) throw e;
	an(e, t);
}
function an(e, t) {
	if (e === T) throw e;
	if (!(t !== null && t.f & 16384)) {
		for (; t !== null;) {
			if (t.f & 128 && !(t.f & 33570816)) {
				if (!(t.f & 32768)) throw e;
				try {
					t.b.error(e);
					return;
				} catch (t) {
					e = t;
				}
			}
			t = t.parent;
		}
		throw e;
	}
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/reactivity/effects.js
function on(e) {
	K === null && (W === null && Ae(e), ke()), kn && Oe(e);
}
function sn(e, t) {
	var n = t.last;
	n === null ? t.last = t.first = e : (n.next = e, e.prev = n, t.last = e);
}
function cn(e, t) {
	var n = K;
	n !== null && n.f & 8192 && (e |= _);
	var r = {
		ctx: M,
		deps: null,
		nodes: null,
		f: e | h | 512,
		first: null,
		fn: t,
		last: null,
		next: null,
		parent: n,
		b: n && n.b,
		prev: null,
		teardown: null,
		wv: 0,
		ac: null
	};
	F?.register_created_effect(r);
	var i = r;
	if (e & 4) _t === null ? xt.ensure().schedule(r) : _t.push(r);
	else if (t !== null) {
		try {
			qn(r);
		} catch (e) {
			throw U(r), e;
		}
		i.deps === null && i.teardown === null && i.nodes === null && i.first === i.last && !(i.f & 524288) && (i = i.first, e & 16 && e & 65536 && i !== null && (i.f |= x));
	}
	if (i !== null && (i.parent = n, n !== null && sn(i, n), W !== null && W.f & 2 && !(e & 64))) {
		var a = W;
		(a.effects ??= []).push(i);
	}
	return r;
}
function ln() {
	return W !== null && !jn;
}
function un(e) {
	let t = cn(8, null);
	return P(t, m), t.teardown = e, t;
}
function dn(e) {
	on("$effect");
	var t = K.f;
	if (!W && t & 32 && M !== null && !M.i) {
		var n = M;
		(n.e ??= []).push(e);
	} else return fn(e);
}
function fn(e) {
	return cn(4 | ee, e);
}
function pn(e) {
	xt.ensure();
	let t = cn(64 | S, e);
	return (e = {}) => new Promise((n) => {
		e.outro ? Cn(t, () => {
			U(t), n(void 0);
		}) : (U(t), n(void 0));
	});
}
function mn(e) {
	return cn(4, e);
}
function hn(e) {
	return cn(ne | S, e);
}
function gn(e, t = 0) {
	return cn(8 | t, e);
}
function V(e, t = [], n = [], r = []) {
	Ze(r, t, n, (t) => {
		cn(8, () => {
			e(...t.map(X));
		});
	});
}
function _n(e, t = 0) {
	return cn(16 | t, e);
}
function H(e) {
	return cn(32 | S, e);
}
function vn(e) {
	var t = e.teardown;
	if (t !== null) {
		let n = kn, r = W;
		An(!0), G(null);
		try {
			t.call(null);
		} catch (t) {
			an(t, e.parent);
		} finally {
			An(n), G(r);
		}
	}
}
function yn(e, t = !1) {
	var n = e.first;
	for (e.first = e.last = null; n !== null;) {
		let e = n.ac;
		e !== null && Ye(() => {
			e.abort(de);
		});
		var r = n.next;
		n.f & 64 ? n.parent = null : U(n, t), n = r;
	}
}
function bn(e) {
	for (var t = e.first; t !== null;) {
		var n = t.next;
		t.f & 32 || U(t), t = n;
	}
}
function U(e, t = !0) {
	var n = !1;
	(t || e.f & 262144) && e.nodes !== null && e.nodes.end !== null && (xn(e.nodes.start, e.nodes.end), n = !0), e.f |= b, yn(e, t && !n), Kn(e, 0);
	var r = e.nodes && e.nodes.t;
	if (r !== null) for (let e of r) e.stop();
	vn(e), e.f ^= b, e.f |= v;
	var i = e.parent;
	i !== null && i.first !== null && Sn(e), e.next = e.prev = e.teardown = e.ctx = e.deps = e.fn = e.nodes = e.ac = e.b = null;
}
function xn(e, t) {
	for (; e !== null;) {
		var n = e === t ? null : /* @__PURE__ */ Xt(e);
		e.remove(), e = n;
	}
}
function Sn(e) {
	var t = e.parent, n = e.prev, r = e.next;
	n !== null && (n.next = r), r !== null && (r.prev = n), t !== null && (t.first === e && (t.first = r), t.last === e && (t.last = n));
}
function Cn(e, t, n = !0) {
	var r = [];
	e.f |= 256, wn(e, r, !0);
	var i = () => {
		n && U(e), t && t();
	}, a = r.length;
	if (a > 0) {
		var o = () => --a || i();
		for (var s of r) s.out(o);
	} else i();
}
function wn(e, t, n) {
	if (!(e.f & 8192)) {
		e.f ^= _;
		var r = e.nodes && e.nodes.t;
		if (r !== null) for (let e of r) (e.is_global || n) && t.push(e);
		for (var i = e.first; i !== null;) {
			var a = i.next;
			if (!(i.f & 64)) {
				var o = !!(i.f & 65536) || !!(i.f & 32) && !!(e.f & 16);
				wn(i, t, o ? n : !1);
			}
			i = a;
		}
	}
}
function Tn(e) {
	e.f &= -257, En(e, !0);
}
function En(e, t) {
	if (!(e.f & 256) && e.f & 8192) {
		e.f ^= _, e.f & 1024 || (P(e, h), xt.ensure().schedule(e));
		for (var n = e.first; n !== null;) {
			var r = n.next, i = !!(n.f & 65536) || !!(n.f & 32);
			En(n, i ? t : !1), n = r;
		}
		var a = e.nodes && e.nodes.t;
		if (a !== null) for (let e of a) (e.is_global || t) && e.in();
	}
}
function Dn(e, t) {
	if (e.nodes) for (var n = e.nodes.start, r = e.nodes.end; n !== null;) {
		var i = n === r ? null : /* @__PURE__ */ Xt(n);
		t.append(n), n = i;
	}
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/legacy.js
var On = null, kn = !1;
function An(e) {
	kn = e;
}
var W = null, jn = !1;
function G(e) {
	W = e;
}
var K = null;
function Mn(e) {
	K = e;
}
var Nn = null;
function Pn(e) {
	W !== null && (W.f & 2097152 || W.f & 2) && (Nn ??= /* @__PURE__ */ new Set()).add(e);
}
var q = null, J = 0, Y = null;
function Fn(e) {
	Y = e;
}
var In = 1, Ln = 0, Rn = Ln;
function zn(e) {
	Rn = e;
}
function Bn() {
	return ++In;
}
function Vn(e) {
	var t = e.f;
	if (t & 2048) return !0;
	if (t & 4096) {
		for (var n = e.deps, r = n.length, i = 0; i < r; i++) {
			var a = n[i];
			if (Vn(a) && ct(a), a.wv > e.wv) return !0;
		}
		t & 512 && pt === null && P(e, m);
	}
	return !1;
}
function Hn(e, t, n = !0) {
	var r = e.reactions;
	if (r !== null && !(Nn !== null && Nn.has(e))) for (var i = 0; i < r.length; i++) {
		var a = r[i];
		a.f & 2 ? Hn(a, t, !1) : t === a && (n ? P(a, h) : a.f & 1024 && P(a, g), Et(a));
	}
}
function Un(e) {
	var t = q, n = J, r = Y, i = W, a = Nn, o = M, s = jn, c = Rn, l = e.f;
	q = null, J = 0, Y = null, W = l & 96 ? null : e, Nn = null, Ie(e.ctx), jn = !1, Rn = ++Ln, e.ac !== null && (Ye(() => {
		e.ac.abort(de);
	}), e.ac = null);
	try {
		e.f |= C;
		var u = e.fn, d = u();
		e.f |= y;
		var f = Wn(e);
		if (Be() && Y !== null && !jn && f !== null && !(e.f & 6146)) for (var p = 0; p < Y.length; p++) Hn(Y[p], e);
		if (i !== null && i !== e) {
			if (Ln++, i.deps !== null) for (let e = 0; e < n; e += 1) i.deps[e].rv = Ln;
			if (t !== null) for (let e of t) e.rv = Ln;
			Y !== null && (r === null ? r = Y : r.push(...Y));
		}
		return e.f & 8388608 && (e.f ^= re), d;
	} catch (t) {
		return Wn(e), rn(t);
	} finally {
		e.f ^= C, q = t, J = n, Y = r, W = i, Nn = a, Ie(o), jn = s, Rn = c;
	}
}
function Wn(e) {
	var t = e.deps, n = F?.is_fork;
	if (q !== null) {
		var r;
		if (n || Kn(e, J), t !== null && J > 0) for (t.length = J + q.length, r = 0; r < q.length; r++) t[J + r] = q[r];
		else e.deps = t = q;
		if (ln() && e.f & 512) for (r = J; r < t.length; r++) (t[r].reactions ??= []).push(e);
	} else !n && t !== null && J < t.length && (Kn(e, J), t.length = J);
	return t;
}
function Gn(e, r) {
	let i = r.reactions;
	if (i !== null) {
		var a = t.call(i, e);
		if (a !== -1) {
			var o = i.length - 1;
			o === 0 ? i = r.reactions = null : (i[a] = i[o], i.pop());
		}
	}
	if (i === null && r.f & 2 && (q === null || !n.call(q, r))) {
		var s = r;
		s.f & 512 && (s.f ^= 512), s.v !== E && Ge(s), s.ac !== null && Ye(() => {
			s.ac.abort(de), s.ac = null, P(s, h);
		}), lt(s), Kn(s, 0);
	}
}
function Kn(e, t) {
	var n = e.deps;
	if (n !== null) for (var r = t; r < n.length; r++) Gn(e, n[r]);
}
function qn(e) {
	var t = e.f;
	if (!(t & 16384)) {
		P(e, m);
		var n = K;
		K = e;
		try {
			t & 16777232 ? bn(e) : yn(e), vn(e);
			var r = Un(e);
			e.teardown = typeof r == "function" ? r : null, e.wv = In;
		} finally {
			K = n;
		}
	}
}
async function Jn() {
	await Promise.resolve(), St();
}
function X(e) {
	var t = !!(e.f & 2);
	if (On?.add(e), W !== null && !jn && !(K !== null && K.f & 16384) && (Nn === null || !Nn.has(e))) {
		var r = W.deps;
		if (W.f & 2097152) e.rv < Ln && (e.rv = Ln, q === null && r !== null && r[J] === e ? J++ : q === null ? q = [e] : q.push(e));
		else {
			W.deps ??= [], n.call(W.deps, e) || W.deps.push(e);
			var i = e.reactions;
			i === null ? e.reactions = [W] : n.call(i, W) || i.push(W);
		}
	}
	if (kn && At.has(e)) return At.get(e);
	if (t) {
		var a = e;
		if (kn) {
			var o = a.v;
			return (!(a.f & 1024) && a.reactions !== null || Xn(a)) && (o = st(a)), At.set(a, o), o;
		}
		var s = !(a.f & 512) && !jn && W !== null && !!(W.f & 512), c = (a.f & y) === 0;
		Vn(a) && (s && (a.f |= 512), ct(a)), s && !c && (ut(a), Yn(a));
	}
	if (pt?.has(e)) return pt.get(e);
	if (e.f & 8388608) throw e.v;
	return e.v;
}
function Yn(e) {
	if (e.f |= 512, e.deps !== null) for (let r of e.deps) {
		var t = r.reactions;
		t === null ? r.reactions = [e] : n.call(t, e) || t.push(e), r.f & 2 && !(r.f & 512) && (ut(r), Yn(r));
	}
}
function Xn(e) {
	if (e.v === E) return !0;
	if (e.deps === null) return !1;
	for (let t of e.deps) if (At.has(t) || t.f & 2 && Xn(t)) return !0;
	return !1;
}
function Zn(e) {
	var t = jn;
	try {
		return jn = !0, e();
	} finally {
		jn = t;
	}
}
function Qn(e) {
	if (!(typeof e != "object" || !e || e instanceof EventTarget)) {
		if (w in e) $n(e);
		else if (!Array.isArray(e)) for (let t in e) {
			let n = e[t];
			typeof n == "object" && n && w in n && $n(n);
		}
	}
}
function $n(e, t = /* @__PURE__ */ new Set()) {
	if (typeof e == "object" && e && !(e instanceof EventTarget) && !t.has(e)) {
		t.add(e), e instanceof Date && e.getTime();
		for (let n in e) try {
			$n(e[n], t);
		} catch {}
		let n = l(e);
		if (n !== Object.prototype && n !== Array.prototype && n !== Map.prototype && n !== Set.prototype && n !== Date.prototype) {
			let t = o(n);
			for (let n in t) {
				let r = t[n].get;
				if (r) try {
					r.call(e);
				} catch {}
			}
		}
	}
}
[.../* @__PURE__ */ "allowfullscreen.async.autofocus.autoplay.checked.controls.default.disabled.formnovalidate.indeterminate.inert.ismap.loop.multiple.muted.nomodule.novalidate.open.playsinline.readonly.required.reversed.seamless.selected.webkitdirectory.defer.disablepictureinpicture.disableremoteplayback".split(".")];
var er = ["touchstart", "touchmove"];
function tr(e) {
	return er.includes(e);
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/elements/events.js
var nr = Symbol("events"), rr = /* @__PURE__ */ new Set(), ir = /* @__PURE__ */ new Set();
function ar(e, t, n, r = {}) {
	function i(e) {
		if (r.capture || ur.call(t, e), !e.cancelBubble) return Ye(() => n?.call(this, e));
	}
	return e.startsWith("pointer") || e.startsWith("touch") || e === "wheel" ? (i.__removed = !1, N(() => {
		i.__removed || t.addEventListener(e, i, r);
	})) : t.addEventListener(e, i, r), i;
}
function or(e, t, n, r, i) {
	var a = {
		capture: r,
		passive: i
	}, o = ar(e, t, n, a);
	(t === document.body || t === window || t === document || t instanceof HTMLMediaElement) && un(() => {
		o.__removed = !0, t.removeEventListener(e, o, a);
	});
}
function Z(e, t, n) {
	(t[nr] ??= {})[e] = n;
}
function sr(e) {
	for (var t = 0; t < e.length; t++) rr.add(e[t]);
	for (var n of ir) n(e);
}
var cr = null, lr = !1;
function ur(e) {
	var t = this, n = t.ownerDocument, r = e.type, a = e.composedPath?.() || [], o = a[0] || e.target;
	cr = e, lr || (lr = !0, setTimeout(() => {
		lr = !1, cr = null;
	}));
	var s = 0, c = cr === e && e[nr];
	if (c) {
		var l = a.indexOf(c);
		if (l !== -1 && (t === document || t === window)) {
			e[nr] = t;
			return;
		}
		var u = a.indexOf(t);
		if (u === -1) return;
		l <= u && (s = l);
	}
	if (o = a[s] || e.target, o !== t) {
		i(e, "currentTarget", {
			configurable: !0,
			get() {
				return o || n;
			}
		});
		var d = W, f = K;
		G(null), Mn(null);
		try {
			for (var p, m = []; o !== null && o !== t;) {
				try {
					var h = o[nr]?.[r];
					h != null && (!o.disabled || e.target === o) && h.call(o, e);
				} catch (e) {
					p ? m.push(e) : p = e;
				}
				if (e.cancelBubble) break;
				s++, o = s < a.length ? a[s] : null;
			}
			if (p) {
				for (let e of m) queueMicrotask(() => {
					throw e;
				});
				throw p;
			}
		} finally {
			e[nr] = t, delete e.currentTarget, G(d), Mn(f);
		}
	}
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/reconciler.js
var dr = globalThis?.window?.trustedTypes && /* @__PURE__ */ globalThis.window.trustedTypes.createPolicy("svelte-trusted-html", { createHTML: (e) => e });
function fr(e) {
	return dr?.createHTML(e) ?? e;
}
function pr(e) {
	var t = tn("template");
	return t.innerHTML = fr(e.replaceAll("<!>", "<!---->")), t.content;
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/template.js
function mr(e, t) {
	var n = K;
	n.nodes === null && (n.nodes = {
		start: e,
		end: t,
		a: null,
		t: null
	});
}
/*#__NO_SIDE_EFFECTS__*/
function Q(e, t) {
	var n = !!(t & 1), r = !!(t & 2), i, a = !e.startsWith("<!>");
	return () => {
		if (D) return mr(O, null), O;
		i === void 0 && (i = pr(a ? e : "<!>" + e), n || (i = /* @__PURE__ */ Yt(i)));
		var t = r || Gt ? document.importNode(i, !0) : i.cloneNode(!0);
		if (n) {
			var o = /* @__PURE__ */ Yt(t), s = t.lastChild;
			mr(o, s);
		} else mr(t, t);
		return t;
	};
}
function hr() {
	if (D) return mr(O, null), O;
	var e = document.createDocumentFragment(), t = document.createComment(""), n = R();
	return e.append(t, n), mr(t, n), e;
}
function $(e, t) {
	if (D) {
		var n = K;
		(!(n.f & 32768) || n.nodes.end === null) && (n.nodes.end = O), ye();
	} else e !== null && e.before(t);
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/reactivity/create-subscriber.js
function gr(e) {
	let t = 0, n = Mt(0), r;
	return () => {
		ln() && (X(n), gn(() => (t === 0 && (r = Zn(() => e(() => zt(n)))), t += 1, () => {
			N(() => {
				--t, t === 0 && (r?.(), r = void 0, zt(n));
			});
		})));
	};
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/blocks/boundary.js
var _r = x | S;
function vr(e, t, n, r) {
	new yr(e, t, n, r);
}
var yr = class {
	parent;
	is_pending = !1;
	transform_error;
	#e;
	#t = D ? O : null;
	#n;
	#r;
	#i;
	#a = null;
	#o = null;
	#s = null;
	#c = null;
	#l = 0;
	#u = 0;
	#d = !1;
	#f = /* @__PURE__ */ new Set();
	#p = /* @__PURE__ */ new Set();
	#m = null;
	#h = gr(() => (this.#m = Mt(this.#l), () => {
		this.#m = null;
	}));
	constructor(e, t, n, r) {
		this.#e = e, this.#n = t, this.#r = (e) => {
			var t = K;
			t.b = this, t.f |= 128, n(e);
		}, this.parent = K.b, this.transform_error = r ?? this.parent?.transform_error ?? ((e) => e), this.#i = _n(() => {
			if (D) {
				let e = xe(this.#t);
				ye();
				let t = e === "[!";
				if (e.startsWith("[?")) {
					let t = JSON.parse(e.slice(2));
					this.#_(t);
				} else t ? this.#b() : this.#g();
			} else this.#x();
		}, _r), D && (this.#e = O);
	}
	#g() {
		try {
			this.#a = H(() => this.#r(this.#e));
		} catch (e) {
			this.error(e);
		}
	}
	#_(e) {
		let t = this.#n.failed, { reset: n, invoke_onerror: r } = this.#v(e);
		N(r), t && (this.#s = H(() => {
			t(this.#e, () => e, () => n);
		}));
	}
	#v(e) {
		var t = !1, n = !1;
		let r = () => {
			this.#y() || (t ? _e() : (t = !0, n && Fe(), this.#s !== null && Cn(this.#s, () => {
				this.#s = null;
			}), this.#C(() => {
				this.#x();
			})));
		};
		return {
			reset: r,
			invoke_onerror: () => {
				if (!this.#y()) try {
					n = !0, this.#n.onerror?.(e, r), n = !1;
				} catch (e) {
					an(e, this.#i && this.#i.parent);
				}
			}
		};
	}
	#y() {
		return (this.#i.f & (v | b)) !== 0;
	}
	#b() {
		let e = this.#n.pending;
		e && (this.is_pending = !0, this.#o = H(() => e(this.#e)), N(() => {
			if (!this.#y()) {
				var e = this.#c = document.createDocumentFragment(), t = R(), n = !1;
				e.append(t), this.#a = this.#C(() => {
					try {
						return H(() => this.#r(t));
					} catch (e) {
						try {
							this.error(e), n = !0;
						} catch (e) {
							an(e, this.#i.parent);
						}
						return null;
					}
				}), this.#a === null ? (this.#c = null, n && this.#S(F)) : this.#u === 0 && (this.#e.before(e), this.#c = null, Cn(this.#o, () => {
					this.#o = null;
				}), this.#S(F));
			}
		}));
	}
	#x() {
		try {
			if (this.is_pending = this.has_pending_snippet(), this.#u = 0, this.#l = 0, this.#a = H(() => {
				this.#r(this.#e);
			}), this.#u > 0) {
				var e = this.#c = document.createDocumentFragment();
				Dn(this.#a, e);
				let t = this.#n.pending;
				this.#o = H(() => t(this.#e));
			} else this.#S(F);
		} catch (e) {
			this.error(e);
		}
	}
	#S(e) {
		this.is_pending = !1, e.transfer_effects(this.#f, this.#p);
	}
	defer_effect(e) {
		Ke(e, this.#f, this.#p);
	}
	is_rendered() {
		return !this.is_pending && (!this.parent || this.parent.is_rendered());
	}
	has_pending_snippet() {
		return !!this.#n.pending;
	}
	#C(e) {
		var t = K, n = W, r = M;
		Mn(this.#i), G(this.#i), Ie(this.#i.ctx);
		try {
			return xt.ensure(), e();
		} finally {
			Mn(t), G(n), Ie(r);
		}
	}
	#w(e, t) {
		this.has_pending_snippet() ? (this.#u += e, this.#u === 0 && (this.#S(t), this.#o && Cn(this.#o, () => {
			this.#o = null;
		}), this.#c &&= (this.#e.before(this.#c), null))) : this.parent && this.parent.#w(e, t);
	}
	update_pending_count(e, t) {
		this.#w(e, t), this.#l += e, !(!this.#m || this.#d) && (this.#d = !0, N(() => {
			this.#d = !1, this.#m && It(this.#m, this.#l);
		}));
	}
	get_effect_pending() {
		return this.#h(), X(this.#m);
	}
	error(e) {
		if (e === T || !this.#n.onerror && !this.#n.failed) throw e;
		F?.is_fork ? (this.#a && F.skip_effect(this.#a), this.#o && F.skip_effect(this.#o), this.#s && F.skip_effect(this.#s), F.oncommit(() => {
			this.#y() || this.#T(e);
		})) : this.#T(e);
	}
	#T(e) {
		this.#a &&= (U(this.#a), null), this.#o &&= (U(this.#o), null), this.#s &&= (U(this.#s), null), D && (k(this.#t), j(), k(be()));
		let t = this.#n.failed, n = (e) => {
			if (this.#y()) return;
			let { reset: n, invoke_onerror: r } = this.#v(e);
			r(), t && !this.#y() && (this.#s = this.#C(() => {
				try {
					return H(() => {
						var r = K;
						r.b = this, r.f |= 128, t(this.#e, () => e, () => n);
					});
				} catch (e) {
					return an(e, this.#i.parent), null;
				}
			}));
		};
		N(() => {
			if (!this.#y()) {
				var t;
				try {
					t = this.transform_error(e);
				} catch (e) {
					an(e, this.#i && this.#i.parent);
					return;
				}
				typeof t == "object" && t && typeof t.then == "function" ? t.then(n, (e) => an(e, this.#i && this.#i.parent)) : n(t);
			}
		});
	}
};
function br(e, t) {
	var n = t == null ? "" : typeof t == "object" ? `${t}` : t;
	n !== (e[le] ??= e.nodeValue) && (e[le] = n, e.nodeValue = `${n}`);
}
function xr(e, t) {
	return Cr(e, t);
}
var Sr = /* @__PURE__ */ new Map();
function Cr(e, { target: t, anchor: n, props: i = {}, events: a, context: o, intro: s = !0, transformError: c }) {
	Jt();
	var l = void 0, u = pn(() => {
		var s = n ?? t.appendChild(R());
		vr(s, { pending: () => {} }, (t) => {
			Le({});
			var n = M;
			if (o && (n.c = o), a && (i.$$events = a), D && mr(t, null), l = e(t, i) || ze(), D && (K.nodes.end = O, O === null || O.nodeType !== 8 || O.data !== "]")) throw he(), T;
			Re();
		}, c);
		var u = /* @__PURE__ */ new Set(), d = (e) => {
			for (var n = 0; n < e.length; n++) {
				var r = e[n];
				if (!u.has(r)) {
					u.add(r);
					var i = tr(r);
					for (let e of [t, document]) {
						var a = Sr.get(e);
						a === void 0 && (a = /* @__PURE__ */ new Map(), Sr.set(e, a));
						var o = a.get(r);
						o === void 0 ? (e.addEventListener(r, ur, { passive: i }), a.set(r, 1)) : a.set(r, o + 1);
					}
				}
			}
		};
		return d(r(rr)), ir.add(d), () => {
			for (var e of u) for (let n of [t, document]) {
				var r = Sr.get(n), i = r.get(e);
				--i == 0 ? (n.removeEventListener(e, ur), r.delete(e), r.size === 0 && Sr.delete(n)) : r.set(e, i);
			}
			ir.delete(d), s !== n && s.parentNode?.removeChild(s);
		};
	});
	return wr.set(l, u), l;
}
var wr = /* @__PURE__ */ new WeakMap();
function Tr(e, t) {
	let n = wr.get(e);
	return n ? (wr.delete(e), n(t)) : Promise.resolve();
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/blocks/branches.js
var Er = class {
	anchor;
	#e = /* @__PURE__ */ new Map();
	#t = /* @__PURE__ */ new Map();
	#n = /* @__PURE__ */ new Map();
	#r = /* @__PURE__ */ new Set();
	#i = !0;
	constructor(e, t = !0) {
		this.anchor = e, this.#i = t;
	}
	#a = (e) => {
		if (this.#e.has(e)) {
			var t = this.#e.get(e), n = this.#t.get(t);
			if (n) Tn(n), this.#r.delete(t);
			else {
				var r = this.#n.get(t);
				r && (Tn(r.effect), this.#t.set(t, r.effect), this.#n.delete(t), r.fragment.lastChild.remove(), this.anchor.before(r.fragment), n = r.effect);
			}
			for (let [t, n] of this.#e) {
				if (this.#e.delete(t), t === e) break;
				let r = this.#n.get(n);
				r && (U(r.effect), this.#n.delete(n));
			}
			for (let [e, r] of this.#t) {
				if (e === t || this.#r.has(e)) continue;
				let i = () => {
					if (Array.from(this.#e.values()).includes(e)) {
						var t = document.createDocumentFragment();
						Dn(r, t), t.append(R()), this.#n.set(e, {
							effect: r,
							fragment: t
						});
					} else U(r);
					this.#r.delete(e), this.#t.delete(e);
				};
				this.#i || !n ? (this.#r.add(e), Cn(r, i, !1)) : i();
			}
		}
	};
	#o = (e) => {
		this.#e.delete(e);
		let t = Array.from(this.#e.values());
		for (let [e, n] of this.#n) t.includes(e) || (U(n.effect), this.#n.delete(e));
	};
	ensure(e, t) {
		var n = F, r = en();
		if (t && !this.#t.has(e) && !this.#n.has(e)) {
			if (r) {
				var i = document.createDocumentFragment(), a = R();
				i.append(a), this.#n.set(e, {
					effect: H(() => t(a)),
					fragment: i
				});
			} else this.#t.set(e, H(() => t(this.anchor)));
		}
		if (this.#e.set(n, e), r) {
			for (let [t, r] of this.#t) t === e ? n.unskip_effect(r) : n.skip_effect(r);
			for (let [t, r] of this.#n) t === e ? n.unskip_effect(r.effect) : n.skip_effect(r.effect);
			n.oncommit(this.#a), n.ondiscard(this.#o);
		} else D && (this.anchor = O), this.#a(n);
	}
};
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/blocks/if.js
function Dr(e, t, n = !1) {
	var r;
	D && (r = O, ye());
	var i = new Er(e), a = n ? x : 0;
	function o(e, t) {
		if (D) {
			var n = xe(r);
			if (e !== parseInt(n.substring(1))) {
				var a = be();
				k(a), i.anchor = a, ve(!1), i.ensure(e, t), ve(!0);
				return;
			}
		}
		i.ensure(e, t);
	}
	_n(() => {
		var e = !1;
		t((t, n = 0) => {
			e = !0, o(n, t);
		}), e || o(-1, null);
	}, a);
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/blocks/key.js
var Or = Symbol("NaN");
function kr(e, t, n) {
	D && ye();
	var r = new Er(e), i = !Be();
	_n(() => {
		var e = t();
		e !== e && (e = Or), i && typeof e == "object" && e && (e = {}), r.ensure(e, n);
	});
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/blocks/each.js
function Ar(e, t) {
	return t;
}
function jr(e, t, n) {
	for (var i = [], a = t.length, o, s = t.length, c = 0; c < a; c++) {
		let n = t[c];
		Cn(n, () => {
			if (o) {
				if (o.pending.delete(n), o.done.add(n), o.pending.size === 0) {
					var t = e.outrogroups;
					Mr(e, r(o.done)), t.delete(o), t.size === 0 && (e.outrogroups = null);
				}
			} else --s;
		}, !1);
	}
	if (s === 0) {
		var l = i.length === 0 && n !== null && e.pending.size === 0;
		if (l) {
			var u = n, d = u.parentNode;
			$t(d), d.append(u), e.items.clear();
		}
		Mr(e, t, !l);
	} else o = {
		pending: new Set(t),
		done: /* @__PURE__ */ new Set()
	}, (e.outrogroups ??= /* @__PURE__ */ new Set()).add(o);
}
function Mr(e, t, n = !0) {
	var r;
	if (e.pending.size > 0) {
		r = /* @__PURE__ */ new Set();
		for (let t of e.pending.values()) for (let n of t) r.add(e.items.get(n).e);
	}
	for (var i = 0; i < t.length; i++) {
		var a = t[i];
		r?.has(a) ? (a.f |= te, Dn(a, document.createDocumentFragment())) : U(t[i], n);
	}
}
var Nr;
function Pr(t, n, i, a, o, s = null) {
	var c = t, l = /* @__PURE__ */ new Map();
	if (n & 4) {
		var u = t;
		c = D ? k(/* @__PURE__ */ Yt(u)) : u.appendChild(R());
	}
	D && ye();
	var d = null, f = /* @__PURE__ */ at(() => {
		var t = i();
		return e(t) ? t : t == null ? [] : r(t);
	}), p = /* @__PURE__ */ new Map(), m = !0;
	function h(e) {
		if (!(_.effect.f & 16384)) {
			_.pending.delete(e);
			var t = X(f);
			_.fallback = d, Ir(_, t, c, n, a), d !== null && (t.length === 0 ? d.f & 33554432 ? (d.f ^= te, Rr(d, null, c)) : Tn(d) : Cn(d, () => {
				d = null;
			}));
		}
	}
	function g(e) {
		_.pending.delete(e);
	}
	var _ = {
		effect: _n(() => {
			var e = X(f), t = e.length;
			let r = !1;
			D && xe(c) === "[!" != (t === 0) && (c = be(), k(c), ve(!1), r = !0);
			for (var u = /* @__PURE__ */ new Set(), _ = F, v = en(), y = 0; y < t; y += 1) {
				D && O.nodeType === 8 && O.data === "]" && (c = O, r = !0, ve(!1));
				var b = e[y], x = a(b, y), S = m ? null : l.get(x);
				S ? (S.v && It(S.v, b), S.i && It(S.i, y), v && _.unskip_effect(S.e)) : (S = Lr(l, m ? c : Nr ??= R(), b, x, y, o, n, i), m || (S.e.f |= te), l.set(x, S)), u.add(x);
			}
			if (t === 0 && s && !d && (m ? d = H(() => s(c)) : (d = H(() => s(Nr ??= R())), d.f |= te)), t > u.size && De("", "", ""), D && t > 0 && k(be()), !m) {
				if (p.set(_, u), v) {
					for (let [e, t] of l) u.has(e) || _.skip_effect(t.e);
					_.oncommit(h), _.ondiscard(g);
				} else h(_);
			}
			r && ve(!0), X(f);
		}),
		flags: n,
		items: l,
		pending: p,
		outrogroups: null,
		fallback: d
	};
	m = !1, D && (c = O);
}
function Fr(e) {
	for (; e !== null && !(e.f & 32);) e = e.next;
	return e;
}
function Ir(e, t, n, i, a) {
	var o = !!(i & 8), s = t.length, c = e.items, l = Fr(e.effect.first), u, d = null, f, p = [], m = [], h, g, _, v;
	if (o) for (v = 0; v < s; v += 1) h = t[v], g = a(h, v), _ = c.get(g).e, _.f & 33554432 || (_.nodes?.a?.measure(), (f ??= /* @__PURE__ */ new Set()).add(_));
	for (v = 0; v < s; v += 1) {
		if (h = t[v], g = a(h, v), _ = c.get(g).e, e.outrogroups !== null) for (let t of e.outrogroups) t.pending.delete(_), t.done.delete(_);
		if (_.f & 8192 && (Tn(_), o && (_.nodes?.a?.unfix(), (f ??= /* @__PURE__ */ new Set()).delete(_))), _.f & 33554432) {
			if (_.f ^= te, _ === l) Rr(_, null, n);
			else {
				var y = d ? d.next : l;
				_ === e.effect.last && (e.effect.last = _.prev), _.prev && (_.prev.next = _.next), _.next && (_.next.prev = _.prev), zr(e, d, _), zr(e, _, y), Rr(_, y, n), d = _, p = [], m = [], l = Fr(d.next);
				continue;
			}
		}
		if (_ !== l) {
			if (u !== void 0 && u.has(_)) {
				if (p.length < m.length) {
					var b = m[0], x;
					d = b.prev;
					var S = p[0], ee = p[p.length - 1];
					for (x = 0; x < p.length; x += 1) Rr(p[x], b, n);
					for (x = 0; x < m.length; x += 1) u.delete(m[x]);
					zr(e, S.prev, ee.next), zr(e, d, S), zr(e, ee, b), l = b, d = ee, --v, p = [], m = [];
				} else u.delete(_), Rr(_, l, n), zr(e, _.prev, _.next), zr(e, _, d === null ? e.effect.first : d.next), zr(e, d, _), d = _;
				continue;
			}
			for (p = [], m = []; l !== null && l !== _;) (u ??= /* @__PURE__ */ new Set()).add(l), m.push(l), l = Fr(l.next);
			if (l === null) continue;
		}
		_.f & 33554432 || p.push(_), d = _, l = Fr(_.next);
	}
	if (e.outrogroups !== null) {
		for (let t of e.outrogroups) t.pending.size === 0 && (Mr(e, r(t.done)), e.outrogroups?.delete(t));
		e.outrogroups.size === 0 && (e.outrogroups = null);
	}
	if (l !== null || u !== void 0) {
		var C = [];
		if (u !== void 0) for (_ of u) _.f & 8192 || C.push(_);
		for (; l !== null;) !(l.f & 8192) && l !== e.fallback && C.push(l), l = Fr(l.next);
		var ne = C.length;
		if (ne > 0) {
			var re = i & 4 && s === 0 ? n : null;
			if (o) {
				for (v = 0; v < ne; v += 1) C[v].nodes?.a?.measure();
				for (v = 0; v < ne; v += 1) C[v].nodes?.a?.fix();
			}
			jr(e, C, re);
		}
	}
	o && N(() => {
		if (f !== void 0) for (_ of f) _.nodes?.a?.apply();
	});
}
function Lr(e, t, n, r, i, a, o, s) {
	var c = o & 1 ? o & 16 ? Mt(n) : /* @__PURE__ */ Nt(n, !1, !1) : null, l = o & 2 ? Mt(i) : null;
	return {
		v: c,
		i: l,
		e: H(() => (a(t, c ?? n, l ?? i, s), () => {
			e.delete(r);
		}))
	};
}
function Rr(e, t, n) {
	if (e.nodes) for (var r = e.nodes.start, i = e.nodes.end, a = t && !(t.f & 33554432) ? t.nodes.start : n; r !== null;) {
		var o = /* @__PURE__ */ Xt(r);
		if (a.before(r), r === i) return;
		r = o;
	}
}
function zr(e, t, n) {
	t === null ? e.effect.first = n : t.next = n, n === null ? e.effect.last = t : n.prev = t;
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/blocks/snippet.js
function Br(e, t, ...n) {
	var r = new Er(e);
	_n(() => {
		let e = t() ?? null;
		r.ensure(e, e && ((t) => e(t, ...n)));
	}, x);
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/elements/actions.js
function Vr(e, t, n) {
	mn(() => {
		var r = Zn(() => t(e, n?.()) || {});
		if (n && r?.update) {
			var i = !1, a = {};
			gn(() => {
				var e = n();
				Qn(e), i && Ce(a, e) && (a = e, r.update(e));
			}), i = !0;
		}
		if (r?.destroy) return () => r.destroy();
	});
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/shared/attributes.js
var Hr = [..." 	\n\r\f\xA0\v﻿"];
function Ur(e, t, n) {
	var r = e == null ? "" : "" + e;
	if (t && (r = r ? r + " " + t : t), n) {
		for (var i of Object.keys(n)) if (n[i]) r = r ? r + " " + i : i;
		else if (r.length) for (var a = i.length, o = 0; (o = r.indexOf(i, o)) >= 0;) {
			var s = o + a;
			(o === 0 || Hr.includes(r[o - 1])) && (s === r.length || Hr.includes(r[s])) ? r = (o === 0 ? "" : r.substring(0, o)) + r.substring(s + 1) : o = s;
		}
	}
	return r === "" ? null : r;
}
function Wr(e, t = !1) {
	var n = t ? " !important;" : ";", r = "";
	for (var i of Object.keys(e)) {
		var a = e[i];
		a != null && a !== "" && (r += " " + i + ": " + a + n);
	}
	return r;
}
function Gr(e) {
	return e[0] !== "-" || e[1] !== "-" ? e.toLowerCase() : e;
}
function Kr(e, t) {
	if (t) {
		var n = "", r, i;
		if (Array.isArray(t) ? (r = t[0], i = t[1]) : r = t, e) {
			e = String(e).replaceAll(/\/\*.*?\*\//g, "").trim();
			var a = !1, o = 0, s = !1, c = [];
			r && c.push(...Object.keys(r).map(Gr)), i && c.push(...Object.keys(i).map(Gr));
			var l = 0, u = -1;
			let t = e.length;
			for (var d = 0; d < t; d++) {
				var f = e[d];
				if (s ? f === "/" && e[d - 1] === "*" && (s = !1) : a ? a === f && (a = !1) : f === "/" && e[d + 1] === "*" ? s = !0 : f === "\"" || f === "'" ? a = f : f === "(" ? o++ : f === ")" && o--, !s && a === !1 && o === 0) {
					if (f === ":" && u === -1) u = d;
					else if (f === ";" || d === t - 1) {
						if (u !== -1) {
							var p = Gr(e.substring(l, u).trim());
							if (!c.includes(p)) {
								f !== ";" && d++;
								var m = e.substring(l, d).trim();
								n += " " + m + ";";
							}
						}
						l = d + 1, u = -1;
					}
				}
			}
		}
		return r && (n += Wr(r)), i && (n += Wr(i, !0)), n = n.trim(), n === "" ? null : n;
	}
	return e == null ? null : String(e);
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/elements/class.js
function qr(e, t, n, r, i, a) {
	var o = e[se];
	if (D || o !== n || o === void 0) {
		var s = Ur(n, r, a);
		(!D || s !== e.getAttribute("class")) && (s == null ? e.removeAttribute("class") : t ? e.className = s : e.setAttribute("class", s)), e[se] = n;
	} else if (a && i !== a) for (var c in a) {
		var l = !!a[c];
		(i == null || l !== !!i[c]) && e.classList.toggle(c, l);
	}
	return a;
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/elements/style.js
function Jr(e, t = {}, n, r) {
	for (var i in n) {
		var a = n[i];
		t[i] !== a && (n[i] == null ? e.style.removeProperty(i) : e.style.setProperty(i, a, r));
	}
}
function Yr(e, t, n, r) {
	var i = e[ce];
	if (D || i !== t) {
		var a = Kr(t, r);
		(!D || a !== e.getAttribute("style")) && (a == null ? e.removeAttribute("style") : e.style.cssText = a), e[ce] = t;
	} else r && (Array.isArray(r) ? (Jr(e, n?.[0], r[0]), Jr(e, n?.[1], r[1], "important")) : Jr(e, n, r));
	return r;
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/elements/bindings/select.js
function Xr(e, t) {
	t ? e.hasAttribute("selected") || e.setAttribute("selected", "") : e.removeAttribute("selected");
}
function Zr(t, n) {
	var r = t.__defaultValue, i = t.multiple, a = i ? r ?? [] : null;
	if (!i || e(a)) {
		var o = t.selectedIndex, s = n && i ? new Set(t.selectedOptions) : null;
		for (var c of t.options) {
			var l = ti(c);
			Xr(c, i ? a.includes(l) : Ut(l, r));
		}
		if (n) {
			if (s !== null) for (c of t.options) {
				var u = s.has(c);
				c.selected !== u && (c.selected = u);
			}
			else t.selectedIndex !== o && (t.selectedIndex = o);
		}
	}
}
function Qr(t, n, r = !1) {
	if (t.multiple) {
		if (n == null) return;
		if (!e(n)) return ge();
		for (var i of t.options) i.selected = n.includes(ti(i));
	} else {
		for (i of t.options) if (Ut(ti(i), n)) {
			i.selected = !0;
			return;
		}
		(!r || n !== void 0) && (t.selectedIndex = -1);
	}
}
function $r(e) {
	var t = new MutationObserver((t) => {
		t.every(ni) || ("__defaultValue" in e && Zr(e, !1), "__value" in e && Qr(e, e.__value));
	});
	t.observe(e, {
		childList: !0,
		subtree: !0,
		attributes: !0,
		attributeFilter: ["value"]
	}), un(() => {
		t.disconnect();
	});
}
function ei(e, t, n = t) {
	var r = /* @__PURE__ */ new WeakSet(), i = !0;
	Xe(e, "change", (t) => {
		var i = t ? "[selected]" : ":checked", a;
		if (e.multiple) a = [].map.call(e.querySelectorAll(i), ti);
		else {
			var o = e.querySelector(i) ?? e.querySelector("option:not([disabled])");
			a = o && ti(o);
		}
		n(a), e.__value = a, F !== null && r.add(F);
	}), mn(() => {
		var a = t();
		if (e === document.activeElement) {
			var o = F;
			if (r.has(o)) return;
		}
		if (Qr(e, a, i), i && a === void 0) {
			var s = e.querySelector(":checked");
			s !== null && (a = ti(s), n(a));
		}
		e.__value = a, i = !1;
	});
}
function ti(e) {
	return "__value" in e ? e.__value : e.value;
}
function ni(e) {
	if (e.target.closest("selectedcontent") !== null) return !0;
	if (e.type === "childList") {
		var t = [...e.addedNodes, ...e.removedNodes];
		return t.length > 0 && t.every((e) => e.nodeName === "SELECTEDCONTENT");
	}
	return !1;
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/elements/attributes.js
var ri = Symbol("is custom element"), ii = Symbol("is html"), ai = fe ? "link" : "LINK";
function oi(e) {
	if (D) {
		var t = !1, n = () => {
			if (!t) {
				if (t = !0, e.hasAttribute("value")) {
					var n = e.value;
					si(e, "value", null), e.value = n;
				}
				if (e.hasAttribute("checked")) {
					var r = e.checked;
					si(e, "checked", null), e.checked = r;
				}
			}
		};
		e[ue] = n, N(n), Je();
	}
}
function si(e, t, n, r) {
	var i = ci(e);
	D && (i[t] = e.getAttribute(t), t === "src" || t === "srcset" || t === "href" && e.nodeName === ai) || i[t] !== (i[t] = n) && (t === "loading" && (e[ae] = n), n == null ? e.removeAttribute(t) : typeof n != "string" && ui(e).has(t) ? e[t] = n : e.setAttribute(t, n));
}
function ci(e) {
	return e[oe] ??= {
		[ri]: e.nodeName.includes("-"),
		[ii]: e.namespaceURI === pe
	};
}
var li = /* @__PURE__ */ new Map();
function ui(e) {
	var t = e.getAttribute("is") || e.nodeName, n = li.get(t);
	if (n) return n;
	li.set(t, n = /* @__PURE__ */ new Set());
	for (var r, i = e, a = Element.prototype; a !== i;) {
		for (var s in r = o(i), r) r[s].set && s !== "innerHTML" && s !== "textContent" && s !== "innerText" && n.add(s);
		i = l(i);
	}
	return n;
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/elements/bindings/input.js
function di(e, t, n = t) {
	var r = /* @__PURE__ */ new WeakSet();
	Xe(e, "input", async (i) => {
		var a = i ? e.defaultValue : e.value;
		if (a = hi(e) ? gi(a) : a, n(a), F !== null && r.add(F), await Jn(), a !== (a = t())) {
			var o = e.selectionStart, s = e.selectionEnd, c = e.value.length;
			if (e.value = a ?? "", s !== null) {
				var l = e.value.length;
				o === s && s === c && l > c ? (e.selectionStart = l, e.selectionEnd = l) : (e.selectionStart = o, e.selectionEnd = Math.min(s, l));
			}
		}
	}), (D && e.defaultValue !== e.value || Zn(t) == null && e.value) && (n(hi(e) ? gi(e.value) : e.value), F !== null && r.add(F)), gn(() => {
		var n = t();
		if (e === document.activeElement) {
			var i = F;
			if (r.has(i)) return;
		}
		hi(e) && n === gi(e.value) || (e.type !== "date" || n || e.value) && n !== e.value && (e.value = n ?? "");
	});
}
var fi = /* @__PURE__ */ new Set();
function pi(e, t, n, r, i = r) {
	var a = n.getAttribute("type") === "checkbox", o = e;
	let s = !1;
	if (t !== null) for (var c of t) o = o[c] ??= [];
	o.push(n), Xe(n, "change", () => {
		var e = n.__value;
		a && (e = mi(o, e, n.checked)), i(e);
	}, () => i(a ? [] : null)), gn(() => {
		var e = r();
		D && n.defaultChecked !== n.checked ? s = !0 : a ? (e ||= [], n.checked = e.includes(n.__value)) : n.checked = Ut(n.__value, e);
	}), un(() => {
		var e = o.indexOf(n);
		e !== -1 && o.splice(e, 1);
	}), fi.has(o) || (fi.add(o), N(() => {
		o.sort((e, t) => e.compareDocumentPosition(t) === 4 ? -1 : 1), fi.delete(o);
	})), N(() => {
		if (s) {
			var e = a ? mi(o, e, n.checked) : o.find((e) => e.checked)?.__value;
			i(e);
		}
	});
}
function mi(e, t, n) {
	for (var r = /* @__PURE__ */ new Set(), i = 0; i < e.length; i += 1) e[i].checked && r.add(e[i].__value);
	return n || r.delete(t), Array.from(r);
}
function hi(e) {
	var t = e.type;
	return t === "number" || t === "range";
}
function gi(e) {
	return e === "" ? null : +e;
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/client/dom/elements/bindings/this.js
function _i(e, t) {
	return e === t || e?.[w] === t;
}
function vi(e = ze(), t, n, r) {
	var i = M.r, a = K;
	return mn(() => {
		var o, s;
		return gn(() => {
			o = s, s = r?.() || [], Zn(() => {
				_i(n(...s), e) || (t(e, ...s), o && _i(n(...o), e) && t(null, ...o));
			});
		}), () => {
			let r = a;
			for (; r !== i && r.parent !== null && r.parent.f & 33554432;) r = r.parent;
			let o = () => {
				s && _i(n(...s), e) && t(null, ...s);
			}, c = r.teardown;
			r.teardown = () => {
				o(), c?.();
			};
		};
	}), e;
}
function yi(e) {
	M === null && Te("onMount"), dn(() => {
		let t = Zn(e);
		if (typeof t == "function") return t;
	});
}
//#endregion
//#region node_modules/.pnpm/svelte@5.57.2/node_modules/svelte/src/internal/disclose-version.js
typeof window < "u" && ((window.__svelte ??= {}).v ??= /* @__PURE__ */ new Set()).add("5");
//#endregion
//#region src/lib/hass.ts
var bi;
function xi(e) {
	bi = e;
}
function Si() {
	return bi !== void 0;
}
function Ci(e, t, n) {
	if (!bi) throw Error("Home Assistant is not connected.");
	return bi.callWS({
		type: "map_editor",
		action: e,
		...t ? { entry_id: t } : {},
		...n ? { data: n } : {}
	});
}
//#endregion
//#region src/lib/maps.ts
function wi(e) {
	return Ci("status", e);
}
async function Ti(e) {
	if (Si()) return Oi(await Ci("load", e));
	let t = await fetch("/api/map", {
		method: "POST",
		headers: { "Content-Type": "application/json" },
		body: JSON.stringify({ hostname: e })
	}), n = await t.json();
	if (!t.ok) throw Error(n.error ?? "Map loading failed.");
	return Oi(n);
}
async function Ei(e, t, n, r, i = () => {}) {
	if (Si()) {
		let a = await Ci("save", e, {
			native: t.native,
			cells: Di(n),
			rooms: Di(r),
			confirmation: "install-and-reboot"
		});
		for (; a.state === "saving";) i(a), await new Promise((e) => setTimeout(e, 2e3)), a = await wi(e);
		if (i(a), a.state !== "done") throw Error(a.error ?? "Save was interrupted. Check the robot before retrying.");
		return Ti(e);
	}
	let a = await fetch("/api/map/save", {
		method: "POST",
		headers: { "Content-Type": "application/json" },
		body: JSON.stringify({
			native: t.native,
			cells: Di(n),
			rooms: Di(r),
			hostname: e,
			confirmation: "install-and-reboot"
		})
	}), o = await a.json();
	if (!a.ok) throw Error(o.error ?? "Could not save the map.");
	return Oi(o.map);
}
function Di(e) {
	let t = "";
	for (let n = 0; n < e.length; n += 32768) t += String.fromCharCode(...e.subarray(n, n + 32768));
	return btoa(t);
}
function Oi(e) {
	return {
		...e,
		cells: ki(e.cells),
		rooms: ki(e.rooms)
	};
}
function ki(e) {
	return Uint8Array.from(atob(e), (e) => e.charCodeAt(0));
}
//#endregion
//#region src/lib/view.ts
function Ai(e) {
	let t = {
		x: 0,
		y: 0,
		width: e.width,
		height: e.height
	};
	if (!e.cells) return t;
	let n = e.width, r = e.height, i = -1, a = -1;
	for (let t = 0; t < e.cells.length; t++) {
		if (e.cells[t] === 128) continue;
		let o = t % e.width, s = Math.floor(t / e.width);
		n = Math.min(n, o), r = Math.min(r, s), i = Math.max(i, o), a = Math.max(a, s);
	}
	return i < 0 ? t : {
		x: n,
		y: r,
		width: i - n + 1,
		height: a - r + 1
	};
}
function ji(e, t, n) {
	let r = Ai(n), i = Math.max(.01, Math.min(64, Math.min(e / r.width, t / r.height) * .9));
	return {
		x: (e - r.width * i) / 2 - r.x * i,
		y: (t - r.height * i) / 2 - r.y * i,
		scale: i
	};
}
function Mi(e, t, n, r) {
	let i = Math.max(.01, Math.min(64, e.scale * t)), a = i / e.scale;
	return {
		x: n - (n - e.x) * a,
		y: r - (r - e.y) * a,
		scale: i
	};
}
function Ni(e) {
	let t = e * .61803398875 % 1;
	return [
		0,
		2 / 3,
		1 / 3
	].map((e) => {
		let n = Math.abs((t + e) % 1 * 6 - 3) - 1;
		return Math.round(90 + Math.max(0, Math.min(1, n)) * 140);
	});
}
function Pi(e) {
	let t = new Uint8ClampedArray(e.cells.length * 4), n = Array.from({ length: 64 }, (e, t) => Ni(t));
	for (let r = 0; r < e.cells.length; r++) {
		let i = e.cells[r];
		if (i === 128) continue;
		let a = Math.round(192 - 84 / 255 * i), o = e.rooms[r], s = o && i < 128 ? n[o] : void 0;
		for (let e = 0; e < 3; e++) t[r * 4 + e] = s ? Math.round(a * .8 + s[e] * .2) : a;
		t[r * 4 + 3] = 255;
	}
	return t;
}
function Fi(e) {
	let t = /* @__PURE__ */ new Map();
	for (let n = 0; n < e.rooms.length; n++) {
		let r = e.rooms[n];
		if (!r || e.cells[n] >= 128) continue;
		let i = t.get(r) ?? {
			x: 0,
			y: 0,
			count: 0
		};
		i.x += n % e.width + .5, i.y += Math.floor(n / e.width) + .5, i.count++, t.set(r, i);
	}
	let n = /* @__PURE__ */ new Map();
	for (let r = 0; r < e.rooms.length; r++) {
		let i = e.rooms[r], a = t.get(i);
		if (!a || e.cells[r] >= 128) continue;
		let o = r % e.width + .5, s = Math.floor(r / e.width) + .5, c = (o - a.x / a.count) ** 2 + (s - a.y / a.count) ** 2;
		c >= (n.get(i)?.distance ?? Infinity) || n.set(i, {
			id: i,
			x: o,
			y: s,
			distance: c
		});
	}
	return [...n.values()];
}
//#endregion
//#region src/lib/editor.ts
var Ii = {
	Floor: 0,
	Unknown: 128,
	Wall: 255
};
function Li(e, t, n, r) {
	return {
		left: Math.max(0, Math.min(n - 1, Math.min(e.x, t.x))),
		top: Math.max(0, Math.min(r - 1, Math.min(e.y, t.y))),
		right: Math.max(0, Math.min(n - 1, Math.max(e.x, t.x))),
		bottom: Math.max(0, Math.min(r - 1, Math.max(e.y, t.y)))
	};
}
function Ri(e, t, n, r) {
	if (![
		e.x,
		e.y,
		t.x,
		t.y
	].every(Number.isFinite)) return null;
	let i = t.x - e.x, a = t.y - e.y, o = 0, s = 1;
	for (let [t, c] of [
		[-i, e.x],
		[i, n - 1 - e.x],
		[-a, e.y],
		[a, r - 1 - e.y]
	]) {
		if (t === 0) {
			if (c < 0) return null;
			continue;
		}
		let e = c / t;
		if (t < 0 ? o = Math.max(o, e) : s = Math.min(s, e), o > s) return null;
	}
	return [{
		x: Math.round(e.x + o * i),
		y: Math.round(e.y + o * a)
	}, {
		x: Math.round(e.x + s * i),
		y: Math.round(e.y + s * a)
	}];
}
var zi = class {
	data;
	roomData;
	width;
	height;
	past = [];
	future = [];
	stroke = /* @__PURE__ */ new Map();
	constructor(e, t, n, r = new Uint8Array(n.length)) {
		if (!Number.isInteger(e) || !Number.isInteger(t) || e <= 0 || t <= 0 || n.length !== e * t || r.length !== n.length) throw Error("Invalid map dimensions.");
		this.width = e, this.height = t, this.data = n.slice(), this.roomData = r.slice();
	}
	get cells() {
		return this.data;
	}
	get rooms() {
		return this.roomData;
	}
	get canUndo() {
		return this.past.length > 0;
	}
	get canRedo() {
		return this.future.length > 0;
	}
	fill(e, t) {
		for (let n = Math.max(0, e.top); n <= Math.min(this.height - 1, e.bottom); n++) for (let r = Math.max(0, e.left); r <= Math.min(this.width - 1, e.right); r++) this.paint(n * this.width + r, t);
	}
	line(e, t, n) {
		let r = Ri(e, t, this.width, this.height);
		if (!r) return;
		let { x: i, y: a } = r[0], { x: o, y: s } = r[1], c = Math.abs(o - i), l = -Math.abs(s - a), u = i < o ? 1 : -1, d = a < s ? 1 : -1, f = c + l;
		for (;;) {
			if (this.setCell(i, a, n), i === o && a === s) return;
			let e = 2 * f;
			e >= l && (f += l, i += u), e <= c && (f += c, a += d);
		}
	}
	commit() {
		let e = [...this.stroke.values()].filter((e) => e.before !== e.after);
		return this.stroke.clear(), e.length ? (this.past.push(e), this.past.length > 50 && this.past.shift(), this.future = [], !0) : !1;
	}
	cancel() {
		this.restore([...this.stroke.values()], "before"), this.stroke.clear();
	}
	undo() {
		let e = this.past.pop();
		return e ? (this.restore(e, "before"), this.future.push(e), !0) : !1;
	}
	redo() {
		let e = this.future.pop();
		return e ? (this.restore(e, "after"), this.past.push(e), !0) : !1;
	}
	paint(e, t) {
		typeof t == "number" ? this.setValue(e, t, "cells") : this.data[e] >= Ii.Unknown || !Number.isInteger(t.room) || t.room < 1 || t.room > 63 || this.setValue(e, t.room, "rooms");
	}
	setCell(e, t, n) {
		this.setValue(t * this.width + e, n, "cells");
	}
	setValue(e, t, n) {
		let r = n === "cells" ? this.data : this.roomData, i = r[e];
		if (i === t) return;
		let a = e + (n === "rooms" ? this.data.length : 0), o = this.stroke.get(a) ?? {
			layer: n,
			index: e,
			before: i,
			after: t
		};
		o.after = t, this.stroke.set(a, o), r[e] = t;
	}
	restore(e, t) {
		for (let n of e) {
			let e = n.layer === "cells" ? this.data : this.roomData;
			e[n.index] = n[t];
		}
	}
}, Bi = /* @__PURE__ */ Q("<button> </button>"), Vi = /* @__PURE__ */ Q("<label class=\"flex cursor-pointer items-center gap-2 text-sm\"><input class=\"radio radio-sm\" type=\"radio\"/> </label>"), Hi = /* @__PURE__ */ Q("<aside class=\"w-40 shrink-0 overflow-y-auto border-r border-base-300 bg-base-100 p-3\" aria-label=\"Rectangle fills\"><fieldset class=\"flex min-w-0 flex-col gap-3\"><legend class=\"mb-3 text-sm font-medium\">Fill</legend> <!> <input class=\"input input-sm w-full\" type=\"number\" aria-label=\"Room number\" min=\"1\" max=\"63\" step=\"1\" required=\"\"/></fieldset></aside>"), Ui = /* @__PURE__ */ Q("<span class=\"pointer-events-none absolute -translate-x-1/2 -translate-y-1/2 select-none rounded bg-base-100/85 px-2 py-0.5 text-xs font-medium\"> </span>"), Wi = /* @__PURE__ */ Q("<div class=\"pointer-events-none absolute border border-info bg-info/10\" aria-hidden=\"true\"></div>"), Gi = /* @__PURE__ */ Q("<div class=\"flex min-h-0 min-w-0 flex-1 flex-col\"><div class=\"flex shrink-0 flex-wrap items-center justify-between gap-2 border-b border-base-300 bg-base-100 px-4 py-3\"><div class=\"flex flex-wrap gap-2\"><div class=\"join\" role=\"group\" aria-label=\"Tools\"></div> <div class=\"join\" role=\"group\" aria-label=\"Edits\"><button class=\"btn btn-sm join-item\">Undo</button> <button class=\"btn btn-sm join-item\">Redo</button></div></div> <!></div> <div class=\"relative flex min-h-0 flex-1\"><!> <div role=\"application\" tabindex=\"0\"><canvas class=\"pointer-events-none absolute left-0 top-0 origin-top-left [image-rendering:pixelated]\" aria-label=\"Room map\"></canvas> <!> <!></div> <div class=\"join absolute bottom-4 right-4\" role=\"group\" aria-label=\"Zoom\"><button class=\"btn btn-sm join-item\" aria-label=\"Zoom out\">−</button> <button class=\"btn btn-sm join-item\">Fit</button> <button class=\"btn btn-sm join-item\" aria-label=\"Zoom in\">+</button></div></div></div>");
function Ki(e, t) {
	Le(t, !0);
	let n = [], r = {
		Pan: "Pan",
		Rectangle: "Rectangle"
	}, i = {
		Floor: "Floor",
		Wall: "Wall",
		Unknown: "Unknown",
		Room: "Room"
	}, a = /* @__PURE__ */ I(void 0), o = /* @__PURE__ */ I(void 0), s = /* @__PURE__ */ I(0), c = /* @__PURE__ */ I(0), l = /* @__PURE__ */ I(Vt({
		x: 0,
		y: 0,
		scale: 1
	})), u = /* @__PURE__ */ I(!1), f = /* @__PURE__ */ I(!1), p = null, m = {
		width: 0,
		height: 0
	}, h = null, g = /* @__PURE__ */ I(Vt(r.Pan)), _ = /* @__PURE__ */ I(Vt(i.Wall)), v = /* @__PURE__ */ I(1), y = /* @__PURE__ */ I(null), b = /* @__PURE__ */ I(0), x = /* @__PURE__ */ it(() => new zi(t.map.width, t.map.height, t.initialCells ?? t.map.cells, t.initialRooms ?? t.map.rooms)), S = /* @__PURE__ */ it(() => X(_) === i.Room ? typeof X(v) != "number" || !Number.isInteger(X(v)) || X(v) < 1 || X(v) > 63 ? null : { room: X(v) } : Ii[X(_)]), ee = /* @__PURE__ */ it(() => (X(b), {
		...t.map,
		cells: X(x).cells,
		rooms: X(x).rooms
	})), te = /* @__PURE__ */ it(() => Fi(X(ee))), C = /* @__PURE__ */ it(() => (X(b), X(x).canUndo)), ne = /* @__PURE__ */ it(() => (X(b), X(x).canRedo));
	dn(() => {
		if (!X(a)) return;
		let e = new ResizeObserver(([e]) => {
			e && (L(s, e.contentRect.width, !0), L(c, e.contentRect.height, !0));
		});
		return e.observe(X(a)), () => e.disconnect();
	}), dn(() => {
		if (!X(s) || !X(c)) return;
		let e = Zn(() => X(l));
		L(l, p === t.map ? {
			...e,
			x: e.x + (X(s) - m.width) / 2,
			y: e.y + (X(c) - m.height) / 2
		} : t.initialView ?? ji(X(s), X(c), {
			...t.map,
			cells: X(x).cells
		}), !0), p = t.map, m = {
			width: X(s),
			height: X(c)
		}, L(f, !0);
	}), dn(() => {
		let e = X(l), n = t.onview;
		if (!X(f) || !n) return;
		let r = setTimeout(() => n(e), 150);
		return () => clearTimeout(r);
	}), dn(() => {
		X(b);
		let e = X(o)?.getContext("2d");
		if (!e) return;
		let n = Pi(X(ee));
		e.putImageData(new ImageData(n, t.map.width, t.map.height), 0, 0);
	});
	function re() {
		L(l, ji(X(s), X(c), {
			...t.map,
			cells: X(x).cells
		}), !0);
	}
	function w(e) {
		L(l, Mi(X(l), e, X(s) / 2, X(c) / 2), !0);
	}
	function ie(e) {
		let t = (t) => {
			if (t.preventDefault(), h) return;
			let n = e.getBoundingClientRect(), r = t.deltaY * (t.deltaMode === 1 ? 16 : t.deltaMode === 2 ? X(c) : 1);
			L(l, Mi(X(l), Math.exp(-Math.max(-500, Math.min(500, r)) * .002), t.clientX - n.left, t.clientY - n.top), !0);
		};
		return e.addEventListener("wheel", t, { passive: !1 }), { destroy() {
			e.removeEventListener("wheel", t);
		} };
	}
	function ae(e) {
		let t = X(a).getBoundingClientRect();
		return {
			x: Math.floor((e.clientX - t.left - X(l).x) / X(l).scale),
			y: Math.floor((e.clientY - t.top - X(l).y) / X(l).scale)
		};
	}
	function oe() {
		Rt(b), t.onedit?.(X(x).cells, X(x).rooms);
	}
	function se() {
		!h && X(x).undo() && oe();
	}
	function ce() {
		!h && X(x).redo() && oe();
	}
	function le(e) {
		if (e.button !== 0 && e.button !== 1 || h || !X(a)) return;
		let n = e.button === 1 || e.altKey ? r.Pan : X(g), i = ae(e);
		n !== r.Pan && (i.x < 0 || i.y < 0 || i.x >= t.map.width || i.y >= t.map.height) || (n !== r.Rectangle || X(S) !== null) && (e.preventDefault(), X(a).focus(), X(a).setPointerCapture(e.pointerId), h = {
			id: e.pointerId,
			point: i,
			screen: {
				x: e.clientX,
				y: e.clientY
			},
			tool: n,
			fill: X(S)
		}, L(u, n === r.Pan), ue(i));
	}
	function ue(e) {
		h && h.tool !== r.Pan && h.fill !== null && (X(x).cancel(), L(y, Li(h.point, e, t.map.width, t.map.height), !0), X(x).fill(X(y), h.fill), Rt(b));
	}
	function de(e) {
		h && h.id === e.pointerId && (h.tool === r.Pan ? (L(l, {
			...X(l),
			x: X(l).x + e.clientX - h.screen.x,
			y: X(l).y + e.clientY - h.screen.y
		}, !0), h.screen = {
			x: e.clientX,
			y: e.clientY
		}) : h.tool === r.Rectangle && ue(ae(e)));
	}
	function fe(e) {
		if (h?.id !== e.pointerId) return;
		de(e);
		let t = h.tool;
		h = null, L(u, !1), L(y, null), t !== r.Pan && X(x).commit() && oe();
	}
	function T() {
		if (!h) return;
		let e = h.id;
		h.tool !== r.Pan && (X(x).cancel(), Rt(b)), L(y, null), h = null, L(u, !1), X(a)?.hasPointerCapture(e) && X(a).releasePointerCapture(e);
	}
	function E(e) {
		let t = e.key.toLowerCase();
		if (t === "escape") T();
		else if (h) return;
		else if ((e.ctrlKey || e.metaKey) && t === "z") e.shiftKey ? ce() : se();
		else if ((e.ctrlKey || e.metaKey) && t === "y") ce();
		else if (e.ctrlKey || e.metaKey) return;
		else if (e.key === "+" || e.key === "=") w(1.25);
		else if (e.key === "-") w(.8);
		else if (e.key === "0") re();
		else if (e.key === "ArrowLeft") L(l, {
			...X(l),
			x: X(l).x + 40
		}, !0);
		else if (e.key === "ArrowRight") L(l, {
			...X(l),
			x: X(l).x - 40
		}, !0);
		else if (e.key === "ArrowUp") L(l, {
			...X(l),
			y: X(l).y + 40
		}, !0);
		else if (e.key === "ArrowDown") L(l, {
			...X(l),
			y: X(l).y - 40
		}, !0);
		else return;
		e.preventDefault();
	}
	var pe = Gi(), me = z(pe), he = z(me), ge = z(he);
	Pr(ge, 21, () => Object.values(r), Ar, (e, t) => {
		var n = Bi();
		let r;
		var i = Qt(n, !0);
		V(() => {
			r = qr(n, 1, "btn btn-sm join-item", null, r, { "btn-primary": X(g) === X(t) }), si(n, "aria-pressed", X(g) === X(t)), br(i, X(t));
		}), Z("click", n, () => L(g, X(t), !0)), $(e, n);
	}), A(ge);
	var _e = B(ge, 2), D = z(_e), ve = B(D, 2);
	A(_e), A(he), Br(B(he, 2), () => t.controls ?? d), A(me);
	var O = B(me, 2), k = z(O), ye = (e) => {
		var t = Hi(), r = z(t), a = B(z(r), 2);
		Pr(a, 17, () => Object.values(i), Ar, (e, t) => {
			var r = Vi(), a = z(r);
			oi(a);
			var o, s = B(a);
			A(r), V(() => {
				o !== (o = X(t)) && (a.value = (a.__value = o) ?? ""), br(s, ` ${(X(t) === i.Room ? "Room ID" : X(t)) ?? ""}`);
			}), pi(n, [], a, () => (X(t), X(_)), (e) => L(_, e)), $(e, r);
		});
		var o = B(a, 2);
		oi(o), A(r), A(t), V(() => o.disabled = X(_) !== i.Room), di(o, () => X(v), (e) => L(v, e)), $(e, t);
	};
	Dr(k, (e) => {
		X(g) === r.Rectangle && e(ye);
	});
	var j = B(k, 2);
	let be;
	var xe = z(j);
	let Se;
	vi(xe, (e) => L(o, e), () => X(o));
	var Ce = B(xe, 2);
	Pr(Ce, 17, () => X(te), (e) => e.id, (e, t) => {
		var n = Ui();
		let r;
		var i = Qt(n);
		V(() => {
			r = Yr(n, "", r, {
				left: `${X(l).x + X(t).x * X(l).scale}px`,
				top: `${X(l).y + X(t).y * X(l).scale}px`
			}), br(i, `Room ${X(t).id ?? ""}`);
		}), $(e, n);
	});
	var we = B(Ce, 2), Te = (e) => {
		var t = Wi();
		let n;
		V(() => n = Yr(t, "", n, {
			left: `${X(l).x + X(y).left * X(l).scale}px`,
			top: `${X(l).y + X(y).top * X(l).scale}px`,
			width: `${(X(y).right - X(y).left + 1) * X(l).scale}px`,
			height: `${(X(y).bottom - X(y).top + 1) * X(l).scale}px`
		})), $(e, t);
	};
	Dr(we, (e) => {
		X(y) && e(Te);
	}), A(j), vi(j, (e) => L(a, e), () => X(a)), Vr(j, (e) => ie?.(e));
	var Ee = B(j, 2), De = z(Ee), Oe = B(De, 2), ke = B(Oe, 2);
	A(Ee), A(O), A(pe), V(() => {
		D.disabled = !X(C), ve.disabled = !X(ne), be = qr(j, 1, "relative min-h-0 min-w-0 flex-1 touch-none overflow-hidden outline-offset-[-2px]", null, be, {
			"cursor-grab": X(g) === r.Pan && !X(u),
			"cursor-grabbing": X(u),
			"cursor-crosshair": X(g) !== r.Pan && !X(u)
		}), si(j, "aria-label", `Map from ${t.source ?? ""}`), si(xe, "width", t.map.width), si(xe, "height", t.map.height), Se = Yr(xe, "", Se, { transform: `translate(${X(l).x ?? ""}px, ${X(l).y ?? ""}px) scale(${X(l).scale ?? ""})` });
	}), Z("click", D, se), Z("click", ve, ce), Z("pointerdown", j, le), Z("pointermove", j, de), Z("pointerup", j, fe), or("pointercancel", j, T), or("lostpointercapture", j, T), Z("keydown", j, E), Z("click", De, () => w(.8)), Z("click", Oe, re), Z("click", ke, () => w(1.25)), $(e, pe), Re();
}
sr([
	"click",
	"pointerdown",
	"pointermove",
	"pointerup",
	"keydown"
]);
//#endregion
//#region src/lib/session.ts
function qi() {
	return new Promise((e, t) => {
		let n = indexedDB.open("map-editor", 1);
		n.onupgradeneeded = () => n.result.createObjectStore("session"), n.onsuccess = () => e(n.result), n.onerror = () => t(n.error);
	});
}
function Ji(e) {
	return new Promise((t, n) => {
		e.oncomplete = () => t(), e.onerror = () => n(e.error), e.onabort = () => n(e.error);
	});
}
async function Yi() {
	let e = await qi();
	try {
		let t = e.transaction("session", "readonly"), n = t.objectStore("session"), r = n.get("map"), i = n.get("view"), a = n.get("draft");
		await Ji(t);
		let o = r.result;
		if (!o) return null;
		let s = i.result, c = s?.id === o.id ? s.view : void 0, l = a.result, u = l?.id === o.id && l.cells.length === o.map.cells.length ? l.cells : void 0, d = u && l?.rooms?.length === o.map.rooms.length ? l.rooms : void 0;
		return {
			...o,
			view: c,
			...u ? { draft: u } : {},
			...d ? { draftRooms: d } : {}
		};
	} finally {
		e.close();
	}
}
async function Xi(e) {
	let t = await qi();
	try {
		let n = t.transaction("session", "readwrite"), r = n.objectStore("session");
		r.put(e, "map"), r.delete("view"), r.delete("draft"), await Ji(n);
	} finally {
		t.close();
	}
}
async function Zi(e, t, n) {
	let r = t.slice(), i = n?.slice(), a = await qi();
	try {
		let t = a.transaction("session", "readwrite");
		t.objectStore("session").put({
			id: e,
			cells: r,
			rooms: i
		}, "draft"), await Ji(t);
	} finally {
		a.close();
	}
}
async function Qi(e, t) {
	let n = await qi();
	try {
		let r = n.transaction("session", "readwrite"), i = {
			x: t.x,
			y: t.y,
			scale: t.scale
		};
		r.objectStore("session").put({
			id: e,
			view: i
		}, "view"), await Ji(r);
	} finally {
		n.close();
	}
}
//#endregion
//#region src/App.svelte
var $i = /* @__PURE__ */ Q("<option> </option>"), ea = /* @__PURE__ */ Q("<label for=\"robot\" class=\"text-sm\">Robot</label> <select id=\"robot\" class=\"select select-sm w-48\"></select>", 1), ta = /* @__PURE__ */ Q("<label for=\"hostname\" class=\"text-sm\">Robot hostname</label> <input id=\"hostname\" class=\"input input-sm w-48\" placeholder=\"robot.local\" required=\"\"/>", 1), na = /* @__PURE__ */ Q("<div class=\"flex flex-wrap items-center gap-2\"><form class=\"flex flex-wrap items-center gap-2\"><!> <button class=\"btn btn-primary btn-sm\"> </button></form> <button class=\"btn btn-sm\"> </button></div>"), ra = /* @__PURE__ */ Q("<p class=\"alert alert-error m-4\" role=\"alert\"> </p>"), ia = /* @__PURE__ */ Q("<p class=\"px-4 py-2 text-sm\" role=\"status\"> </p>"), aa = /* @__PURE__ */ Q("<div class=\"flex min-h-0 flex-1 flex-col\"><div class=\"flex justify-end border-b border-base-300 bg-base-100 px-4 py-3\"><!></div> <p class=\"flex flex-1 items-center justify-center text-sm text-base-content/50\">No map loaded</p></div>"), oa = /* @__PURE__ */ Q("<div data-theme=\"dark\" class=\"flex h-dvh flex-col bg-base-200\"><!> <!> <main class=\"flex min-h-0 flex-1 justify-center\"><!></main> <dialog class=\"modal\" aria-labelledby=\"save-title\"><div class=\"modal-box\"><h2 id=\"save-title\" class=\"text-lg font-semibold\">Save changes?</h2> <p class=\"py-4\"> </p> <div class=\"modal-action\"><button class=\"btn btn-sm\">Cancel</button> <button class=\"btn btn-primary btn-sm\">Save and restart</button></div></div> <form method=\"dialog\" class=\"modal-backdrop\"><button aria-label=\"Close\">Close</button></form></dialog></div>");
function sa(e, t) {
	Le(t, !0);
	let n = Si(), r = /* @__PURE__ */ I(Vt([])), i = /* @__PURE__ */ I(""), a = /* @__PURE__ */ I(!1), o = /* @__PURE__ */ I(""), s = /* @__PURE__ */ I(null), c = /* @__PURE__ */ I(""), l = /* @__PURE__ */ it(() => n ? X(r).find((e) => e.id === X(c))?.name ?? X(c) : X(c)), u = /* @__PURE__ */ I(""), d = /* @__PURE__ */ I(void 0), f = /* @__PURE__ */ I(void 0), p = /* @__PURE__ */ I(void 0), m = 0, h = /* @__PURE__ */ I("idle"), g = /* @__PURE__ */ I(""), _ = /* @__PURE__ */ I(null), v = /* @__PURE__ */ I(void 0);
	yi(() => {
		if (!n) try {
			L(i, localStorage.getItem("robot-hostname") ?? "", !0);
		} catch {}
		(async () => {
			n && L(r, await Ci("entries"), !0);
			let e = await Yi().catch(() => null);
			m || (e && (!n || X(r).some((t) => t.id === e.source)) && (L(s, e.map, !0), L(c, e.source, !0), L(u, e.id, !0), L(d, e.view, !0), L(f, e.draft, !0), L(p, e.draftRooms, !0), L(i, X(i) || e.source, !0)), n && (L(i, X(i) || (X(r)[0]?.id ?? ""), !0), await y()));
		})().catch((e) => {
			L(o, e instanceof Error ? e.message : "Could not connect to Home Assistant.", !0);
		});
	});
	async function y() {
		if (!n || !X(i) || X(h) !== "idle") return;
		let e = X(i), t = await wi(e);
		if (t.state !== "saving") t.state === "error" && L(o, t.error ?? "Check the robot before retrying.", !0);
		else {
			L(h, "save");
			try {
				for (; t.state === "saving";) L(g, t.stage, !0), await new Promise((e) => setTimeout(e, 2e3)), t = await wi(e);
				if (t.state !== "done") throw Error(t.error ?? "Save interrupted. Check the robot before retrying.");
				await S(await Ti(e), e), L(g, "Saved. Robot restarted.");
			} catch (e) {
				L(o, e instanceof Error ? e.message : "Could not check save progress.", !0);
			} finally {
				L(h, "idle");
			}
		}
	}
	function b(e) {
		X(u) && Qi(X(u), e).catch(() => {});
	}
	function x(e, t) {
		L(_, {
			cells: e.slice(),
			rooms: t.slice()
		}, !0), X(u) && Zi(X(u), e, t).catch(() => {
			L(o, "Could not save edits in this browser.");
		});
	}
	async function S(e, t) {
		let n = {
			id: crypto.randomUUID(),
			source: t,
			map: e
		};
		await Xi(n).catch(() => {}), L(u, n.id, !0), L(d, void 0), L(f, void 0), L(p, void 0), L(_, null), L(s, e, !0), L(c, t, !0);
	}
	async function ee() {
		if (X(v)?.close(), X(s) && X(h) === "idle" && !X(a)) {
			L(h, "save"), m++, L(o, ""), L(g, "");
			try {
				await S(await Ei(X(c), X(s), X(_)?.cells ?? X(f) ?? X(s).cells, X(_)?.rooms ?? X(p) ?? X(s).rooms, (e) => {
					L(g, e.stage, !0);
				}), X(c)), L(g, "Saved. Robot restarted.");
			} catch (e) {
				L(o, e instanceof Error ? e.message : "Could not save the map.", !0);
			} finally {
				L(h, "idle");
			}
		}
	}
	async function te(e) {
		if (e.preventDefault(), X(a) || X(h) !== "idle") return;
		let t = X(i).trim();
		m++, L(a, !0), L(o, ""), L(g, "");
		try {
			if (!n) try {
				localStorage.setItem("robot-hostname", t);
			} catch {}
			await S(await Ti(t), t);
		} catch (e) {
			L(o, e instanceof Error ? e.message : "Map loading failed.", !0);
		} finally {
			L(a, !1);
		}
	}
	var C = oa();
	{
		let e = (e) => {
			var t = na(), c = z(t), l = z(c), u = (e) => {
				var t = ea(), n = B(Zt(t), 2);
				Pr(n, 21, () => X(r), Ar, (e, t) => {
					var n = $i(), r = Qt(n, !0), i = {};
					V(() => {
						br(r, X(t).name), i !== (i = X(t).id) && (n.value = (n.__value = i) ?? "");
					}), $(e, n);
				}), A(n), $r(n), V(() => n.disabled = X(a) || X(h) !== "idle"), Z("change", n, () => {
					y().catch((e) => {
						L(o, String(e), !0);
					});
				}), ei(n, () => X(i), (e) => L(i, e)), $(e, t);
			}, d = (e) => {
				var t = ta(), n = B(Zt(t), 2);
				oi(n), V(() => n.disabled = X(a) || X(h) !== "idle"), di(n, () => X(i), (e) => L(i, e)), $(e, t);
			};
			Dr(l, (e) => {
				n ? e(u) : e(d, -1);
			});
			var f = B(l, 2), p = Qt(f, !0);
			A(c);
			var m = B(c, 2), g = Qt(m, !0);
			A(t), V((e) => {
				f.disabled = e, br(p, X(a) ? "Loading…" : "Load map"), m.disabled = !X(s) || X(a) || X(h) !== "idle", br(g, X(h) === "save" ? "Saving…" : "Save");
			}, [() => X(a) || X(h) !== "idle" || !X(i).trim()]), or("submit", c, te), Z("click", m, () => X(v)?.showModal()), $(e, t);
		};
		var ne = z(C), re = (e) => {
			var t = ra(), n = Qt(t, !0);
			V(() => br(n, X(o))), $(e, t);
		};
		Dr(ne, (e) => {
			X(o) && e(re);
		});
		var w = B(ne, 2), ie = (e) => {
			var t = ia(), n = Qt(t, !0);
			V(() => br(n, X(g))), $(e, t);
		};
		Dr(w, (e) => {
			X(g) && e(ie);
		});
		var ae = B(w, 2), oe = z(ae), se = (t) => {
			var n = hr();
			kr(Zt(n), () => X(u), (t) => {
				Ki(t, {
					get controls() {
						return e;
					},
					get map() {
						return X(s);
					},
					get source() {
						return X(l);
					},
					get initialView() {
						return X(d);
					},
					get initialCells() {
						return X(f);
					},
					get initialRooms() {
						return X(p);
					},
					onview: b,
					onedit: x
				});
			}), $(t, n);
		}, ce = (t) => {
			var n = aa(), r = z(n), i = z(r);
			e(i), A(r), j(2), A(n), $(t, n);
		};
		Dr(oe, (e) => {
			X(s) ? e(se) : e(ce, -1);
		}), A(ae);
		var le = B(ae, 2), ue = z(le), de = B(z(ue), 2), fe = Qt(de), T = B(de, 2), E = z(T), pe = B(E, 2);
		A(T), A(ue), j(2), A(le), vi(le, (e) => L(v, e), () => X(v)), A(C), V(() => {
			si(ae, "aria-busy", X(a) || X(h) !== "idle"), ae.inert = X(h) !== "idle", br(fe, `Save changes to ${X(l) ?? ""} and restart the robot?`);
		}), Z("click", E, () => X(v)?.close()), Z("click", pe, ee);
	}
	$(e, C), Re();
}
sr(["change", "click"]);
//#endregion
//#region src/panel.ts
var ca = class extends HTMLElement {
	app;
	current;
	set hass(e) {
		this.current = e, xi(e), this.start();
	}
	connectedCallback() {
		this.start();
	}
	disconnectedCallback() {
		this.app && Tr(this.app), this.app = void 0, this.shadowRoot?.replaceChildren();
	}
	start() {
		if (!this.isConnected || !this.current || this.app) return;
		let e = this.shadowRoot ?? this.attachShadow({ mode: "open" }), t = document.createElement("link");
		t.rel = "stylesheet", t.href = new URL(
			/* @vite-ignore */
			"./panel.css",
			import.meta.url
		).href, e.append(t), this.app = xr(sa, { target: e });
	}
};
customElements.get("s7-map-editor") || customElements.define("s7-map-editor", ca);
//#endregion
