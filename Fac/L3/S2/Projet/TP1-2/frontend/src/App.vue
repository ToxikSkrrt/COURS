<script setup lang="ts">
import HelloWorld from './components/HelloWorld.vue'
import Gallery from './components/Gallery.vue'
import { ref } from 'vue';

const toggleHW = ref<boolean>(true);
const toggleGallery = ref<boolean>(false);

function toggleComponents() {
  toggleHW.value = !toggleHW.value;
  toggleGallery.value = !toggleGallery.value;
}
</script>

<template>
  <div>
    <img src="/home/thomas-alexandre/Documents/COURS/Fac/L3/S2/Projet/TP1-2/backend/src/main/resources/logo.jpg"
      class="logo" alt="logo" @click="toggleComponents()" />
  </div>

  <h1 class="titre">IMGine</h1>

  <div>
    <sub>Par Thomalex</sub>
  </div>

  <div>
    <sub>(Cliquez sur l'icône pour changer l'affichage)</sub>
  </div>

  <HelloWorld v-if="toggleHW" />

  <Gallery v-if="toggleGallery" />
</template>

<style scoped>
.titre {
  margin-bottom: 0;
  margin-top: 0;
}

.logo {
  height: 25em;
  padding: 1.5em;
  will-change: filter;
  transition: filter 300ms;
}

.logo:hover {
  filter: drop-shadow(0 0 2em #646cffaa);
}

.logo.vue:hover {
  filter: drop-shadow(0 0 2em #42b883aa);
}
</style>
