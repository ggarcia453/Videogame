#include "../inc/player.hpp"
#include <iostream>

Player::Player(sf::Sprite* m, sf::Texture& Texture1)
:main_sprite{m}, current_position{0,0}
{
    main_sprite->setTexture(Texture1);
    main_sprite->setScale(0.105, 0.105);
    main_sprite->setOrigin(main_sprite->getLocalBounds().width / 2.f, main_sprite->getLocalBounds().height / 2.f);  
}


const sf::Sprite Player::get_sprite() const{
    return *main_sprite;

}

const int Player::get_xlimit() const{
    return main_sprite->getTexture()->getSize().x * main_sprite->getScale().x /2;
}

const int Player::get_ylimit() const{
    return main_sprite->getTexture()->getSize().y * main_sprite->getScale().y /2;
}

void Player::set_position(float x, float y){
    main_sprite->setPosition(x,y);
}

void Player::move(float x, float y){
    main_sprite->move(x,y);
}


const float Player:: get_x() const{
    return main_sprite->getPosition().x;
}

const float Player:: get_y() const{
    return main_sprite->getPosition().y;
}

void Player::update_position(const short x, const short y){
    current_position.x += x;
    current_position.y += y;
    std:: cout << current_position.x << " " << current_position.y << "\n";
}