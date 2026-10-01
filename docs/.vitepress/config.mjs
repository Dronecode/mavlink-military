import { defineConfig } from "vitepress";
import { sidebar } from "./get_sidebar.js";

// Served from https://dronecode.github.io/mavlink-military/ until the project
// domain is live. CI sets DOCS_BASE and DOCS_HOSTNAME; once the custom domain
// is configured, drop DOCS_BASE (defaults to "/") and point DOCS_HOSTNAME at it.
const base = process.env.DOCS_BASE || "/";
// The sitemap resolves each page against the hostname, which drops the last
// path segment unless the hostname ends in a slash.
const hostname = (process.env.DOCS_HOSTNAME || "https://dronecode.github.io/mavlink-military").replace(/\/?$/, "/");
const repo = "https://github.com/Dronecode/mavlink-military";

export default defineConfig({
  title: "MAVLink-M",
  description: "MAVLink-M: an open MAVLink 2 dialect for coordination and situational awareness",
  base,
  lastUpdated: true,
  cleanUrls: false,
  sitemap: { hostname },
  srcExclude: ["**/_*.md", "scripts/**", "README.md"],

  head: [["link", { rel: "icon", href: `${base}favicon.svg`, type: "image/svg+xml" }]],

  // Render ```mermaid fences as <pre class="mermaid"> for the theme to draw in
  // the browser, instead of highlighting them as code. v-pre keeps Vue from
  // reading braces in a diagram as template syntax.
  markdown: {
    config(md) {
      const fence = md.renderer.rules.fence;
      md.renderer.rules.fence = (tokens, idx, options, env, self) => {
        const token = tokens[idx];
        if (token.info.trim() !== "mermaid") return fence(tokens, idx, options, env, self);
        return `<pre class="mermaid" tabindex="0" v-pre>${md.utils.escapeHtml(token.content)}</pre>\n`;
      };
    },
  },

  themeConfig: {
    siteTitle: "MAVLink-M",
    sidebar: sidebar("en"),
    externalLinkIcon: true,
    search: { provider: "local" },
    outline: { level: [2, 3] },

    // Serialized into the client bundle, so it can't close over `repo`.
    editLink: {
      pattern: ({ filePath, frontmatter }) =>
        "https://github.com/Dronecode/mavlink-military/edit/main/" +
        (frontmatter.editLink_path || `docs/${filePath}`),
      text: "Edit on GitHub",
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

    footer: {
      message: "Released under the MIT License.",
      copyright: "Copyright © Dronecode Foundation",
    },
  },
});
