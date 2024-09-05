#include "../inc/settings.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <iostream>

// Settings::Settings()
// :musicOn{true}
// {
// }

// void Settings::check_changes(){
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
//         std::cout << "here\n";
//     }
// }

const bool Settings::playMusic() const{
    return musicOn;
}