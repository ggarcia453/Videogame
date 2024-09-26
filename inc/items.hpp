#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "SFML/Graphics.hpp"
#include "constants.hpp"

class Item{
    private:
        sf::Sprite* sprite;
        bool visible;
        position screen_pos;
        position map_pos;

        bool collision_detection(float x,float y, const int height, const int width) const;

    public:
        Item(sf::Sprite* s, position screen, position map);    
        const bool show() const;
        void draw(sf::RenderWindow* w, position map, float x, float y, const int height, const int width) ;
        
};


#endif