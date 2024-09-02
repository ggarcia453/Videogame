#include "../inc/player.hpp"
#include <iostream>
#include "../inc/constants.hpp"
#include <SFML/Window/Keyboard.hpp>

void Player::bound_check(){
    if (this ->current_position.y == 25 & this ->get_y() < this->get_ylimit()){
        this ->set_position(this ->get_x(), this->get_ylimit());
    }
    else if (this ->get_y() < -this->get_ylimit()){
        this ->set_position(this ->get_x(), this ->get_y() +SCRHEIGHT);
        this ->update_position(0,1);
    }
    if (this ->current_position.y == 1 & this ->get_y() > SCRHEIGHT - this->get_ylimit()){
        this ->set_position(this ->get_x(), SCRHEIGHT - this->get_ylimit());
    }
    else if (this ->get_y() > SCRHEIGHT + this->get_ylimit()){
        this ->set_position(this ->get_x(), this ->get_y() -SCRHEIGHT);
        this ->update_position(0,-1);
    }
    if (this ->current_position.x == 1 & this ->get_x() < this->get_xlimit()){
        this ->set_position(this->get_xlimit(), this ->get_y());
    }
    else if (this ->get_x() < -this->get_xlimit()){
        this ->set_position(this ->get_x() + SCRWIDTH, this ->get_y());
        this ->update_position(-1,0);
    }
    if (this ->current_position.x == 25 & this ->get_x() > SCRWIDTH - this->get_xlimit()){
        this ->set_position(SCRWIDTH - this->get_xlimit(), this ->get_y());
    }
    else if (this ->get_x() > SCRWIDTH + this->get_xlimit()){
        this ->set_position(this ->get_x() - SCRWIDTH, this ->get_y());
        this ->update_position(1,0);
    }
}

Player::Player(sf::Sprite* m, sf::Texture& Texture1)
:main_sprite{m}, current_position{1,1}
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

void Player::move(){
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
    this->bound_check();
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