<script setup lang="ts">
import { ref } from 'vue'
import { getImagesData } from '../http.api';

const data = ref<{ name: string; id: number }[]>([]);

getImagesData(data);
</script>

<template>
  <h2>Galerie</h2>
  <div>
    <a v-for="d in data" :href="`/images/${d.id}`" target="_blank"><img class="imgGallery" :src="`/images/${d.id}`" /></a>
  </div>
</template>

<style scoped>
.imgGallery {
  max-height: 25em;
  margin-left: 5px;
  margin-right: 5px;
  margin-top: 2.5px;
  margin-bottom: 2.5px;
}

.imgGallery:hover {
  filter: drop-shadow(0 0 2em #646cffaa);
}

.imgGallery.vue:hover {
  filter: drop-shadow(0 0 2em #42b883aa);
}
</style>
