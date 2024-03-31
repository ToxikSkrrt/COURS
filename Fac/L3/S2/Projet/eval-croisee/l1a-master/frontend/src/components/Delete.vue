<script setup lang="ts">
import { ref } from 'vue';
import { api, getImageList } from '@/http-api';
import { ImageType } from '@/image'


const selectedId = ref(-1);
const imageList = ref<ImageType[]>([]);
getImageList().then((data:ImageType[])=>imageList.value = data);




function deleteImage() {
    api.deleteImage(selectedId.value);
    }


</script>

<template>
  <div class="container">
    <div>
      <h2>Choose an Image to delete </h2>
      <hr/>
      <label>Image to delete</label>
      <select v-model="selectedId">
        <option v-for="image in imageList" :value="image.id" :key="image.id">{{ image.name }}</option>
      </select>      <br>
      <button v-on:click="deleteImage()">Delete</button>
    </div>
  </div>
</template>

