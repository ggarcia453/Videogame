#include "config.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "inc/player.hpp"

typedef enum {TitleScreen, GameScreen, Questions} States;

void string_setup(sf::Text& text, std::string message, sf::Font& font){
  text.setFont(font);
  text.setString(message);
  text.setFillColor(sf::Color::Red);
  text.setCharacterSize(36); 
  text.setStyle(sf::Text::Bold);
  sf::FloatRect textRect = text.getLocalBounds();
  text . setOrigin(textRect.left + textRect.width/2.0f,
               textRect.top  + textRect.height/2.0f);
}

int main(int argc, char* argv[]) {
  //Initialize assets and Load from assets folder
  sf::Music Titlemusic;
  sf::Music Gamemusic;
  sf::Font font;
  sf::Text text1;
  sf::Text text2;
  sf::Text text3;
  sf::Text text4;
  sf::Text text5;
  sf::Texture Texture1;
  sf::Sprite Sprite1;
  Player main_character(&Sprite1);
  if (!Titlemusic.openFromFile("../assets/music/fnaf_title.ogg")){
    return -1;
  }
  if (!font.loadFromFile("../assets/fonts/font.ttf")){
    return -1;
  }
  if (!Gamemusic.openFromFile("../assets/music/bonnie.ogg")){
    return -1;
  }
  if (!Texture1.loadFromFile("../assets/img/kfc_goku.jpg")){
    return -1;
  }

  //Window set up
  const short SCRWIDTH = 500; 
  const short SCRHEIGHT = 420;
  sf::RenderWindow window(sf::VideoMode(SCRWIDTH, SCRHEIGHT), "videoagme");

  //Title Screen text Set up   
  string_setup(text1, "Title Screen", font);

  //text2 set up
  string_setup(text2, "P to Play game", font);

  //Instrcutiontext2 set up
  string_setup(text3, "Q to Question????", font);

  //test4 setup
  string_setup(text4, "Settings", font);

  //text5
  string_setup(text5, "Esc to stop questions", font);

  //Titlemusic set up  
  Titlemusic.setLoop(true);
  Titlemusic.play();
  Gamemusic.setLoop(true);

  //Sprite Setup
  main_character.main_sprite->setTexture(Texture1);
  main_character.main_sprite->setScale(0.105, 0.105);
  main_character.main_sprite->setOrigin(main_character.main_sprite->getLocalBounds().width / 2.f, main_character.main_sprite->getLocalBounds().height / 2.f);  
  main_character.main_sprite->setPosition(SCRWIDTH/2.0f ,SCRHEIGHT/2.0f);  
  const int xlimit = Texture1.getSize().x * main_character.main_sprite->getScale().x /2;
  const int ylimit = Texture1.getSize().y * main_character.main_sprite->getScale().y /2;

  //State Setup
  States curState = TitleScreen;
  States nextState = TitleScreen;

   while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        switch (curState)
        {
        case TitleScreen:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            return EXIT_SUCCESS;
          }
          text1.setPosition(sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f - SCRHEIGHT/4.0f));
          text2.setPosition(sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f));
          text3.setPosition(sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/3.0f ));
          if (Titlemusic.getStatus() != 2){
              Titlemusic.play();
            }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            nextState = Questions;
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            nextState =GameScreen;
          }
          window.clear();
          window.draw(text1);
          window.draw(text2);
          window.draw(text3);
          window.display();
          break;
        case Questions:
          if(Titlemusic.getStatus() == 2){Titlemusic.pause();}
          text4.setPosition(sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f - SCRHEIGHT/4.0f));
          text5.setPosition(sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f));
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            nextState = TitleScreen;
          }
          window.clear();
          window.draw(text4);
          window.draw(text5);
          window.display();
          break;
        case GameScreen:
          if(Titlemusic.getStatus() != 0){Titlemusic.stop();}
          if(Gamemusic.getStatus() != 2){Gamemusic.play();}
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            main_character.main_sprite->move(0,-0.25);
            if (main_character.main_sprite->getPosition().y < -ylimit){
              main_character.main_sprite->setPosition(main_character.main_sprite->getPosition().x, main_character.main_sprite->getPosition().y + SCRHEIGHT);
            }
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            main_character.main_sprite->move(0,0.25);
            if (main_character.main_sprite->getPosition().y > SCRHEIGHT + ylimit){
              main_character.main_sprite->setPosition(main_character.main_sprite->getPosition().x, main_character.main_sprite->getPosition().y - SCRHEIGHT);
            }
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            main_character.main_sprite->move(-0.25,0);
            if (main_character.main_sprite->getPosition().x < -xlimit){
              main_character.main_sprite->setPosition(main_character.main_sprite->getPosition().x + SCRWIDTH , main_character.main_sprite->getPosition().y);
            }
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            main_character.main_sprite->move(0.25,0);
            if (main_character.main_sprite->getPosition().x > SCRWIDTH + xlimit){
              main_character.main_sprite->setPosition(main_character.main_sprite->getPosition().x - SCRWIDTH, main_character.main_sprite->getPosition().y);
            }
          }
          window.clear();
          window.draw(main_character.get_sprite());
          window.display();
          break;
        default:
          std:: cerr << "SOmething is off" << std:: endl;
          return EXIT_FAILURE;
        } 
        curState = nextState;
    }
  return EXIT_SUCCESS;
  
}