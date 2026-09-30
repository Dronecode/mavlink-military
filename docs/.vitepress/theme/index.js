import DefaultTheme from "vitepress/theme";
import { inBrowser } from "vitepress";
import { h, onMounted } from "vue";
import HeroDronecode from "./components/HeroDronecode.vue";
import "./style.css";

export default {
  extends: DefaultTheme,
  Layout: () =>
    h(DefaultTheme.Layout, null, {
      "home-hero-actions-after": () => h(HeroDronecode),
    }),
  setup() {
    // The generated message pages are long enough that the initial anchor jump
    // can land off target once fonts and layout settle. Re-scroll on first load
    // (same workaround as the MAVLink devguide).
    onMounted(() => {
      if (!inBrowser || !location.hash) return;
      const id = decodeURIComponent(location.hash.slice(1));
      const loaded =
        document.readyState === "complete"
          ? Promise.resolve()
          : new Promise((r) => window.addEventListener("load", r, { once: true }));
      Promise.all([document.fonts?.ready ?? Promise.resolve(), loaded]).then(() =>
        requestAnimationFrame(() => document.getElementById(id)?.scrollIntoView())
      );
    });
  },
};
