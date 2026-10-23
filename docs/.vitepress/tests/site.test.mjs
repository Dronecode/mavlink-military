// Tests for site.mjs. Run from docs/: npm run docs:test
import assert from "node:assert/strict";
import { test } from "node:test";
import { REPO, pinSourceLink, siteLayout } from "../site.mjs";

test("an unset version builds at the root, as a local preview does", () => {
  assert.deepEqual(siteLayout({}), {
    version: "main",
    release: false,
    root: "/",
    base: "/",
    hostname: "https://mavlink-m.dronecode.org/",
    ref: "main",
  });
});

test("main and releases sit below the root, with the sitemap under the same path", () => {
  const env = { DOCS_BASE: "/fork", DOCS_HOSTNAME: "https://example.org/fork" };
  assert.deepEqual(siteLayout({ ...env, DOCS_VERSION: "main" }), {
    version: "main",
    release: false,
    root: "/fork/",
    base: "/fork/main/",
    hostname: "https://example.org/fork/main/",
    ref: "main",
  });
  assert.deepEqual(siteLayout({ ...env, DOCS_VERSION: "v1.20.3" }), {
    version: "v1.20.3",
    release: true,
    root: "/fork/",
    base: "/fork/v1.20.3/",
    hostname: "https://example.org/fork/v1.20.3/",
    ref: "v1.20.3",
  });
});

test("a version that is neither main nor a release tag stops the build", () => {
  for (const version of ["1.0.0", "v1.0", "v01.0.0", "v1.0.0-rc.1", "v1.0.0+1", "develop"]) {
    assert.throws(() => siteLayout({ DOCS_VERSION: version }), /is neither main nor a release tag/);
  }
});

test("a release's links to this repository's files name its tag", () => {
  const link = `${REPO}/blob/main/military.xml`;
  assert.equal(pinSourceLink(link, "v1.2.3"), `${REPO}/blob/v1.2.3/military.xml`);
  assert.equal(pinSourceLink(link, "main"), link);
  for (const other of [`${REPO}/edit/main/x.md`, "https://example.org/blob/main/a", "/en/guide/"]) {
    assert.equal(pinSourceLink(other, "v1.2.3"), other);
  }
});
