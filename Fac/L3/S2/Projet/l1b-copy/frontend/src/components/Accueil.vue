<script setup lang="ts">
import { ref } from 'vue';
import axios from 'axios';
import { getImagesData } from '../http-api';

// const reponse = ref('');
const data = ref<{ id: number; name: string }[]>([]);
const imageSelectionnee = ref<number | null>(null);
const sourceImage = ref<string | null>(null);

function obtenirNomImage(imageId: number | null): string {
  const imageSelectionnee = data.value.find(image => image.id === imageId);
  return imageSelectionnee ? imageSelectionnee.name : '';
}

async function chargerImage() {
  if (imageSelectionnee.value !== null) {
    try {
      const reponseServeur = await axios.get(`/images/${imageSelectionnee.value}`, { responseType: 'blob' });
      const lecteur = new FileReader();
      lecteur.readAsDataURL(reponseServeur.data);
      lecteur.onload = function () {
        const imageUrl = lecteur.result as string;
        sourceImage.value = imageUrl;
      };
    } catch (error) {
      console.error(error);
    }
  }
}

getImagesData(data);
</script>

<template>
  <h2>Accueil</h2>
  <div>
    <div class="card">
      <p>Bienvenue sur <b>GestIMG</b>, le site numéro 1</p>
      <p>Pour la Gestion et le traitement des images</p>
    </div>

    <label for="Select">Sélectionnez une image : </label>
    <select id="Select" v-model="imageSelectionnee" @change="chargerImage">
      <option disabled value="">Select an image</option>
      <option v-for="image in data" :key="image.id" :value="image.id">{{ obtenirNomImage(imageSelectionnee) }}</option>
    </select>

    <div v-if="imageSelectionnee !== null">
      <p>Image [{{ imageSelectionnee }}] : {{ obtenirNomImage(imageSelectionnee) }}</p>
      <div class="conteneur-image" v-if="sourceImage">
        <div class="cadre-photo">
          <img :src="sourceImage" alt="Image sélectionnée" class="image-selectionnee">
        </div>
      </div>
    </div>

    <div>
      <br>
      <router-link to="/galerie">
        <button>Galerie</button>
      </router-link>
      <router-link to="/post">
        <button>Post</button>
      </router-link>
    </div>
  </div>
</template>

<style scoped>
.image-selectionnee {
  width: 100%;
  height: 100%;
  object-fit: cover;
}

.cadre-photo {
  border: 3px solid #42b883aa;
  border-radius: 8px;
  overflow: hidden;
  aspect-ratio: 1/1;
  margin-top: 10px;
}

.conteneur-image {
  width: 100%;
  max-width: 400px;
  margin: 0 auto;
  overflow: hidden;
}
</style>
