<script setup lang="ts">
import { ref } from 'vue';
// import axios from 'axios';
import { getImagesData } from '../http-api';

const donnees = ref<{ id: number; name: string }[]>([]);

function obtenirUrlImage(idImage: number): string {
  return `/images/${idImage}`;
}

getImagesData(donnees);
</script>

<template>
  <h2>Galerie de {{ donnees.length }} photos</h2>
  <div class="galerie">
    <a v-for="image in donnees" :key="image.id" :href="obtenirUrlImage(image.id)" target="_blank" class="element-galerie">
      <div class="cadre-photo">
        <img :src="obtenirUrlImage(image.id)" alt="Image" class="image-galerie">
      </div>
    </a>
  </div>
</template>

<style scoped>
.galerie {
  display: flex;
  flex-wrap: wrap;
  justify-content: space-between;
}

.element-galerie {
  margin: 10px;
  width: calc(33.33% - 20px);
  box-sizing: border-box;
}

.cadre-photo {
  border: 3px solid #42b883aa;
  border-radius: 8px;
  overflow: hidden;
  aspect-ratio: 1/1;
}

.image-galerie {
  width: 100%;
  height: 100%;
  object-fit: cover;
  border: 3px solid #42b883aa;
  border-radius: 8px;
  overflow: hidden;
  aspect-ratio: 1/1;
}
</style>
