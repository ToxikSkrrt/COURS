<script setup lang="ts">

import { ref, watch } from 'vue'
import { getImagesData } from '../http.api'
import axios, { AxiosResponse } from 'axios';

const data = ref<{ name: string; id: number }[]>([]);
const selected = ref<string>("");
const id = ref<number>();
const imageDataUrl = ref<string>("");

getImagesData(data);

// axios.get('/images')
//   .then(function (response) {
//     data.value = response.data;
//   })
//   .catch(function (error) {
//     console.log(error);
//   })

watch(selected, (newVal) => {
  const selectedImg = data.value.find(d => d.name === newVal);
  if (selectedImg) {
    id.value = selectedImg.id;
  }
  var imageUrl = `/images/${id.value}`;

  axios.get(imageUrl, { responseType: "blob" })
    .then(function (response: AxiosResponse) {
      const reader = new window.FileReader();
      reader.readAsDataURL(response.data);
      reader.onload = function () {
        imageDataUrl.value = reader.result as string;
      }
    });
});
</script>

<template>
  <h2>Page principale</h2>

  <select v-model="selected" class="choix">
    <option disabled value="">Sélectionnez une image</option>
    <option v-for="d in data">{{ d.name }}</option>
  </select>

  <div>
    <a :href="`/images/${id}`" target="_blank"><img class="selectImg" :src="imageDataUrl"></a>
  </div>

  <div class=" card" v-if="selected">
    <button type="button">Nom de l'image : {{ selected }}<br>
      ID de l'image : {{ id }}
    </button>
  </div>
</template>

<style scoped>
.selectImg {
  max-width: 1000px;
  max-height: 1000px;
  margin-top: 20px;
}

.selectImg:hover {
  filter: drop-shadow(0 0 2em #646cffaa);
}

.selectImg.vue:hover {
  filter: drop-shadow(0 0 2em #42b883aa);
}

.choix {
  margin-top: 5em;
}
</style>
