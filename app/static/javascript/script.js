document.addEventListener('DOMContentLoaded', function() {
    const themeToggle = document.getElementById('theme-toggle');
    const currentTheme = localStorage.getItem('theme') || 'dark';

    document.documentElement.setAttribute('data-theme', currentTheme);

    themeToggle.addEventListener('click', function() {
        const theme = document.documentElement.getAttribute('data-theme') === 'dark' ? 'light' : 'dark';
        document.documentElement.setAttribute('data-theme', theme);
        localStorage.setItem('theme', theme);
    });
});

document.addEventListener('htmx:afterSwap', function (event) {
        const triggerElement = event.detail.requestConfig.elt;
        const scrollTarget = triggerElement.getAttribute('data-scroll');
        if (scrollTarget) {
            const targetElement = document.getElementById(scrollTarget);
            if (targetElement) {
                targetElement.scrollIntoView({ behavior: 'smooth' });
            }
        } else {
            // Scroll to the top of the page
            window.scrollTo({ top: 0, behavior: 'smooth' });
        }
    });
