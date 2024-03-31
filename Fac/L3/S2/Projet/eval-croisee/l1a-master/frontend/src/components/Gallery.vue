<script setup lang="ts">
import { ref } from 'vue'
import { getImageList } from '@/http-api';
import { ImageType } from '@/image'
import Image from './Image.vue';
import router from "@/router";


const imageList = ref<ImageType[]>([]);
getImageList().then((data:ImageType[])=>imageList.value=data);

function onImageClicked(id:number){
  router.push({ name: 'imagePreview', params: { id:id } })
}

</script>
<template>
  <div>
    <h3>Gallery</h3>
    <a v-for="image in imageList" class="box" @click="onImageClicked(image.id)">
      <Image :id="image.id" />

    </a>
  </div>
</template>

<style>
.box Image{
  position: relative;
  top: 0;
  left: 0;
  width: 100%;
  height: 300px;
  object-fit: cover;


}
</style>
