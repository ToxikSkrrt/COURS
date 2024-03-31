<script setup lang="ts">
import { ref } from 'vue';
import { api } from '@/http-api';

var file:File;
const input = ref<HTMLInputElement>();

function submitFile() {
  if(file==undefined)return;
  let formData = new FormData();
  formData.append('file', file);
  
  api.createImage(formData)
    .then( () => {if(input.value!=undefined)input.value.value='';})
    .catch(() => console.log('FAILURE!!'));
}

function handleFileUpload ( event:Event ) {
  input.value = (event.target as HTMLInputElement);
  if(!event || !input.value || !input.value.files) 
    return;
  file = input.value.files[0];
}

</script>

<template>
  <div class="container">
    <div>
      <h2>Single File</h2>
      <hr/>
      <label>File
        <input type="file" id="file" ref="file" @change="handleFileUpload( $event )"/>
      </label>
      <br>
      <button v-on:click="submitFile()">Submit</button>
    </div>
  </div>
</template>

