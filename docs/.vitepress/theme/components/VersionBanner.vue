<script setup>
// A note above the page on every version but the latest release (the rules
// are in ../versions.js). main's note is in the built page; the others appear
// once the version list loads, since a release does not know what came after it.
import { computed, onMounted, ref } from "vue";
import { useData } from "vitepress";
import { banner, loadVersions } from "../versions.js";

const { theme } = useData();
const own = theme.value.docsVersion;
const root = theme.value.docsRoot;
const list = ref(null);
onMounted(async () => {
  list.value = await loadVersions(root);
});
const note = computed(() => banner(own, list.value));
</script>

<template>
  <div v-if="note" class="version-banner" :class="note.kind" role="note">
    <span v-if="note.kind === 'development'">
      This is the development version, built from main; it can change before the next release.
    </span>
    <span v-else-if="note.kind === 'withdrawn'">Release {{ own }} is withdrawn; do not build against it.</span>
    <span v-else>This is release {{ own }}, which is not the latest.</span>
    <a v-if="note.latest" :href="root + note.latest.path">Read {{ note.latest.version }}, the latest release.</a>
    <span v-else-if="note.listed">There is no release yet.</span>
  </div>
</template>

<style scoped>
.version-banner {
  display: flex;
  flex-wrap: wrap;
  gap: 4px 8px;
  margin: 0 0 24px;
  padding: 12px 16px;
  border-radius: 8px;
  font-size: 14px;
  line-height: 22px;
  color: var(--vp-c-text-1);
  background-color: var(--vp-c-warning-soft);
}
.version-banner.development {
  background-color: var(--vp-c-tip-soft);
}
.version-banner.withdrawn {
  background-color: var(--vp-c-danger-soft);
}
.version-banner a {
  font-weight: 500;
  color: var(--vp-c-brand-1);
  text-decoration: underline;
}
</style>
