let E=[],c=[{id:"classic",name:"Original Portfolio",preview:"Aa"},{id:"gears",name:"Share Tech Mono",preview:"Aa"}],q="Custom";const A="#a51d24",p="classic",C="portfolio-accent-color",S="portfolio-font-theme";function m(o){document.documentElement.style.setProperty("--color-accent",o)}function h(){try{return localStorage.getItem(C)||A}catch{return A}}function b(o){try{localStorage.setItem(C,o)}catch{}}function g(o){document.documentElement.dataset.fontTheme=o==="gears"?"gears":p}function k(){try{return localStorage.getItem(S)==="gears"?"gears":p}catch{return p}}function B(o){try{localStorage.setItem(S,o)}catch{}}async function T(){const o=document.getElementById("picker-trigger"),s=document.getElementById("picker-panel"),O=document.getElementById("panel-close"),r=document.getElementById("slot-grid"),f=document.getElementById("equipped-name"),l=document.getElementById("font-grid"),y=document.getElementById("font-equipped-name");if(!o||!s||!r||!f||!l||!y)return;try{const t=await(await fetch("/data/ui-text.json",{cache:"no-cache"})).json();E=t.accentPicker?.colors||[],q=t.accentPicker?.customName||"Custom",c=t.accentPicker?.fontPicker?.options||c}catch{}const d=h(),u=k();m(d),g(u),r.innerHTML=E.map(e=>`
      <button
        class="color-slot rarity-${e.rarity}${e.value===d?" equipped":""}"
        data-color="${e.value}"
        data-name="${e.name}"
        data-rarity="${e.rarity}"
        aria-label="Equip ${e.name}"
        title="${e.name}"
      >
        <span class="slot-fill" style="background: ${e.value};"></span>
        <span class="slot-frame"></span>
        <span class="equip-flash"></span>
      </button>
    `).join("");const I=E.find(e=>e.value===d);f.textContent=I?.name||q,l.innerHTML=c.map(e=>`
      <button
        type="button"
        class="font-choice${e.id===u?" equipped":""}"
        data-font-theme="${e.id}"
        aria-label="Equip ${e.name}"
        aria-pressed="${e.id===u}"
      >
        <span class="font-preview">${e.preview}</span>
        <span class="font-option-name">${e.name}</span>
      </button>
    `).join(""),y.textContent=c.find(e=>e.id===u)?.name||c[0].name;const L=o.querySelectorAll("circle");L.forEach(e=>e.style.fill=d);function v(){s.setAttribute("aria-hidden","true"),s.classList.remove("open")}function $(){s.classList.contains("open")?v():(s.setAttribute("aria-hidden","false"),s.classList.add("open"))}o.onclick=e=>{e.stopPropagation(),$()},O.onclick=()=>v(),window.__pickerOutsideClickBound||(window.__pickerOutsideClickBound=!0,document.addEventListener("click",e=>{const t=document.getElementById("accent-picker"),n=document.getElementById("picker-panel");t&&n&&n.classList.contains("open")&&!t.contains(e.target)&&(n.setAttribute("aria-hidden","true"),n.classList.remove("open"))}),document.addEventListener("keydown",e=>{if(e.key==="Escape"){const t=document.getElementById("picker-panel");t&&t.classList.contains("open")&&(t.setAttribute("aria-hidden","true"),t.classList.remove("open"))}})),r.onclick=e=>{const t=e.target.closest(".color-slot");if(!t)return;const n=t.dataset.color,a=t.dataset.name;r.querySelectorAll(".color-slot").forEach(i=>i.classList.remove("equipped")),t.classList.add("equipped"),t.classList.add("equipping"),setTimeout(()=>t.classList.remove("equipping"),600),m(n),b(n),f.textContent=a,L.forEach(i=>i.style.fill=n)},l.onclick=e=>{const t=e.target.closest(".font-choice");if(!t)return;const n=t.dataset.fontTheme==="gears"?"gears":p;l.querySelectorAll(".font-choice").forEach(a=>{const i=a===t;a.classList.toggle("equipped",i),a.setAttribute("aria-pressed",String(i))}),g(n),B(n),y.textContent=c.find(a=>a.id===n)?.name||c[0].name}}m(h());g(k());T();document.addEventListener("astro:page-load",()=>{m(h()),g(k()),T()});
