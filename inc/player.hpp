#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "constants.hpp"
#include "items.hpp"

class Player{
    private:
        position current_position;            
        sf::Sprite* main_sprite;
        void bound_check();
        void update_position(const short x, const short y);
        void move_arrows();
        void move_wasd();
        bool wasd;
        std::vector<Item> itemholder;
        
    public:

        Player();
        Player(sf::Sprite* m, sf::Texture& Texture1);
        ~Player();
        const sf::Sprite get_sprite() const;
        void move();
        const short get_xPosition() const;
        const short get_yPosition() const;
        const int get_xlimit() const;
        const int get_ylimit() const;
        void set_wasd(const bool newwasd);
        const position get_pos() const;
        const float get_x() const;
        const float get_y() const;
        const int get_width() const;
        const int get_height() const;
        void add_item(Item* item);
        bool holding_item(Item* item);
        void level_up();
};

#endif