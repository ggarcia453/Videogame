#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

struct position{
    short x;
    short y;
};

class Player{
    private:
        position current_position;            
        sf::Sprite* main_sprite;
        void bound_check();
        void update_position(const short x, const short y);
        short level;
        void move_arrows();
        void move_wasd();
        bool wasd;
        
    public:

        Player(sf::Sprite* m, sf::Texture& Texture1);
        ~Player();
        const sf::Sprite get_sprite() const;
        const float get_x() const;
        const float get_y() const;
        void move();
        const short get_xPosition() const;
        const short get_yPosition() const;
        const int get_xlimit() const;
        const int get_ylimit() const;
        void set_wasd(const bool newwasd);
};

#endif