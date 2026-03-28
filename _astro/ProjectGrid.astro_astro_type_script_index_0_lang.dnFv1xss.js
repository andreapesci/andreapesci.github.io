function m(a){return a.split("-").map(n=>n.charAt(0).toUpperCase()+n.slice(1)).join(" ")}let u=[],i={engine:null,genre:null,status:null},v=!1,g={};async function S(){const a=document.getElementById("project-grid"),n=document.getElementById("filter-bar");if(a){i={engine:null,genre:null,status:null},v=!1;try{const[e,c]=await Promise.all([fetch("/data/projects/_index.json"),fetch("/data/ui-text.json")]),o=await e.json();g=await c.json(),u=await Promise.all(o.map(async s=>(await fetch(`/data/projects/${s}.json`)).json())),n&&E(n),y(a)}catch(e){console.error("Failed to load projects:",e)}}}function h(a){let n=u;return a!=="engine"&&i.engine&&(n=n.filter(e=>e.engine===i.engine)),a!=="genre"&&i.genre&&(n=n.filter(e=>e.genres.includes(i.genre))),a!=="status"&&i.status&&(n=n.filter(e=>e.status===i.status)),n}function A(a){const n=new Set(h("engine").map(s=>s.engine)),e=new Set(h("genre").flatMap(s=>s.genres)),c=new Set(h("status").map(s=>s.status)),o=Object.values(i).some(s=>s!==null);a.querySelectorAll(".filter-chip").forEach(s=>{const t=s,l=t.dataset.type,d=t.dataset.value??t.dataset.filter;if(l==="all"){const b=!o;t.classList.toggle("active",b),t.setAttribute("aria-pressed",String(b));return}let r=!1;l==="engine"?r=n.has(d):l==="genre"?r=e.has(d):l==="status"&&(r=c.has(d)),t.classList.toggle("filter-hidden",!r);const f=i[l]===d;t.classList.toggle("active",f),t.setAttribute("aria-pressed",String(f))}),a.querySelectorAll(".filter-divider").forEach(s=>{let t=!1,l=s.nextElementSibling;for(;l&&!l.classList.contains("filter-divider");){if(l.classList.contains("filter-chip")&&!l.classList.contains("filter-hidden")){t=!0;break}l=l.nextElementSibling}s.classList.toggle("filter-hidden",!t)})}function E(a){const n=[...new Set(u.map(t=>t.engine))].sort(),e=[...new Set(u.flatMap(t=>t.genres))].sort(),c=[...new Set(u.map(t=>t.status))].sort(),o=g.projects?.filterAll||"All";let s='<div class="filter-group">';s+=`<button class="filter-chip active" data-filter="all" data-type="all" aria-pressed="true">${o}</button>`,n.length>1&&(s+='<span class="filter-divider"></span>',n.forEach(t=>{s+=`<button class="filter-chip" data-filter="${t}" data-type="engine" aria-pressed="false">${t}</button>`})),e.length>1&&(s+='<span class="filter-divider"></span>',e.forEach(t=>{s+=`<button class="filter-chip" data-filter="${t}" data-type="genre" aria-pressed="false">${t}</button>`})),c.length>1&&(s+='<span class="filter-divider"></span>',c.forEach(t=>{s+=`<button class="filter-chip" data-filter="${m(t)}" data-type="status" data-value="${t}" aria-pressed="false">${m(t)}</button>`})),s+="</div>",a.innerHTML=s,a.onclick=t=>{const l=t.target.closest(".filter-chip");if(!l)return;const d=l.dataset.type,r=l.dataset.value??l.dataset.filter;if(d==="all")i={engine:null,genre:null,status:null};else{const f=d;i[f]=i[f]===r?null:r}A(a);const p=document.getElementById("project-grid");p&&y(p)}}function j(a){const n=g.projects?.statusStyle||"dot";a.dataset.statusStyle=n,a.innerHTML=u.map(e=>{const c=e.featured,o=g.projects?.featuredRibbon||"Featured",s=c?`<span class="banner-ribbon">${o}</span>`:"",t=m(e.status),l=`<span class="status-dot status-${e.status}">${t}</span>`,d=`<span class="status-tag status-${e.status}">${t}</span>`;return`
          <a href="/projects/${e.slug}/" class="project-card reveal visible${c?" card-featured":""}"
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
              ${s}
            </div>
            <div class="card-body">
              <div class="card-engine-row">
                <span class="card-engine">${e.engine}</span>
                ${l}
              </div>
              <h3 class="card-title">${e.title}</h3>
              <p class="card-tagline">${e.tagline}</p>
              <div class="card-genres">
                ${d}
                ${e.genres.map(r=>`<span class="genre-tag">${r}</span>`).join("")}
              </div>
            </div>
          </a>
        `}).join(""),v=!0}function y(a){if(!v){j(a);return}const n=a.querySelector(".empty-state");n&&n.remove();const e=a.querySelectorAll(".project-card");let c=0;if(e.forEach(o=>{const s=o,t=s.dataset.engine,l=s.dataset.genres.split(","),d=s.dataset.status;let r=!0;i.engine&&t!==i.engine&&(r=!1),i.genre&&!l.includes(i.genre)&&(r=!1),i.status&&d!==i.status&&(r=!1),s.classList.toggle("filter-hidden",!r),r&&c++}),c===0){const o=g.projects?.emptyFilters||"No projects match the selected filters.";a.insertAdjacentHTML("beforeend",`<p class="empty-state">${o}</p>`)}}function $(){document.getElementById("project-grid")&&S()}$();document.addEventListener("astro:page-load",$);
