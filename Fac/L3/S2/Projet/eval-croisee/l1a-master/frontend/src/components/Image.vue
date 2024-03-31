<script setup lang="ts">
import { onMounted } from 'vue';
import { ImageDisplay } from "@/display";


const props = defineProps<{ id: number }>()

onMounted(()=>{
  const galleryElt = document.getElementById("gallery-"+props.id);
  const display = new ImageDisplay(document.createElement("img"), {name:"",id:props.id,type:"",size:""});
  galleryElt?.appendChild(display.getElement());
})

</script>

<template>
  <figure :id="'gallery-'+id"></figure>  
  
</template>