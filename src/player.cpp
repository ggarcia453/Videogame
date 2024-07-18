#include "../inc/player.hpp"

Player::Player(sf::Sprite* m){
    main_sprite = m;
}


const sf::Sprite Player::get_sprite() const{
    return *main_sprite;

}