import{d as _,r as d,c as a,a as l,w as g,v as p,F as f,b as k,e as i,u as h,o as s,t as b}from"./index-8773ab14.js";import{a as r}from"./http-api-8d2c1dec.js";const I=l("h1",null,"Innovez dans l’image – Gérez, collez, découvrez.",-1),y=l("h2",null,"Choose an image",-1),C=l("option",{disabled:"",value:""},"Select a picture",-1),w=["value"],z=l("br",null,null,-1),L=["src"],S=l("br",null,null,-1),D=_({__name:"Home",setup($){const t=d(-1),u=d([]);c();function c(){r.getImageList().then(o=>{u.value=o}).catch(o=>{console.log(o.message)})}function v(o,n){const e=document.createElement("a");e.href=o,e.target="_blank",e.download=n,e.click()}return(o,n)=>(s(),a("div",null,[I,y,l("div",null,[g(l("select",{"onUpdate:modelValue":n[0]||(n[0]=e=>t.value=e)},[C,(s(!0),a(f,null,k(u.value,e=>(s(),a("option",{value:e.id,key:e.id},b(e.name),9,w))),128))],512),[[p,t.value]])]),z,l("div",null,[t.value!=-1?(s(),a("img",{key:0,src:`images/${t.value}`},null,8,L)):i("",!0)]),S,l("div",null,[t.value!=-1?(s(),a("button",{key:0,onClick:n[1]||(n[1]=e=>v(`images/${t.value}`,u.value[u.value.findIndex(m=>m.id===t.value)].name))},"Save")):i("",!0),t.value!=-1?(s(),a("button",{key:1,onClick:n[2]||(n[2]=e=>h(r).deleteImage(t.value))},"Delete")):i("",!0)])]))}});export{D as default};