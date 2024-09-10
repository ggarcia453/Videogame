#include "../inc/player.hpp"
#include <iostream>
#include "../inc/constants.hpp"
#include <SFML/Window/Keyboard.hpp>

void Player::move_arrows() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            main_sprite->move(0,-0.75);
         } else{
             main_sprite->move(0,-0.25);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            main_sprite->move(0,0.75);
        }
        else{
            main_sprite->move(0,0.25);
            }
        }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            main_sprite->move(-0.75,0);
        }
        else{
            main_sprite->move(-0.25,0);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            main_sprite->move(0.75,0);
        }
        else{
            main_sprite->move(0.25,0);
        }
    }
    bound_check();
}

void Player::move_wasd(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            main_sprite->move(0,-0.75);
         } else{
             main_sprite->move(0,-0.25);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            main_sprite->move(0,0.75);
        }
        else{
            main_sprite->move(0,0.25);
            }
        }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            main_sprite->move(-0.75,0);
        }
        else{
            main_sprite->move(-0.25,0);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
            main_sprite->move(0.75,0);
        }
        else{
            main_sprite->move(0.25,0);
        }
    }
    bound_check();
}

void Player::bound_check(){
    if (current_position.y == 10 & get_y() < get_ylimit()){
        main_sprite->setPosition(get_x(), get_ylimit());
    }
    else if (get_y() < -get_ylimit()){
        main_sprite->setPosition(get_x(), get_y() +SCRHEIGHT);
        update_position(0,1);
    }
    if (current_position.y == 1 & get_y() > SCRHEIGHT - get_ylimit()){
        main_sprite->setPosition(get_x(), SCRHEIGHT - get_ylimit());
    }
    else if (get_y() > SCRHEIGHT + get_ylimit()){
        main_sprite->setPosition(get_x(), get_y() -SCRHEIGHT);
        update_position(0,-1);
    }
    if (current_position.x == 1 & get_x() < get_xlimit()){
        main_sprite->setPosition(get_xlimit(), get_y());
    }
    else if (get_x() < -get_xlimit()){
        main_sprite->setPosition(get_x() + SCRWIDTH, get_y());
        update_position(-1,0);
    }
    if (current_position.x == 10 & get_x() > SCRWIDTH - get_xlimit()){
        main_sprite->setPosition(SCRWIDTH - get_xlimit(), get_y());
    }
    else if (get_x() > SCRWIDTH + get_xlimit()){
        main_sprite->setPosition(get_x() - SCRWIDTH, get_y());
        update_position(1,0);
    }
}

Player::Player(sf::Sprite* m, sf::Texture& Texture1)
:main_sprite{m}, current_position{1,1}, level{1}, wasd{false}
{
    main_sprite->setTexture(Texture1);
    main_sprite->setScale(0.105, 0.105);
    main_sprite->setOrigin(main_sprite->getLocalBounds().width / 2.f, main_sprite->getLocalBounds().height / 2.f);  
    main_sprite->setPosition(get_xlimit() ,SCRHEIGHT - get_ylimit()); 
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

void Player::move(){
    if (wasd){
        move_wasd();
    }
    else{
        move_arrows();
    }
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
}

const short Player::get_xPosition() const{
    return current_position.x;
}

const short Player::get_yPosition() const{
    return current_position.y;
}

void Player::set_wasd(const bool newwasd){
    wasd = newwasd;
}

Player::~Player(){};