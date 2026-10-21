import { mount, unmount } from 'svelte'
import App from './App.svelte'
import { setHass, type HomeAssistant } from './lib/hass'
import './app.css'

class MapEditorPanel extends HTMLElement {
  private app: ReturnType<typeof mount> | undefined
  private current: HomeAssistant | undefined

  set hass(value: HomeAssistant) {
    this.current = value
    setHass(value)
    this.start()
  }

  connectedCallback() { this.start() }

  disconnectedCallback() {
    if (this.app) void unmount(this.app)
    this.app = undefined
    this.shadowRoot?.replaceChildren()
  }

  private start() {
    if (!this.isConnected || !this.current || this.app) return
    const root = this.shadowRoot ?? this.attachShadow({ mode: 'open' })
    const styles = document.createElement('link')
    styles.rel = 'stylesheet'
    styles.href = new URL(/* @vite-ignore */ './panel.css', import.meta.url).href
    root.append(styles)
    this.app = mount(App, { target: root })
  }
}

if (!customElements.get('s7-map-editor')) customElements.define('s7-map-editor', MapEditorPanel)
