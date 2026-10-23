import DefaultTheme from "vitepress/theme";
import { getScrollOffset, inBrowser, onContentUpdated, useData, useRoute } from "vitepress";
import { h, nextTick, onMounted, watch } from "vue";
import HeroDronecode from "./components/HeroDronecode.vue";
import VersionBanner from "./components/VersionBanner.vue";
import VersionMenu from "./components/VersionMenu.vue";
import "./style.css";

// Mermaid is large, so it is imported only on pages that have a diagram. Each
// block keeps its source in data-source, because mermaid replaces the text with
// an SVG, and the source is needed to redraw the diagram for the other theme.
// Blocks are drawn one at a time, yielding in between, so the page stays
// responsive and keeps its height during a redraw. Returns true once every
// block is drawn, and false if there are none or the page changed meanwhile.
let mermaidModule;
async function renderMermaid(dark) {
  const blocks = [...document.querySelectorAll("pre.mermaid")];
  if (blocks.length === 0) return false;
  mermaidModule ??= import("mermaid").then((m) => m.default);
  const mermaid = await mermaidModule;
  // Draw at natural size, scrolling sideways when wider than the column, rather
  // than shrinking wide diagrams to fit. Text isn't wrapped, so names and values
  // are drawn exactly as written.
  mermaid.initialize({
    startOnLoad: false,
    theme: dark ? "dark" : "default",
    flowchart: { useMaxWidth: false },
    sequence: { useMaxWidth: false },
  });
  for (const block of blocks) {
    if (!block.isConnected) return false; // the page changed; the next run draws it
    if (block.dataset.source === undefined) block.dataset.source = block.textContent;
    else block.textContent = block.dataset.source;
    block.removeAttribute("data-processed");
    await mermaid.run({ nodes: [block], suppressErrors: true });
    await new Promise((resolve) => setTimeout(resolve));
  }
  return true;
}

// The router scrolls to a #hash target, or on back and forward to the saved
// offset, before the diagrams are drawn, and drawing them changes the height of
// the page, so scroll there again once they are drawn. The saved offset is kept
// with its path, so it is only used for the page it was saved for. A reader who
// scrolls, clicks or presses a key while the diagrams are drawn stays put.
let savedScroll;
let readerMoved = false;
if (inBrowser) {
  window.addEventListener("popstate", (e) => {
    savedScroll = { path: location.pathname, y: e.state?.scrollPosition };
  });
  for (const type of ["wheel", "touchmove", "keydown", "pointerdown"]) {
    window.addEventListener(type, () => (readerMoved = true), { capture: true, passive: true });
  }
}
function rescroll(saved) {
  const id = decodeURIComponent(location.hash.slice(1));
  const target = id && document.getElementById(id);
  if (saved) {
    window.scrollTo(0, saved);
  } else if (target) {
    const padding = parseInt(getComputedStyle(target).paddingTop, 10);
    window.scrollTo(0, scrollY + target.getBoundingClientRect().top - getScrollOffset() + padding);
  }
}

export default {
  extends: DefaultTheme,
  Layout: () =>
    h(DefaultTheme.Layout, null, {
      "home-hero-actions-after": () => h(HeroDronecode),
      // Which version of the docs this is, and the others the site serves.
      "home-hero-info-before": () => h(VersionBanner),
      "doc-before": () => h(VersionBanner),
      "nav-bar-content-after": () => h(VersionMenu),
      "nav-screen-content-after": () => h(VersionMenu, { screen: true }),
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

    // Draw diagrams whenever the page content changes (first load, each page
    // change, and each save in docs:dev) and again when the colour theme
    // changes. Runs are queued so two never overlap, and requests made while a
    // run waits to start join that run, since a page change sends several.
    const { isDark } = useData();
    const route = useRoute();
    let queue = Promise.resolve();
    let waiting = false;
    let drawnPath;
    const draw = () => {
      if (!inBrowser || waiting) return;
      waiting = true;
      queue = queue
        .then(() => nextTick())
        .then(async () => {
          waiting = false;
          // Only the first draw of a page scrolls, not a redraw after an edit
          // or a theme change.
          const newPage = route.path !== drawnPath;
          drawnPath = route.path;
          const saved = savedScroll?.path === location.pathname ? savedScroll.y : undefined;
          savedScroll = undefined;
          if (newPage) readerMoved = false;
          if ((await renderMermaid(isDark.value)) && newPage && !readerMoved) rescroll(saved);
        })
        .catch((error) => console.error(error));
    };
    onContentUpdated(draw);
    watch(isDark, draw);
  },
};
