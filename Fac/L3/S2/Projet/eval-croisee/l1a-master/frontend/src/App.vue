<script setup lang="ts">
</script>

<template>
  <div id="app">
    <nav>
      <ul>
        <li>
          <router-link to="/">Home</router-link>
        </li>
        <li>
          <router-link to="/gallery">Gallery</router-link>
        </li>
        <li>
          <router-link to="/upload">Upload</router-link>
        </li>
        <li>
          <router-link to="/delete">Delete</router-link>
        </li>
        <li>
          <router-link to="/download">Download</router-link>
        </li>
      </ul>
    </nav>

    <div>
      <h1>PDL - L3</h1>
      <router-view />
    </div>
  </div>
</template>

<style>
:root {
  background-color: #242424;
}

#app {
  text-align: center;
  font-family: Arial, Helvetica, sans-serif;
  color: #fff;
}
ul {
  list-style-type: none;
  margin: 0;
  padding: 0;
  overflow: hidden;
  background-color: #333;
}
li {
  float: left;
}
li a {
  display: block;
  color: white;
  text-align: center;
  padding: 14px 16px;
  text-decoration: none;
}
.error {
  color: red;
  font-weight: bold;
  list-style-type: none;
  margin-top: 1em;
}
</style>
