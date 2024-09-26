#include "../inc/items.hpp"
#include "../inc/constants.hpp"
#include "iostream"

Item::Item(sf::Sprite* s, position screen, position map)
:sprite{s}, visible{true}, screen_pos{screen}, map_pos{map}
{
    s->setScale(item_scale, item_scale);
    s->setOrigin(s->getLocalBounds().width / 2.f, s->getLocalBounds().height / 2.f);  
    s->setPosition(screen_pos.x, screen_pos.y);
}

const bool Item::show() const{
    return visible;
}

bool Item::collision_detection(float x, float y, const int height, const int width)const{
    const int thisheight = sprite->getTexture()->getSize().y * sprite->getScale().y;
    const int thiswidth = sprite->getTexture()->getSize().x * sprite->getScale().x;
    return (screen_pos.x < x + width && screen_pos.x + thiswidth > x && screen_pos.y < y + height && screen_pos.y + thisheight > y);
}

void Item::draw(sf::RenderWindow* w, position map, float x, float y, const int height, const int width) {
    if (map.x ==map_pos.x & map.y == map_pos.y){
        visible = visible & !collision_detection(x,y, height, width);
        if (visible){
            w->draw(*sprite);
        }
    }
}