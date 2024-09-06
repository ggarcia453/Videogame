#include "../inc/settings.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <iostream>

Settings::Settings()
:musicOn{true}, buffer{false}
{
}

void Settings::check_changes(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && not buffer){
        buffer = true;
        musicOn = !musicOn;
    }
    else if (! sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
        buffer = false;
    }
}

const bool Settings::playMusic() const{
    return musicOn;
}