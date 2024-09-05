#include "../inc/items.hpp"

Item::Item(sf::Sprite* s)
:sprite{s}, visible{false}
{}

void Item::display(){
    visible = true;
}

void Item::hide(){
    visible = false;
}

const bool Item::show() const{
    return visible;
}