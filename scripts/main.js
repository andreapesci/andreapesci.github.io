function switchHighlightTheme(theme) {
    const highlightLight = document.getElementById('highlight-light');
    const highlightDark = document.getElementById('highlight-dark');
    if (theme === 'light') {
        highlightLight.disabled = false;
        highlightDark.disabled = true;
    } else {
        highlightLight.disabled = true;
        highlightDark.disabled = false;
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
        projectIndex: 0,
        projects: [], // Lista dinamica dei progetti
        toggleSection(title) {
            this.content.sections.forEach(section => {
                if (section.title === title) {
                    section.isOpen = !section.isOpen;
                }
            });
        },
        nextProject() {
            this.projectIndex = (this.projectIndex + 1) % this.projects.length;
            this.loadProject();
        },
        prevProject() {
            this.projectIndex = (this.projectIndex - 1 + this.projects.length) % this.projects.length;
            this.loadProject();
        },
        loadProject() {
            const project = this.projects[this.projectIndex];
            fetch(`data/${project}/project.json`)
                .then(response => response.json())
                .then(data => {
                    this.content = data;
                    this.loadSnippets(data.sections);
                    this.loading = false; // Nasconde lo spinner di caricamento quando i dati sono pronti
                })
                .catch(error => console.error('Error loading content:', error));
        },
        loadSnippets(sections) {
            sections.forEach(section => {
                section.codeSnippets.forEach(snippet => {
                    fetch(snippet.file)
                        .then(response => response.text())
                        .then(code => {
                            if (typeof hljs !== 'undefined') {
                                snippet.code = hljs.highlightAuto(code).value; // Highlight the code
                            } else {
                                snippet.code = code;
                            }
                        })
                        .catch(error => console.error('Error loading snippet:', error));
                });
            });
        },
        toggleSnippet(snippet, index) {
            if (this.activeSnippet === snippet.code) {
                this.activeSnippet = null;
                this.activeIndex = null;
            } else {
                this.activeSnippet = snippet.code;
                this.activeIndex = index;
            }
        },
        loadProjects() {
            fetch('data/projects.json') // Carica la lista dei progetti da un file JSON
                .then(response => response.json())
                .then(data => {
                    this.projects = data.projects;
                    this.loadProject(); // Carica il primo progetto dopo aver caricato la lista dei progetti
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
            this.loadProjects();
        }
    };
}

// Assicurati che mainData sia disponibile globalmente per Alpine.js
window.mainData = mainData;
