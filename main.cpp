#include "config.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "inc/player.hpp"
#include "inc/constants.hpp"
#include "inc/settings.hpp"
#include <thread>
sf::Mutex mutex;

void string_setup(sf::Text* text, std::string message, sf::Font& font, sf::Vector2f v){
  mutex.lock();
  text->setFont(font);
  mutex.unlock();
  text->setString(message);
  text->setFillColor(sf::Color::Red);
  text->setCharacterSize(36); 
  text->setStyle(sf::Text::Bold);
  sf::FloatRect textRect = text->getLocalBounds();
  text->setOrigin(textRect.left + textRect.width/2.0f,
               textRect.top  + textRect.height/2.0f);
  text->setPosition(v);
}

int main(int argc, char* argv[]) {
  //Initialize assets and Load from assets folder
  Settings settings;
  sf::Music Titlemusic;
  sf::Music Gamemusic;
  sf::Font font;
  sf::Text text1;
  sf::Text text2;
  sf::Text text3;
  sf::Text text4;
  sf::Text text5;
  sf::Text text6;
  sf::Texture Texture1;
  sf::Sprite Sprite1;
  sf::Texture Texture2;
  sf::Sprite Sprite2;
  bool buffer = false;
  const std:: string ast_path = "../assets/";
  if (!Titlemusic.openFromFile(ast_path + "music/fnaf_title.ogg")){
    return -1;
  }
  if (!font.loadFromFile(ast_path + "fonts/font.ttf")){
    return -1;
  }
  if (!Gamemusic.openFromFile(ast_path + "music/bonnie.ogg")){
    return -1;
  }
  if (!Texture1.loadFromFile(ast_path + "img/kfc_goku.jpg")){
    return -1;
  }
  if (!Texture2.loadFromFile(ast_path + "img/key.jpg")){
    return -1;
  }

  //Window set up
  sf::RenderWindow window(sf::VideoMode(SCRWIDTH, SCRHEIGHT), "videogame");

  //Title Screen text Set up   
  sf::Thread t1(std::bind(& string_setup, &text1, "Title Screen", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f - SCRHEIGHT/4.0f)));
  t1.launch();
  // string_setup(&text1, "Title Screen", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f - SCRHEIGHT/4.0f));

  //text2 setup
  sf::Thread t2(std::bind(&string_setup, &text2, "P to Play game", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f)));
  t2.launch();
  //string_setup(&text2, "P to Play game", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f));

  //text3 setup
  sf::Thread t3(std::bind(&string_setup, &text3, "Q to Question????", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/3.0f)));
  t3.launch();
  // string_setup(&text3, "Q to Question????", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/3.0f));

  //test4 setup
  sf::Thread t4(std::bind(&string_setup, &text4, "Settings", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f - SCRHEIGHT/4.0f)));
  t4.launch();
  // string_setup(&text4, "Settings", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f - SCRHEIGHT/4.0f));

  //text5 setup
  sf::Thread t5(std::bind(&string_setup,&text5, "Esc to stop questions", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f) ));
  t5.launch();
  // string_setup(&text5, "Esc to stop questions", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f));

  //Titlemusic set up  
  Titlemusic.setLoop(true);
  Titlemusic.play();
  Gamemusic.setLoop(true);

  //Sprite Setup
  Player main_character(&Sprite1, Texture1);
  std::string pos_string  = std::to_string(main_character.get_xPosition()) + "," + std::to_string(main_character.get_yPosition());
  sf::Thread t6(std::bind(&string_setup, &text6, pos_string, font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f)));
  t6.launch();
  // string_setup(&text6, pos_string, font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f));

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
        //Check for exit
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) and not buffer){
            return EXIT_SUCCESS;
        }
        else if (not sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
          buffer = false;
        }
          //Play Music
          if (Titlemusic.getStatus() != 2 && settings.playMusic()){
              Titlemusic.play();
            }
          //Go to Settings or Gameplay
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
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            nextState = TitleScreen;
            buffer = true;
          }
          window.clear();
          window.draw(text4);
          window.draw(text5);
          window.display();
          break;
        case GameScreen:
          if(Titlemusic.getStatus() != 0){Titlemusic.stop();}
          if(Gamemusic.getStatus() !=2 && settings.playMusic()){Gamemusic.play();}
          text6.setString(std::to_string(main_character.get_xPosition()) + "," + std::to_string(main_character.get_yPosition()));
          //Check for character movement. See Player.hpp/Player.cpp
          main_character.move();
          window.clear();
          window.draw(main_character.get_sprite());
          window.draw(text6);
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