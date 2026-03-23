async function i(){const e=document.getElementById("featured-grid");if(e)try{const r=await(await fetch("/data/projects/_index.json")).json(),n=(await Promise.all(r.map(async t=>(await fetch(`/data/projects/${t}.json`)).json()))).filter(t=>t.featured).sort((t,a)=>(t.featuredOrder??99)-(a.featuredOrder??99));if(n.length===0){const a=await(await fetch("/data/ui-text.json")).json();e.innerHTML=`<p class="empty-state">${a.featured.emptyState}</p>`;return}e.innerHTML=n.map((t,a)=>`
          <a href="/projects/${t.slug}/" class="spotlight-card reveal"
             style="transition-delay: ${a*80}ms;"
             data-astro-prefetch>
            <div class="spotlight-img-wrap">
              <img
                src="${t.coverImage}"
                alt="${t.title}"
                loading="${a===0?"eager":"lazy"}"
                onerror="this.style.display='none'"
              />
              <div class="spotlight-overlay"></div>
              <span class="status-badge status-${t.status}">${o(t.status)}</span>
            </div>
            <div class="spotlight-body">
              <div class="spotlight-meta">
                <span class="engine-tag">${t.engine}</span>
                <span class="platform-tags">${t.platforms.join(" / ")}</span>
              </div>
              <h3 class="spotlight-title">${t.title}</h3>
              <p class="spotlight-tagline">${t.tagline}</p>
            </div>
          </a>
        `).join(""),document.dispatchEvent(new Event("astro:page-load"))}catch(s){console.error("Failed to load featured projects:",s)}}function o(e){return e.split("-").map(s=>s.charAt(0).toUpperCase()+s.slice(1)).join(" ")}i();document.addEventListener("astro:page-load",()=>{const e=document.getElementById("featured-grid");e&&e.querySelector(".skeleton-card")&&i()});
