import { defineConfig } from "vitepress";
import { sidebar } from "./get_sidebar.js";

// Served from https://dronecode.github.io/mavlink-military/ until the project
// domain is live. CI sets DOCS_BASE and DOCS_HOSTNAME; once the custom domain
// is configured, drop DOCS_BASE (defaults to "/") and point DOCS_HOSTNAME at it.
const base = process.env.DOCS_BASE || "/";
const hostname = process.env.DOCS_HOSTNAME || "https://dronecode.github.io/mavlink-military";
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
