#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "SFML/Graphics.hpp"

class Item{
    private:
        sf::Sprite* sprite;
        bool visible;
    public:
        Item(sf::Sprite* s);    
        void display();
        void hide();
        const bool show() const;
};


#endif