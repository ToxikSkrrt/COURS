import { createWebHashHistory, createRouter } from "vue-router";
import { RouteRecordRaw } from "vue-router";


const routes: Array<RouteRecordRaw> = [
  {
    path: "/",
    name: "home",
    component: () => import("./components/Home.vue"),
    props: true,
  },
  {
    path: "/gallery",
    name: "gallery",
    component: () => import("./components/Gallery.vue"),
    props: true
  },
  {
    path: "/image/:id",
    name: "imagePreview",
    component: () => import("./components/ImagePreview.vue"),
    props: ({ params }) => ({ id:Number(params.id) || 0 })
  },
  {
    path: "/upload",
    name: "upload",
    component: () => import("./components/Upload.vue"),
    props: true
  },
  {
    path: "/delete",
    name: "delete",
    component: () => import("./components/Delete.vue"),
    props: true
  },
  {
    path: "/download",
    name: "download",
    component: () => import("./components/Download.vue"),
    props: true
  },
  { 
    path: '/:pathMatch(.*)*', 
    component: () => import("./components/Home.vue"),
    name: 'NotFound'
  }
];

const router = createRouter({
  history: createWebHashHistory(),
  routes,
});

export default router;