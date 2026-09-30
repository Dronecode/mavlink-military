// Builds the VitePress sidebar from <lang>/SUMMARY.md, the same way the
// MAVLink devguide does. Each nested "- [Title](path.md)" list item becomes a
// sidebar entry; indentation defines nesting.

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
const itemRe = /^(\s*)[*-]\s+\[(.*?)\]\((.*?)\)/;

function toLink(url, lang) {
  if (/^https?:/.test(url)) return url;
  return `/${lang}/${url.replace(/\.md$/, ".html")}`;
}

export function sidebar(lang) {
  const file = path.resolve(here, "..", lang, "SUMMARY.md");
  const lines = fs.readFileSync(file, "utf-8").split("\n");

  const root = { items: [] };
  const stack = [{ indent: -1, node: root }];

  for (const line of lines) {
    const m = itemRe.exec(line);
    if (!m) continue;
    const indent = m[1].length;
    const entry = { text: m[2].replace(/\\([()_])/g, "$1"), link: toLink(m[3].trim(), lang) };

    while (stack[stack.length - 1].indent >= indent) stack.pop();
    const parent = stack[stack.length - 1].node;
    parent.items ??= [];
    if (parent !== root) parent.collapsed ??= true;
    parent.items.push(entry);
    stack.push({ indent, node: entry });
  }

  return root.items;
}
