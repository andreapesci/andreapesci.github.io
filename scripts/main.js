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
