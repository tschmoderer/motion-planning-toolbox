function changeLogoLightDarkMode() {
    const el = document.getElementsByTagName("doxygen-awesome-dark-mode-toggle");
  
    if (el.length) {
      // Do something with el
        console.log("element lightdark found")
        el[0].addEventListener("click", function() {
            initialLightDarkMode();
        })
    } else {
        console.log("retry to find elem")
        setTimeout(changeLogoLightDarkMode, 300); // try again in 300 milliseconds
    }
}

function initialLightDarkMode() {
    if (DoxygenAwesomeDarkModeToggle.userPreference) {
        // if dark mode is already enabled
        // then set logo to white version
        try {
            document.getElementById("motion-planning-toolbox-logo-img").setAttribute('src', 'https://raw.githubusercontent.com/tschmoderer/motion-planning-toolbox/main/docs/img/icons/128x128/rocket-white.png')
        } catch(ex) {
            console.log(ex);
        }
        document.getElementById("projectlogo").childNodes[0].setAttribute('src', 'rocket-white.png')
    } else {
        try {
            document.getElementById("motion-planning-toolbox-logo-img").setAttribute('src', 'https://raw.githubusercontent.com/tschmoderer/motion-planning-toolbox/main/docs/img/icons/128x128/rocket.png')
        }
        catch(ex) {
            console.log(ex);
        }
        document.getElementById("projectlogo").childNodes[0].setAttribute('src', 'rocket.png')
    }
}

$(document).ready(function() {
    initialLightDarkMode()
    changeLogoLightDarkMode();
});  