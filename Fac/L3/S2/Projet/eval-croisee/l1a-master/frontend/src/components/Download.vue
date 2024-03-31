<script setup lang="ts">
import { onMounted, ref } from 'vue';
import { api, getImageList } from '@/http-api';
import { ImageType } from '@/image'


const selectedId = ref(-1);
const imageList = ref<ImageType[]>([]);
getImageList().then((data:ImageType[])=>imageList.value = data);
var downloadElem:HTMLAnchorElement;

onMounted(()=>{
  downloadElem = document.getElementById("download") as HTMLAnchorElement; 
  downloadElem.setAttribute('download', 'image.jpg');
});

async function downloadImage(){
  if(downloadElem==null) return;
  const imageBlob = await api.getImage(selectedId.value);
  const url = window.URL.createObjectURL(imageBlob);
  downloadElem.href = url;
  window.URL.revokeObjectURL(url);
}


</script>

<template>
  <div class="container">
    <div>
      <h2>Choose an Image to download </h2>
      <hr/>
      <label>Image to download</label>
      <select v-model="selectedId">
        <option v-for="image in imageList" :value="image.id" :key="image.id">{{ image.name }}</option>
      </select>      <br>
      <a id="download">
        <button v-on:click="downloadImage()">Download</button>
      </a>
    </div>
  </div>
</template>