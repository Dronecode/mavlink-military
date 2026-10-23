// Where a docs build sits on the site, from the environment docs.yml sets.
// DOCS_BASE and DOCS_HOSTNAME give the site's root. DOCS_VERSION names the
// version the build documents: main, below the root at main/, or a release
// tag, below it at <tag>/. Unset, as in a local preview, the build sits at
// the root. Pure functions, so node --test covers them without VitePress.

export const REPO = "https://github.com/Dronecode/mavlink-military";
export const RELEASE_TAG = /^v(0|[1-9]\d*)\.(0|[1-9]\d*)\.(0|[1-9]\d*)$/;

const slash = (value) => value.replace(/\/?$/, "/");

export function siteLayout(env) {
  const version = env.DOCS_VERSION || "";
  const release = RELEASE_TAG.test(version);
  if (version && version !== "main" && !release) {
    throw new Error(`DOCS_VERSION ${version} is neither main nor a release tag such as v1.0.0`);
  }
  const below = version ? `${version}/` : "";
  const root = slash(env.DOCS_BASE || "/");
  return {
    version: version || "main",
    release,
    root,
    base: root + below,
    // The sitemap resolves each page against the hostname, which drops the
    // last path segment unless the hostname ends in a slash.
    hostname: slash(env.DOCS_HOSTNAME || "https://mavlink-m.dronecode.org") + below,
    // The git ref whose files a page's source links show.
    ref: release ? version : "main",
  };
}

// A release's pages link this repository's files at the release's tag, so a
// link from the reference to military.xml shows the definitions that release
// documents rather than main's.
export function pinSourceLink(href, ref) {
  const main = `${REPO}/blob/main/`;
  return ref !== "main" && href.startsWith(main) ? `${REPO}/blob/${ref}/${href.slice(main.length)}` : href;
}
