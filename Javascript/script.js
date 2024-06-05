// jsfunctions.js
function myFunction() {
    alert("Funzione JavaScript chiamata!");
}

function updateContent() {
    document.getElementById('some-div').innerHTML = 'Contenuto aggiornato!';
}

function generateProjectHTML() {
    console.log('pippo');
    const div = document.getElementById('swap-content');
    console.log(div);
    div.innerHTML = portfolio.map(project => `
        <div class="project">
            <div class="project-image-div">
                <img class="project-image" src="${project.image[0]}" alt="Project Picture"/>
            </div>
            <div class="project-text">
                <div class="project-text-description">
                    <h2 class="project-text-description-title">${project.title}</h2>
                    <p class="project-text-description-plot">
                        ${project.description}
                    </p>
                </div>
                <div class="project-text-information">
                    <div class="project-text-information-paragraph">
                        <p class="project-text-information-paragraph-subject">
                            Tools/Technology
                        </p>
                        <p class="project-text-information-paragraph-object">
                            ${project.tools.join(', ')}
                        </p>
                    </div>
                    <div class="project-text-information-paragraph">
                        <p class="project-text-information-paragraph-subject">Year</p>
                        <p class="project-text-information-paragraph-object">
                            ${project.year}
                        </p>
                    </div>
                    <div class="project-text-information-paragraph">
                        <p class="project-text-information-paragraph-subject">
                            Roles
                        </p>
                        <p class="project-text-information-paragraph-object">
                            ${project.roles.join(', ')}
                        </p>
                    </div>
                </div>
            </div>
        </div>
    `).join('');
}

