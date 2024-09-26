#include "config.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "inc/player.hpp"
#include "inc/constants.hpp"
#include "inc/settings.hpp"
#include "inc/items.hpp"
#include <thread>
sf::Mutex mutex;

States state_handler(States current, sf::Keyboard::Key key){
  if (key == sf::Keyboard::Escape){
    switch (current){
    case PauseScreen:
      return GameScreen;
    case GameScreen:
      return PauseScreen;
    case Questions:
      return TitleScreen;
    case TitleScreen:
      return Exit;
    default:
      return current;
    }
  }
  else if (key == sf::Keyboard::Q){
    switch (current){
      case PauseScreen:
        return TitleScreen;
      case TitleScreen:
        return Questions;    
    default:
      return current;
    }
  }
  else if (key == sf::Keyboard::P){
    switch (current)
    {
    case TitleScreen:
      return GameScreen;
    default:
      return current;
    }
  }
  else {
  return current;}
}

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
  sf::Text text7;
  sf::Text text8;
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

  //text7 setup 
  sf::Thread t7(std::bind(&string_setup, &text7, "M to change music. Its On", font, sf::Vector2f(SCRWIDTH/2.0f, SCRHEIGHT/2.0f - SCRHEIGHT/5.0f + 2)));
  t7.launch();

  sf::Thread t8(std::bind(&string_setup, &text8, "W to play with WASD", font, sf::Vector2f(SCRWIDTH/2.0f, SCRHEIGHT/2.0f)));
  t8.launch();

  //Sprite Setup
  Player main_character(&Sprite1, Texture1);
  sf::Thread t6(std::bind(&string_setup, &text6, std::to_string(main_character.get_xPosition()) + "," + std::to_string(main_character.get_yPosition()), font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f)));
  t6.launch();
  // string_setup(&text6, pos_string, font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f));

  //Titlemusic set up  
  Titlemusic.setLoop(true);
  Titlemusic.play();
  Gamemusic.setLoop(true);

  //State Setup
  States curState = TitleScreen;
  States nextState = TitleScreen;
  t1.wait();
  t2.wait();
  t3.wait();
  Sprite2.setTexture(Texture2);
  Item key(&Sprite2, {SCRWIDTH / 2, SCRHEIGHT / 2}, {6,6});
  while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){window.close();}
      if (event.type == sf::Event::KeyReleased){
        if (curState == Questions){
          settings.check_changes(event.key.code);
          main_character.set_wasd(settings.CharMove());
        }
        nextState = state_handler(curState, event.key.code);
      }
    }
    switch (curState){
      case TitleScreen:
          //Play Music
          text1.setString("Title Screen");
          if (Titlemusic.getStatus() != 2 && settings.playMusic()){
              Titlemusic.play();
            }
          window.clear();
          window.draw(text1);
          window.draw(text2);
          window.draw(text3);
          window.display();
          break;
        case Questions:
          if(Titlemusic.getStatus() == 2){Titlemusic.pause();}
          if (settings.playMusic()){
            text7.setString("M to change music. Its On");
          }
          else{
            text7.setString("M to change music. Its Off");
          }
          if (!settings.CharMove()){
            text8.setString("W to play with WASD");
          }
          else{
            text8.setString("W to play with arrows");
          }
          window.clear();
          window.draw(text4);
          window.draw(text5);
          window.draw(text7);
          window.draw(text8);
          window.display();
          break;
        case GameScreen:
          if(Titlemusic.getStatus() != 0){Titlemusic.stop();}
          if(Gamemusic.getStatus() !=2 && settings.playMusic()){Gamemusic.play();}
          text6.setString(std::to_string(main_character.get_xPosition()) + "," + std::to_string(main_character.get_yPosition()));
          main_character.move();
          window.clear();
          window.draw(main_character.get_sprite());
          key.draw(&window, main_character.get_pos(), main_character.get_x(), main_character.get_y(), main_character.get_height(), main_character.get_width());
          window.draw(text6);
          window.display();
          break;
        case PauseScreen:
          if (Gamemusic.getStatus() == 2){Gamemusic.pause();}
          text1.setString("Paused");
          window.clear();
          window.draw(text1);
          window.display();
          break;
        case Exit:
          return EXIT_SUCCESS;
        default:
          std:: cerr << "SOmething is off" << std:: endl;
          return EXIT_FAILURE;
        } 
        curState = nextState;
    }
  return EXIT_SUCCESS;
  
}