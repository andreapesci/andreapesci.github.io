let d=[],g="Custom";const f="#7c3aed",y="portfolio-accent-color";function l(o){document.documentElement.style.setProperty("--color-accent",o)}function u(){try{return localStorage.getItem(y)||f}catch{return f}}function h(o){try{localStorage.setItem(y,o)}catch{}}async function E(){const o=document.getElementById("picker-trigger"),c=document.getElementById("picker-panel"),k=document.getElementById("panel-close"),a=document.getElementById("slot-grid"),i=document.getElementById("equipped-name");if(!o||!c||!a||!i)return;try{const t=await(await fetch("/data/ui-text.json")).json();d=t.accentPicker?.colors||[],g=t.accentPicker?.customName||"Custom"}catch{}const s=u();l(s),a.innerHTML=d.map(e=>`
      <button
        class="color-slot rarity-${e.rarity}${e.value===s?" equipped":""}"
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
    `).join("");const L=d.find(e=>e.value===s);i.textContent=L?.name||g;const p=o.querySelectorAll("circle");p.forEach(e=>e.style.fill=s);function m(){c.setAttribute("aria-hidden","true"),c.classList.remove("open")}function C(){c.classList.contains("open")?m():(c.setAttribute("aria-hidden","false"),c.classList.add("open"))}o.onclick=e=>{e.stopPropagation(),C()},k.onclick=()=>m(),window.__pickerOutsideClickBound||(window.__pickerOutsideClickBound=!0,document.addEventListener("click",e=>{const t=document.getElementById("accent-picker"),n=document.getElementById("picker-panel");t&&n&&n.classList.contains("open")&&!t.contains(e.target)&&(n.setAttribute("aria-hidden","true"),n.classList.remove("open"))})),a.onclick=e=>{const t=e.target.closest(".color-slot");if(!t)return;const n=t.dataset.color,v=t.dataset.name;a.querySelectorAll(".color-slot").forEach(r=>r.classList.remove("equipped")),t.classList.add("equipped"),t.classList.add("equipping"),setTimeout(()=>t.classList.remove("equipping"),600),l(n),h(n),i.textContent=v,p.forEach(r=>r.style.fill=n)}}l(u());E();document.addEventListener("astro:page-load",()=>{l(u()),E()});
