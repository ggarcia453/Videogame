#include "../inc/settings.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <iostream>

Settings::Settings()
:musicOn{true}, arrows_wasd{false}
{
}

void Settings::check_changes(sf::Keyboard::Key k){
    if (k == sf::Keyboard::M){
        musicOn = !musicOn;
    }
    if (k == sf::Keyboard::W){
        arrows_wasd = !arrows_wasd;
    }
}

const bool Settings::playMusic() const{
    return musicOn;
}

const bool Settings::CharMove() const{
    return arrows_wasd;
}