<script setup lang="ts">
import { ref } from 'vue';
import router from "@/router";
import { getImageList, downloadFile, deleteImage } from '@/http-api';
import { ImageType } from '@/image';
import Image from './Image.vue';
import axios from 'axios';


const selectedId = ref(-1);
const imageList = ref<ImageType[]>([]);
getImageList(imageList);
</script>

<template>
  <div>
    <h1>Innovez dans l’image – Gérez, collez, découvrez.</h1>
    <h2>Choose an image</h2>
    <div>
      <select v-model="selectedId" >
        <option disabled value="">Select a picture</option>
        <option v-for="image in imageList" :value="image.id" :key="image.id">{{ image.name }}</option>
      </select>
    </div>
    <br>
    <div>
      <img v-if="selectedId != -1" :src="`images/${selectedId}`"/>
    </div>
    <br>
    <div>
      <button v-if="selectedId != -1" v-on:click="downloadFile(`images/${selectedId}`, imageList[imageList.findIndex((element) => element.id === selectedId)].name)">Save</button>
      <button v-if="selectedId != -1" v-on:click="deleteImage(selectedId)">Delete</button>
    </div>
  </div>
</template>

<style scoped>
</style>
