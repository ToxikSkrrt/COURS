import{a as r}from"./http-api-8d2c1dec.js";import{d as s,c as i,o as c}from"./index-27d6217d.js";const d=["id"],g=s({__name:"Image",props:{id:{}},setup(l){const o=l;return r.getImage(o.id).then(e=>{const t=new window.FileReader;t.readAsDataURL(e),t.onload=()=>{const a=document.getElementById("gallery-"+o.id);if(a!==null){const n=document.createElement("img");a.appendChild(n),n!==null&&t.result&&n.setAttribute("src",t.result)}}}).catch(e=>{console.log(e.message)}),(e,t)=>(c(),i("figure",{id:"gallery-"+e.id},null,8,d))}});export{g as _};