<script setup>
// The version this page belongs to, in the nav bar, and once the version list
// loads, a menu of every version the site serves. Each entry opens the same
// page in that version, as far as it has one.
import { computed, onMounted, ref } from "vue";
import { useData, useRoute } from "vitepress";
import { loadVersions, menuItems, pagePath } from "../versions.js";

defineProps({ screen: Boolean });

const { site, theme } = useData();
const route = useRoute();
const own = theme.value.docsVersion;
const root = theme.value.docsRoot;
const list = ref(null);
onMounted(async () => {
  list.value = await loadVersions(root);
});
const items = computed(() => menuItems(own, list.value, root, pagePath(route.path, site.value.base)));
</script>

<template>
  <details v-if="items.length" class="version-menu" :class="{ screen }">
    <summary :aria-label="`Version ${own}, choose another version`">{{ own }}</summary>
    <ul>
      <li v-for="item in items" :key="item.link">
        <a :href="item.link" :aria-current="item.current ? 'page' : undefined">{{ item.text }}</a>
      </li>
    </ul>
  </details>
  <span v-else class="version-menu" :class="{ screen }">{{ own }}</span>
</template>

<style scoped>
.version-menu {
  position: relative;
  display: flex;
  align-items: center;
  margin-left: 12px;
  font-size: 14px;
  font-weight: 500;
  color: var(--vp-c-text-2);
}
.version-menu summary {
  cursor: pointer;
  color: var(--vp-c-text-1);
}
.version-menu ul {
  position: absolute;
  top: 100%;
  right: 0;
  z-index: 100;
  min-width: 200px;
  margin: 8px 0 0;
  padding: 8px 0;
  list-style: none;
  border: 1px solid var(--vp-c-divider);
  border-radius: 12px;
  background-color: var(--vp-c-bg-elv);
  box-shadow: var(--vp-shadow-3);
}
.version-menu li a {
  display: block;
  padding: 4px 16px;
  white-space: nowrap;
  color: var(--vp-c-text-1);
}
.version-menu li a:hover,
.version-menu li a[aria-current="page"] {
  color: var(--vp-c-brand-1);
}
/* In the nav bar on wide screens; on narrow ones, in the menu screen instead. */
.version-menu:not(.screen) {
  display: none;
}
@media (min-width: 768px) {
  .version-menu:not(.screen) {
    display: flex;
  }
  .version-menu.screen {
    display: none;
  }
}
.version-menu.screen {
  margin: 24px 0 0;
}
.version-menu.screen ul {
  position: static;
  box-shadow: none;
}
</style>
