let u=[],i={engine:null,genre:null,status:null},h={};async function $(){const a=document.getElementById("project-grid"),e=document.getElementById("filter-bar");if(a){i={engine:null,genre:null,status:null},m=!1;try{const[l,c]=await Promise.all([fetch("/data/projects/_index.json"),fetch("/data/ui-text.json")]),o=await l.json();h=await c.json(),u=await Promise.all(o.map(async t=>(await fetch(`/data/projects/${t}.json`)).json())),e&&E(e),y(a)}catch(l){console.error("Failed to load projects:",l)}}}function g(a){let e=u;return a!=="engine"&&i.engine&&(e=e.filter(l=>l.engine===i.engine)),a!=="genre"&&i.genre&&(e=e.filter(l=>l.genres.includes(i.genre))),a!=="status"&&i.status&&(e=e.filter(l=>l.status===i.status)),e}function S(a){const e=new Set(g("engine").map(t=>t.engine)),l=new Set(g("genre").flatMap(t=>t.genres)),c=new Set(g("status").map(t=>t.status)),o=Object.values(i).some(t=>t!==null);a.querySelectorAll(".filter-chip").forEach(t=>{const s=t,n=s.dataset.type,d=s.dataset.value??s.dataset.filter;if(n==="all"){s.classList.toggle("active",!o);return}let r=!1;n==="engine"?r=e.has(d):n==="genre"?r=l.has(d):n==="status"&&(r=c.has(d)),s.classList.toggle("filter-hidden",!r);const f=n;s.classList.toggle("active",i[f]===d)}),a.querySelectorAll(".filter-divider").forEach(t=>{t.nextElementSibling;let s=!1,n=t.nextElementSibling;for(;n&&!n.classList.contains("filter-divider");){if(n.classList.contains("filter-chip")&&!n.classList.contains("filter-hidden")){s=!0;break}n=n.nextElementSibling}t.classList.toggle("filter-hidden",!s)})}function E(a){const e=[...new Set(u.map(s=>s.engine))].sort(),l=[...new Set(u.flatMap(s=>s.genres))].sort(),c=[...new Set(u.map(s=>s.status))].sort(),o=h.projects?.filterAll||"All";let t='<div class="filter-group">';t+=`<button class="filter-chip active" data-filter="all" data-type="all">${o}</button>`,e.length>1&&(t+='<span class="filter-divider"></span>',e.forEach(s=>{t+=`<button class="filter-chip" data-filter="${s}" data-type="engine">${s}</button>`})),l.length>1&&(t+='<span class="filter-divider"></span>',l.forEach(s=>{t+=`<button class="filter-chip" data-filter="${s}" data-type="genre">${s}</button>`})),c.length>1&&(t+='<span class="filter-divider"></span>',c.forEach(s=>{t+=`<button class="filter-chip" data-filter="${p(s)}" data-type="status" data-value="${s}">${p(s)}</button>`})),t+="</div>",a.innerHTML=t,a.onclick=s=>{const n=s.target.closest(".filter-chip");if(!n)return;const d=n.dataset.type,r=n.dataset.value??n.dataset.filter;if(d==="all")i={engine:null,genre:null,status:null};else{const v=d;i[v]=i[v]===r?null:r}S(a);const f=document.getElementById("project-grid");f&&y(f)}}let m=!1;function j(a){a.innerHTML=u.map(e=>`
        <a href="/projects/${e.slug}/" class="project-card reveal visible"
           data-slug="${e.slug}"
           data-engine="${e.engine}"
           data-genres="${e.genres.join(",")}"
           data-status="${e.status}"
           data-astro-prefetch>
          <div class="card-img-wrap">
            <img
              src="${e.thumbnailImage||e.coverImage}"
              alt="${e.title}"
              loading="lazy"
              onerror="this.style.display='none'"
            />
            <span class="card-status status-${e.status}">${p(e.status)}</span>
          </div>
          <div class="card-body">
            <span class="card-engine">${e.engine}</span>
            <h3 class="card-title">${e.title}</h3>
            <p class="card-tagline">${e.tagline}</p>
            <div class="card-genres">
              ${e.genres.map(l=>`<span class="genre-tag">${l}</span>`).join("")}
            </div>
          </div>
        </a>
      `).join(""),m=!0}function y(a){if(!m){j(a);return}const e=a.querySelector(".empty-state");e&&e.remove();const l=a.querySelectorAll(".project-card");let c=0;if(l.forEach(o=>{const t=o,s=t.dataset.engine,n=t.dataset.genres.split(","),d=t.dataset.status;let r=!0;i.engine&&s!==i.engine&&(r=!1),i.genre&&!n.includes(i.genre)&&(r=!1),i.status&&d!==i.status&&(r=!1),t.classList.toggle("filter-hidden",!r),r&&c++}),c===0){const o=h.projects?.emptyFilters||"No projects match the selected filters.";a.insertAdjacentHTML("beforeend",`<p class="empty-state">${o}</p>`)}}function p(a){return a.split("-").map(e=>e.charAt(0).toUpperCase()+e.slice(1)).join(" ")}function b(){document.getElementById("project-grid")&&$()}b();document.addEventListener("astro:page-load",b);
