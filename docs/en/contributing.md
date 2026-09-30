# Contributing

The `53000-53099` allocation is active for this dialect, and message IDs are
stable once assigned.

## Proposing a message or change

Open a pull request against
[`military.xml`](https://github.com/Dronecode/mavlink-military/blob/main/military.xml).
Keep additions within the [Scope and Boundaries](about/scope.md), and allocate
new IDs from the reserved shared blocks listed in
[Message ID Allocation](guide/id_allocation.md) (update `IDMAPPING.md` in the
same PR).

CI regenerates the C headers on every pull request that touches the XML, so a
schema error shows up before review.

## Improving these docs

The site is built with [VitePress](https://vitepress.dev) from the `docs/`
directory. Hand-written pages live in `docs/en/`, and the sidebar is defined in
`docs/en/SUMMARY.md`. The message reference pages are generated from
`military.xml` and are not checked in.

```sh
cd docs
pip install beautifulsoup4 lxml
npm install
npm run docs:messages   # generate the message reference from military.xml
npm run docs:dev        # local preview at http://localhost:5173
```
