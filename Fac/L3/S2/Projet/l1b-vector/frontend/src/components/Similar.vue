<script setup lang="ts">
import { ref } from 'vue';
import router from "@/router";
import { getImageList, downloadFile, deleteImage } from '@/http-api';
import { ImageType } from '@/image';
import Image from './Image.vue';
import axios from 'axios';


const selectedId = ref(-1);
const selectedHisto = ref(-1);
const imageList = ref<ImageType[]>([]);
getImageList(imageList);
</script>

<template>
  <div>
    <div>
      <select v-model="selectedId">
        <option disabled value="">Select a picture</option>
        <option v-for="image in imageList" :value="image.id" :key="image.id">{{ image.name }}</option>
      </select>
      <select v-model="selectedHisto">
        <option disabled value="">Select a histogram</option>
        <option :value="0">Histogram Hue/Saturation</option>
        <option :value="1">Histogram RGB</option>
      </select>
    </div>
    <br>
    <div>
      <img v-if="selectedId != -1" :src="`images/${selectedId}`" />
    </div>
  </div>
</template>

<style scoped></style>
