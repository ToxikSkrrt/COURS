<script setup lang="ts">
import { onMounted,ref } from 'vue';
import { ImageDisplay } from "@/display";
import { ImageType } from '@/image';
import { getImageList } from '@/http-api';


const props = defineProps<{ id: number }>()
const info = ref<ImageType>();

onMounted(()=>{

    getImageList().then((images:ImageType[]) => {
        const previewElt = document.getElementById("preview-"+props.id);
        const display = new ImageDisplay(document.createElement("img"), images[props.id-1]);
        info.value = images[props.id-1];
        previewElt?.appendChild(display.getElement());
    })

})

</script>

<template>
    <p>name: {{ info?.name }}</p>
    <p>size: {{ info?.size }}</p>
    <p>type: {{ info?.type }}</p>
    <figure :id="'preview-'+props.id"></figure>  
</template>