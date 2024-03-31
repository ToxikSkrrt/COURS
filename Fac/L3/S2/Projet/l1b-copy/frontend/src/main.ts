import './style.css'
import { createApp } from 'vue'
import { createRouter, createWebHistory } from 'vue-router'
import App from './App.vue'
import Accueil from './components/Accueil.vue'
import Galerie from './components/Galerie.vue'
import Post from './components/Post.vue'

const routes = [
  { path: '/', component: Accueil },
  { path: '/galerie', component: Galerie },
  { path: '/post', component: Post },
]

const router = createRouter({
  history: createWebHistory(),
  routes,
})

createApp(App).use(router).mount('#app')
