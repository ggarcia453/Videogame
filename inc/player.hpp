#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>

class Player{
    private:
        

    public:
        sf::Sprite* main_sprite;

        Player(sf::Sprite* m);
        const sf::Sprite get_sprite() const;
        const float get_xlimit() const;
        const float get_ylimit() const;
        

};

#endif