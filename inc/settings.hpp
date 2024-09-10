#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "SFML/Window/Keyboard.hpp"

class Settings{
    private:
        bool musicOn;
        bool arrows_wasd;
    public:
        Settings();
        void check_changes(sf::Keyboard::Key k);
        const bool playMusic() const;
        const bool CharMove() const;

};

#endif