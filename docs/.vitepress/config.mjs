import { execFileSync } from "node:child_process";
import { defineConfig } from "vitepress";
import { sidebar } from "./get_sidebar.js";
import { REPO as repo, pinSourceLink, siteLayout } from "./site.mjs";

// Served below the root of https://mavlink-m.dronecode.org/. CI sets DOCS_BASE
// and DOCS_HOSTNAME to the site's root and DOCS_VERSION to the version built
// (docs.yml); site.mjs places the build. The defaults build for the root.
const layout = siteLayout(process.env);
const { base, hostname } = layout;
const commit = execFileSync("git", ["rev-parse", "--short=12", "HEAD"], { encoding: "utf8" }).trim();

export default defineConfig({
  title: layout.release ? `MAVLink-M ${layout.version}` : "MAVLink-M",
  description: "MAVLink-M: an open MAVLink 2 dialect for military payloads and platforms",
  base,
  lastUpdated: true,
  cleanUrls: false,
  // One page at a time. The local search index takes its entries in the order
  // pages finish, so with pages built concurrently two builds of one commit
  // differ in that file's hash, and so in every page that loads it. Built in
  // page order, the same commit gives the same site, byte for byte.
  buildConcurrency: 1,
  sitemap: { hostname },
  srcExclude: ["**/_*.md", "scripts/**", "README.md"],

  head: [["link", { rel: "icon", href: `${base}favicon.svg`, type: "image/svg+xml" }]],

  // Render ```mermaid fences as <pre class="mermaid"> for the theme to draw in
  // the browser, instead of highlighting them as code. v-pre keeps Vue from
  // reading braces in a diagram as template syntax.
  markdown: {
    config(md) {
      const link = md.renderer.rules.link_open ?? ((tokens, idx, options, env, self) => self.renderToken(tokens, idx, options));
      md.renderer.rules.link_open = (tokens, idx, options, env, self) => {
        const href = tokens[idx].attrGet("href");
        if (href) tokens[idx].attrSet("href", pinSourceLink(href, layout.ref));
        return link(tokens, idx, options, env, self);
      };
      const fence = md.renderer.rules.fence;
      md.renderer.rules.fence = (tokens, idx, options, env, self) => {
        const token = tokens[idx];
        if (token.info.trim() !== "mermaid") return fence(tokens, idx, options, env, self);
        return `<pre class="mermaid" tabindex="0" v-pre>${md.utils.escapeHtml(token.content)}</pre>\n`;
      };
    },
  },

  themeConfig: {
    // The MAVLink logo stands in for the site title, as on mavlink.io. It is
    // the home link's only content, so its alt text names the site.
    logo: { light: "/site/mavlink_logo_light.svg", dark: "/site/mavlink_logo_dark.svg", alt: "MAVLink-M" },
    siteTitle: false,
    // Read by the version menu and banner (theme/versions.js): this build's
    // version, and the root where versions.json lists every version served.
    docsVersion: layout.version,
    docsRoot: layout.root,
    sidebar: sidebar("en"),
    externalLinkIcon: true,
    search: { provider: "local" },
    outline: { level: [2, 3] },

    // Serialized into the client bundle, so it can't close over `repo`. A
    // release's pages are fixed, so their edit links say they open main.
    editLink: {
      pattern: ({ filePath, frontmatter }) =>
        "https://github.com/Dronecode/mavlink-military/edit/main/" +
        (frontmatter.editLink_path || `docs/${filePath}`),
      text: layout.release ? "Edit this page on main" : "Edit on GitHub",
    },

    nav: [
      { text: "Messages", link: "/en/messages/military.md" },
      { text: "ID Allocation", link: "/en/guide/id_allocation.md" },
      {
        text: "Resources",
        items: [
          { text: "C library (generated)", link: "https://github.com/Dronecode/mavlink-military-c_library_v2" },
          { text: "Hardware demo", link: "https://github.com/Dronecode/nucleo-mavlink-m-demo" },
          { text: "MAVLink Guide", link: "https://mavlink.io" },
        ],
      },
    ],

    socialLinks: [{ icon: "github", link: repo }],

    // Every build carries the license, the notices of the code it bundles, and
    // its version record (scripts/write_site_files.py writes all three).
    footer: {
      message:
        `Released under the <a href="${base}LICENSE.txt">MIT License</a>. ` +
        `<a href="${base}THIRD-PARTY-NOTICES.txt">Third-party notices</a>. ` +
        `MAVLink-M ${layout.version}, commit <a href="${base}version.json">${commit}</a>.`,
      copyright: "Copyright © Dronecode Foundation",
    },
  },
});
