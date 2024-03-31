<script setup lang="ts">
import { ref } from 'vue';
import { api, getImagesData } from '../http-api';

const data = ref<{ id: number; name: string }[]>([]);

const target = ref<HTMLInputElement>();

function submitFile() {
  if (target.value !== null && target.value !== undefined && target.value.files !== null) {
    const file = target.value.files[0];
    if (file === undefined)
      return;
    let formData = new FormData();
    formData.append("file", file);
    api.createImage(formData).then(() => {
      if (target.value !== undefined)
        target.value.value = '';
    }).catch((e: { message: any; }) => {
      console.log(e.message);
    });
  }
}

function handleFileUpload(event: Event) {
  target.value = (event.target as HTMLInputElement);
}

getImagesData(data);
</script>

<template>
  <h2>Upload tes photos</h2>
  <h4>En cours de conception</h4>

  <div>
    <h3>Upload an image</h3>
    <div>
      <input type="file" id="file" ref="file" @change="handleFileUpload" />
    </div>
    <div>
      <button @click="submitFile">Submit</button>
    </div>
  </div>
</template>

<style scoped></style>

