<script setup>
import { withBase } from "vitepress";
</script>

<template>
  <a class="hero-dronecode" href="https://dronecode.org" title="A Dronecode Foundation project">
    <span>A project of the</span>
    <img class="light-only" :src="withBase('/site/dronecode_logo_light.svg')" alt="Dronecode Foundation" />
    <img class="dark-only" :src="withBase('/site/dronecode_logo_dark.svg')" alt="Dronecode Foundation" />
  </a>
</template>

<style scoped>
.hero-dronecode {
  display: inline-flex;
  align-items: center;
  gap: 4px;
  margin-top: 32px;
  color: var(--vp-c-text-2);
  font-size: 14px;
  text-decoration: none;
}
.hero-dronecode img {
  height: 60px;
  width: auto;
}
.dark-only,
:global(.dark) .light-only {
  display: none;
}
:global(.dark) .dark-only {
  display: block;
}
@media (max-width: 959px) {
  .hero-dronecode {
    justify-content: center;
  }
}
</style>
