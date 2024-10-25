// Wait for DOM to be fully loaded
document.addEventListener('DOMContentLoaded', function() {
    // Get required elements
    const personalDescription = document.querySelector('.personal-description');
    const progressContainer = document.getElementById('progressContainer');

    // Create hr element
    const separator = document.createElement('hr');
    separator.className = 'progress-separator';

    // Create and append progress bar elements
    const progressLabel = document.createElement('span');
    progressLabel.className = 'progress-label';
    progressLabel.textContent = 'SCROLL HEALTHBAR';

    const progressTrack = document.createElement('div');
    progressTrack.className = 'progress-track';

    const progressBar = document.createElement('div');
    progressBar.className = 'progress-bar';
    progressBar.id = 'progressBar';

    // Construct the progress bar hierarchy
    progressTrack.appendChild(progressBar);

    // Insert hr before progress container
    progressContainer.parentNode.insertBefore(separator, progressContainer);

    progressContainer.appendChild(progressLabel);
    progressContainer.appendChild(progressTrack);

    // Calculate and update progress
    function updateProgress() {
        // Get scroll values
        const scrollTop = personalDescription.scrollTop;
        const scrollHeight = personalDescription.scrollHeight;
        const clientHeight = personalDescription.clientHeight;

        // Calculate percentage
        const scrollPercent = (scrollTop / (scrollHeight - clientHeight)) * 100;

        // Update progress bar width
        progressBar.style.width = `${100 - scrollPercent}%`;
        console.log(scrollPercent);

        // Update color based on progress
        if (scrollPercent > 70) {
            progressBar.style.backgroundColor = '#d16464';
        } else if (scrollPercent > 40) {
            progressBar.style.backgroundColor = '#d3bc56';
        } else {
            progressBar.style.backgroundColor = '#83c57a';
        }
    }

    // Check if content is scrollable
    function checkScrollability() {
        const isScrollable = personalDescription.scrollHeight > personalDescription.clientHeight;
        progressContainer.style.display = isScrollable ? 'flex' : 'none';
        separator.style.display = isScrollable ? 'block' : 'none';

        if (isScrollable) {
            updateProgress();
        }
    }

    // Add event listeners
    personalDescription.addEventListener('scroll', updateProgress);
    window.addEventListener('resize', checkScrollability);

    // Create observer for content changes
    const contentObserver = new MutationObserver(checkScrollability);
    contentObserver.observe(personalDescription, {
        childList: true,
        subtree: true,
        characterData: true
    });

    // Initial check
    checkScrollability();

    // Add smooth transition for progress bar
    progressBar.style.transition = 'width 0.2s ease-out, background-color 0.3s ease';
});
