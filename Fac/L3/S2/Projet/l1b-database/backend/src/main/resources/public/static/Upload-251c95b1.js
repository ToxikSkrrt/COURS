import{b as u}from"./http-api-e13d05e5.js";import{d as r,r as s,c,a,o as f}from"./index-fa8dbb4e.js";const d=a("h2",null,"Upload an image",-1),_=r({__name:"Upload",setup(p){const e=s();function t(){if(e.value!==null&&e.value!==void 0&&e.value.files!==null){const l=e.value.files[0];if(l===void 0)return;let n=new FormData;n.append("file",l),u.createImage(n).then(()=>{e.value!==void 0&&(e.value.value="")}).catch(i=>{console.log(i.message)})}}function o(l){e.value=l.target}return(l,n)=>(f(),c("div",null,[d,a("div",null,[a("input",{type:"file",id:"file",ref:"file",onChange:o},null,544)]),a("div",null,[a("button",{onClick:t},"Submit")])]))}});export{_ as default};