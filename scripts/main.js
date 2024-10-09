function switchHighlightTheme(theme) {
    const highlightLight = document.getElementById('highlight-light');
    const highlightDark = document.getElementById('highlight-dark');
    if (theme === 'light') {
        highlightLight.disabled = false;
        highlightDark.disabled = true;
        removeWhitePngClass();
    } else {
        highlightLight.disabled = true;
        highlightDark.disabled = false;
        addWhitePngClass();
    }
}

function addWhitePngClass() {
    // Seleziona tutte le immagini con ID che iniziano con "togglable-image"
    const icons = document.querySelectorAll('.nav-icon');
    icons.forEach(img => {
        img.classList.add('white-png');
    });
}

function removeWhitePngClass() {
    // Seleziona tutte le immagini con ID che iniziano con "togglable-image"
    const icons = document.querySelectorAll('.nav-icon');
    icons.forEach(img => {
        img.classList.remove('white-png');
    });
}

function changeBackground(imageUrl) {
    const bg1 = document.querySelector('.background1');
    const bg2 = document.querySelector('.background2');

    if (!bg1.classList.contains('active')) {
        bg2.style.backgroundImage = `url(${imageUrl})`;
        bg2.classList.add('active');
        bg1.classList.remove('active');
    } else {
        bg1.style.backgroundImage = `url(${imageUrl})`;
        bg1.classList.add('active');
        bg2.classList.remove('active');
    }
}

document.addEventListener('DOMContentLoaded', () => {
    const currentTheme = document.documentElement.getAttribute('data-theme');
    switchHighlightTheme(currentTheme);

    const themeToggleButton = document.getElementById('theme-toggle');
    themeToggleButton.addEventListener('click', () => {
        const currentTheme = document.documentElement.getAttribute('data-theme');
        const newTheme = currentTheme === 'dark' ? 'light' : 'dark';
        document.documentElement.setAttribute('data-theme', newTheme);
        switchHighlightTheme(newTheme);
    });
});

function toggleSections() {
    var aboutSection = document.querySelector('.about');
    var isAboutVisible = aboutSection.classList.contains('show');

    if (isAboutVisible ) {
        aboutSection.classList.remove('show');
    } else {
        aboutSection.style.display = 'flex';
        requestAnimationFrame(() => {
            aboutSection.classList.add('show');
        });
    }
}

document.addEventListener('transitionend', (event) => {
    if (event.target.classList.contains('about') ) {
        if (!event.target.classList.contains('show')) {
            event.target.style.display = 'none';
        }
    }
});

function combineMedia(section) {
    return [...section.images, ...section.videos].map((item, index) => ({ type: !item.includes('youtube') ? 'image' : 'video', src: item }));
}


function mainData() {
    return {
        currentPage: 'portfolio',
        loading: true,
        aboutData: {
            name: '',
            profession: '',
            brieflyMe: '',
            skills: [],
            info: {
                residence: '',
                city: '',
                age: ''
            },
            socials: {
                github: '',
                linkedin: '',
                email: ''
            },
            cv: ''
        },
        content: null,
        activeSnippet: null,
        activeIndex: null,
        sectionIndex: 0,
        projectIndex: 0,
        projects: [], // Lista dinamica dei progetti
        previewIndex: null,

        toggleSection(title) {
            this.content.sections.forEach(section => {

                if (section.title === title) {

                    section.isOpen = !section.isOpen;
                }
            });
        },
        navigateProject(direction) {
            if (direction === 'prev') {
                this.projectIndex = (this.projectIndex - 1 + this.projects.length) % this.projects.length;
            } else if (direction === 'next') {
                this.projectIndex = (this.projectIndex + 1) % this.projects.length;
        }
            this.loadProject();
        },
        showPreview(index) {
            this.previewIndex = index;
        },

        hidePreview() {
            this.previewIndex = null;
        },

        loadProjectDetails(projectFolder) {
            return fetch(`data/${projectFolder}/project.json`)
                .then(response => response.json())
                .then(projectData => ({
                    ...projectData,
                    folder: projectFolder,
                    icon: projectData.icon || `data/${projectFolder}/icon.png`,
                    preview: projectData.preview || `data/${projectFolder}/project_image.jpg`,
                    description: projectData.description || 'No description available'
                }))
                .catch(error => {
                    console.error(`Error loading details for ${projectFolder}:`, error);
                    return null;
                });
        },

        navigateToProject(index) {
            this.projectIndex = index;
            this.loadProject();
        },

        loadProject() {
            const project = this.projects[this.projectIndex];
            if (!project) return;

            this.content = project;
            changeBackground(project.background);
            this.loadSnippets(project.sections);
            this.loading = false;
        },
        loadSnippets(sections) {

            sections.forEach(section => {
                section.activeSnippet = null;
                section.activeIndex = null;
                section.codeSnippets.forEach(snippet => {
                    fetch(snippet.file)
                        .then(response => response.text())
                        .then(code => {
                            if (typeof hljs !== 'undefined') {
                                snippet.code = hljs.highlightAuto(code).value; // Evidenzia il codice
                            } else {
                                snippet.code = code;
                            }
                        })
                        .catch(error => console.error('Error loading snippet:', error));
                });
            });
        },
        toggleSnippet(sectionIndex, snippet, index) {
            this.content.sections.forEach((section, sIndex) => {
                if (sIndex === sectionIndex) {
                    if (section.activeSnippet === snippet.code) {
                        section.activeSnippet = null;
                        section.activeIndex = null;
                    } else {
                        section.activeSnippet = snippet.code;
                        section.activeIndex = index;
                    }
                } else {
                    section.activeSnippet = null;
                    section.activeIndex = null;
                }
            });
        },
        loadProjects() {
            fetch('data/projects.json')
                .then(response => response.json())
                .then(data => {
                    // Carica i dettagli per ogni progetto
                    Promise.all(data.projects.map(this.loadProjectDetails))
                        .then(detailedProjects => {
                            this.projects = detailedProjects;
                            this.loadProject();
                        });
                })
                .catch(error => console.error('Error loading projects:', error));
        },
        switchPage(page) {
            this.currentPage = page;
            if (page === 'portfolio') {
                this.loading = true; // Mostra lo spinner di caricamento quando si cambia pagina
                this.loadProject();
            } else {
                this.loading = false;
            }
        },
        fetchAboutData() {
            fetch('data/about.json')
                .then(response => response.json())
                .then(data => {
                    this.aboutData = data;
                })
                .catch(error => console.error('Error loading about data:', error));
        },
        init() {
            this.fetchAboutData();
            this.loadProjects();

        }
    };
}

function mediaNavigator(images, videos) {
    // Combine images and videos into a single array with type indication
    const combinedMedia = [
        ...images.map(src => ({ type: 'image', src })),
        ...videos.map(src => ({ type: 'video', src }))
    ];

    return {
        combinedMedia: combinedMedia,
        currentMediaIndex: 0,
        prevMedia() {
            this.currentMediaIndex = (this.currentMediaIndex - 1 + this.combinedMedia.length) % this.combinedMedia.length;
        },
        nextMedia() {
            this.currentMediaIndex = (this.currentMediaIndex + 1) % this.combinedMedia.length;
        }
    };
}



// Assicurati che mainData sia disponibile globalmente per Alpine.js
window.mainData = mainData;
window.mediaNavigator = mediaNavigator;
