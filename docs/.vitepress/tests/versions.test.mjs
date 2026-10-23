// Tests for theme/versions.js. Run from docs/: npm run docs:test
import assert from "node:assert/strict";
import { beforeEach, test } from "node:test";
import {
  banner,
  forgetVersions,
  loadVersions,
  menuItems,
  pagePath,
  parseVersions,
} from "../theme/versions.js";

const MAIN = { version: "main", path: "main/", status: "development" };
const LATEST = { version: "v1.1.0", path: "v1.1.0/", status: "latest" };
const OLD = { version: "v1.0.0", path: "v1.0.0/", status: "outdated" };
const PULLED = { version: "v0.9.0", path: "v0.9.0/", status: "withdrawn" };
const LIST = [MAIN, LATEST, OLD, PULLED];

const reply = (body, ok = true) => async () => ({ ok, json: async () => body });

beforeEach(forgetVersions);

test("a well-formed list is kept", () => {
  assert.equal(parseVersions({ versions: LIST }), LIST);
  assert.deepEqual(parseVersions({ versions: [MAIN] }), [MAIN]);
});

test("anything but a well-formed list is dropped", () => {
  for (const data of [
    null,
    "text",
    {},
    { versions: [] },
    { versions: "main" },
    { versions: [{ ...MAIN, path: "" }] },
    { versions: [{ ...MAIN, status: "latest" }] },
    { versions: [MAIN, { ...LATEST, path: "../elsewhere/" }] },
    { versions: [MAIN, { ...LATEST, status: "candidate" }] },
    { versions: [MAIN, { ...LATEST, version: "v1.1.0-rc.1", path: "v1.1.0-rc.1/" }] },
    { versions: [MAIN, null] },
  ]) {
    assert.equal(parseVersions(data), null, JSON.stringify(data));
  }
});

test("the list loads once per page, from the site's root", async () => {
  const calls = [];
  const get = async (url, options) => {
    calls.push([url, options]);
    return { ok: true, json: async () => ({ versions: LIST }) };
  };
  assert.deepEqual(await loadVersions("/root/", get), LIST);
  assert.deepEqual(await loadVersions("/root/", get), LIST);
  assert.deepEqual(calls, [["/root/versions.json", { cache: "no-cache" }]]);
});

test("a missing, failing or malformed list loads as none", async () => {
  for (const get of [
    reply({ versions: LIST }, false),
    reply({ versions: "bad" }),
    async () => {
      throw new TypeError("offline");
    },
    () => {
      throw new TypeError("no fetch");
    },
  ]) {
    forgetVersions();
    assert.equal(await loadVersions("/", get), null);
  }
});

test("main always says it is the development version", () => {
  assert.deepEqual(banner("main", LIST), { kind: "development", latest: LATEST, listed: true });
  assert.deepEqual(banner("main", [MAIN]), { kind: "development", latest: null, listed: true });
  assert.deepEqual(banner("main", null), { kind: "development", latest: null, listed: false });
});

test("only older and withdrawn releases carry a banner", () => {
  assert.equal(banner("v1.1.0", LIST), null);
  assert.deepEqual(banner("v1.0.0", LIST), { kind: "outdated", latest: LATEST, listed: false });
  assert.deepEqual(banner("v0.9.0", LIST), { kind: "withdrawn", latest: LATEST, listed: false });
  assert.deepEqual(banner("v0.9.0", [MAIN, PULLED]), { kind: "withdrawn", latest: null, listed: false });
  assert.equal(banner("v2.0.0", LIST), null);
  assert.equal(banner("v1.0.0", null), null);
});

test("a page's path is taken below its version's base", () => {
  assert.equal(pagePath("/v1.0.0/en/about/status.html", "/v1.0.0/"), "en/about/status.html");
  assert.equal(pagePath("/v1.0.0/", "/v1.0.0/"), "");
  assert.equal(pagePath("/elsewhere/page.html", "/v1.0.0/"), "");
});

test("the menu opens the same page in every version", () => {
  assert.deepEqual(menuItems("v1.0.0", LIST, "/", "en/guide/"), [
    { text: "main (development)", link: "/main/en/guide/", current: false },
    { text: "v1.1.0 (latest)", link: "/v1.1.0/en/guide/", current: false },
    { text: "v1.0.0", link: "/v1.0.0/en/guide/", current: true },
    { text: "v0.9.0 (withdrawn)", link: "/v0.9.0/en/guide/", current: false },
  ]);
  assert.deepEqual(menuItems("main", null, "/", "en/"), []);
});
