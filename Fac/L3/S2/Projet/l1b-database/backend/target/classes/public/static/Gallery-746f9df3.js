import{b as l}from"./http-api-e13d05e5.js";import{_ as n}from"./Image.vue_vue_type_script_setup_true_lang-93c4200b.js";import{d as _,r as c,c as o,a as r,t as i,F as d,b as p,o as s,f as m,_ as u}from"./index-a5927a2a.js";const f={class:"container"},g={class:"grid"},h=_({__name:"Gallery",setup(v){const a=c([]);return l.getImageList().then(e=>{a.value=e}).catch(e=>{console.log(e.message)}),(e,y)=>(s(),o("div",f,[r("h2",null,"Gallery of "+i(a.value.length)+" photos",1),r("div",g,[(s(!0),o(d,null,p(a.value,t=>(s(),m(n,{key:t.id,id:t.id},null,8,["id"]))),128))])]))}});const G=u(h,[["__scopeId","data-v-57957813"]]);export{G as default};