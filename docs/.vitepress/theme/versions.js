// The docs versions the site serves, and what a page shows about them. Each
// build knows only its own version (themeConfig.docsVersion: "main" or a
// release tag) and the site's root (themeConfig.docsRoot). The deploy writes
// versions.json at that root, so a version built long ago still lists the
// versions published after it. Pure functions, so node --test covers them.

const TAG = "v(0|[1-9]\\d*)\\.(0|[1-9]\\d*)\\.(0|[1-9]\\d*)";
const RELEASE = new RegExp(`^${TAG}$`);
const STATUSES = new Set(["latest", "outdated", "withdrawn"]);

// Each entry is main, at main/, or a release at <tag>/ with its status.
function validEntry(entry) {
  if (entry?.version === "main") return entry.path === "main/" && entry.status === "development";
  return (
    RELEASE.test(entry?.version) && entry.path === `${entry.version}/` && STATUSES.has(entry.status)
  );
}

// The list from versions.json, or null for anything else, so a page never
// shows a banner or a link from a malformed list.
export function parseVersions(data) {
  const list = data?.versions;
  return Array.isArray(list) && list.length > 0 && list.every(validEntry) ? list : null;
}

let pending;

// Fetches versions.json once per page load; null where there is none, as on
// a local preview or an offline copy of a version.
export function loadVersions(root, get = globalThis.fetch) {
  pending ??= Promise.resolve()
    .then(() => get(`${root}versions.json`, { cache: "no-cache" }))
    .then((response) => (response.ok ? response.json() : null))
    .then(parseVersions)
    .catch(() => null);
  return pending;
}

export function forgetVersions() {
  pending = undefined;
}

// What the banner above a page says: main is the development version, an
// older release is out of date, a withdrawn one is withdrawn, and the latest
// release shows none. Without a list, only main's banner shows. listed says
// whether main may add that no release exists yet.
export function banner(own, list) {
  const latest = list?.find((entry) => entry.status === "latest") ?? null;
  if (own === "main") return { kind: "development", latest, listed: list !== null };
  const status = list?.find((entry) => entry.version === own)?.status;
  return status === "outdated" || status === "withdrawn" ? { kind: status, latest, listed: false } : null;
}

const NOTE = { development: " (development)", latest: " (latest)", withdrawn: " (withdrawn)" };

// The page's path below its version's base, so a link to another version opens
// the same page there.
export function pagePath(routePath, base) {
  return routePath.startsWith(base) ? routePath.slice(base.length) : "";
}

// The version menu: every version the site serves, each linking the same page.
export function menuItems(own, list, root, page) {
  return (list ?? []).map((entry) => ({
    text: entry.version + (NOTE[entry.status] ?? ""),
    link: root + entry.path + page,
    current: entry.version === own,
  }));
}
