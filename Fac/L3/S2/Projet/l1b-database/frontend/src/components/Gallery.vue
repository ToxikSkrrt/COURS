<script setup lang="ts">
import { ref } from 'vue'
import { api, getImageList } from '@/http-api';
import { ImageType } from '@/image'
import Image from './Image.vue';

const imageList = ref<ImageType[]>([]);

getImageList(imageList);
</script>

<template>
  <div class="container">
    <h2>Gallery of {{ imageList.length }} photos</h2>
    <div class="grid">
      <Image v-for="image in imageList" :key="image.id" :id="image.id" />
    </div>
  </div>
</template>

<style scoped>
.container {
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  align-items: center;
  width: 90%;
  margin: auto;
}

.grid {
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  align-items: center;
}

.grid img {
  width: 30%; 
  height: auto;
  margin: 10px;
  border-radius: 5%;
}
</style>
