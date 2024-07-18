#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>

struct position{
    short x;
    short y;
};

class Player{
    private:
        position current_position;            
        sf::Sprite* main_sprite;
    public:

        Player(sf::Sprite* m, sf::Texture& Texture1);
        const sf::Sprite get_sprite() const;
        const int get_xlimit() const;
        const int get_ylimit() const;
        void set_position(float x, float y);
        const float get_x() const;
        const float get_y() const;
        void move(float x, float y);
        void update_position(const short x, const short y);
};

#endif