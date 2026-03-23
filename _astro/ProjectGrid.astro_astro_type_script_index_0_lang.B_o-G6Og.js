let d=[],i={engine:null,genre:null,status:null},g={};async function $(){const a=document.getElementById("project-grid"),n=document.getElementById("filter-bar");if(a){i={engine:null,genre:null,status:null},m=!1;try{const[t,c]=await Promise.all([fetch("/data/projects/_index.json"),fetch("/data/ui-text.json")]),o=await t.json();g=await c.json(),d=await Promise.all(o.map(async e=>(await fetch(`/data/projects/${e}.json`)).json())),n&&E(n),b(a)}catch(t){console.error("Failed to load projects:",t)}}}function p(a){let n=d;return a!=="engine"&&i.engine&&(n=n.filter(t=>t.engine===i.engine)),a!=="genre"&&i.genre&&(n=n.filter(t=>t.genres.includes(i.genre))),a!=="status"&&i.status&&(n=n.filter(t=>t.status===i.status)),n}function S(a){const n=new Set(p("engine").map(e=>e.engine)),t=new Set(p("genre").flatMap(e=>e.genres)),c=new Set(p("status").map(e=>e.status)),o=Object.values(i).some(e=>e!==null);a.querySelectorAll(".filter-chip").forEach(e=>{const s=e,l=s.dataset.type,u=s.dataset.value??s.dataset.filter;if(l==="all"){s.classList.toggle("active",!o);return}let r=!1;l==="engine"?r=n.has(u):l==="genre"?r=t.has(u):l==="status"&&(r=c.has(u)),s.classList.toggle("filter-hidden",!r);const f=l;s.classList.toggle("active",i[f]===u)}),a.querySelectorAll(".filter-divider").forEach(e=>{e.nextElementSibling;let s=!1,l=e.nextElementSibling;for(;l&&!l.classList.contains("filter-divider");){if(l.classList.contains("filter-chip")&&!l.classList.contains("filter-hidden")){s=!0;break}l=l.nextElementSibling}e.classList.toggle("filter-hidden",!s)})}function E(a){const n=[...new Set(d.map(s=>s.engine))].sort(),t=[...new Set(d.flatMap(s=>s.genres))].sort(),c=[...new Set(d.map(s=>s.status))].sort(),o=g.projects?.filterAll||"All";let e='<div class="filter-group">';e+=`<button class="filter-chip active" data-filter="all" data-type="all">${o}</button>`,n.length>1&&(e+='<span class="filter-divider"></span>',n.forEach(s=>{e+=`<button class="filter-chip" data-filter="${s}" data-type="engine">${s}</button>`})),t.length>1&&(e+='<span class="filter-divider"></span>',t.forEach(s=>{e+=`<button class="filter-chip" data-filter="${s}" data-type="genre">${s}</button>`})),c.length>1&&(e+='<span class="filter-divider"></span>',c.forEach(s=>{e+=`<button class="filter-chip" data-filter="${h(s)}" data-type="status" data-value="${s}">${h(s)}</button>`})),e+="</div>",a.innerHTML=e,a.onclick=s=>{const l=s.target.closest(".filter-chip");if(!l)return;const u=l.dataset.type,r=l.dataset.value??l.dataset.filter;if(u==="all")i={engine:null,genre:null,status:null};else{const v=u;i[v]=i[v]===r?null:r}S(a);const f=document.getElementById("project-grid");f&&b(f)}}let m=!1;function j(a){const n=g.projects?.statusStyle||"dot";a.dataset.statusStyle=n,a.innerHTML=d.map(t=>{const c=t.featured,o=c?'<span class="banner-ribbon">Featured</span>':"",e=h(t.status),s=`<span class="status-dot status-${t.status}">${e}</span>`,l=`<span class="status-tag status-${t.status}">${e}</span>`;return`
          <a href="/projects/${t.slug}/" class="project-card reveal visible${c?" card-featured":""}"
             data-slug="${t.slug}"
             data-engine="${t.engine}"
             data-genres="${t.genres.join(",")}"
             data-status="${t.status}"
             data-astro-prefetch>
            <div class="card-img-wrap">
              <img
                src="${t.thumbnailImage||t.coverImage}"
                alt="${t.title}"
                loading="lazy"
                onerror="this.style.display='none'"
              />
              ${o}
            </div>
            <div class="card-body">
              <div class="card-engine-row">
                <span class="card-engine">${t.engine}</span>
                ${s}
              </div>
              <h3 class="card-title">${t.title}</h3>
              <p class="card-tagline">${t.tagline}</p>
              <div class="card-genres">
                ${l}
                ${t.genres.map(u=>`<span class="genre-tag">${u}</span>`).join("")}
              </div>
            </div>
          </a>
        `}).join(""),m=!0}function b(a){if(!m){j(a);return}const n=a.querySelector(".empty-state");n&&n.remove();const t=a.querySelectorAll(".project-card");let c=0;if(t.forEach(o=>{const e=o,s=e.dataset.engine,l=e.dataset.genres.split(","),u=e.dataset.status;let r=!0;i.engine&&s!==i.engine&&(r=!1),i.genre&&!l.includes(i.genre)&&(r=!1),i.status&&u!==i.status&&(r=!1),e.classList.toggle("filter-hidden",!r),r&&c++}),c===0){const o=g.projects?.emptyFilters||"No projects match the selected filters.";a.insertAdjacentHTML("beforeend",`<p class="empty-state">${o}</p>`)}}function h(a){return a.split("-").map(n=>n.charAt(0).toUpperCase()+n.slice(1)).join(" ")}function y(){document.getElementById("project-grid")&&$()}y();document.addEventListener("astro:page-load",y);
