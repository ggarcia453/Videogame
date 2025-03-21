#include "config.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "inc/player.hpp"
#include "inc/constants.hpp"
#include "inc/settings.hpp"
#include "inc/items.hpp"
#include <thread>
#include <stdlib.h>
#include <functional>
sf::Mutex mutex;

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
sf::Texture Background1;
sf::Texture Background2;
sf::Texture Background3;
sf::Texture Background4;
sf::Sprite BackgroundSprite;
std::vector<Item> item_list;

//State Setup
States curState = TitleScreen;
States nextState = TitleScreen;
short level = 1;
std::string next_level;
bool progressed = false;
bool can_progress = false;

void drawAllItems(sf::RenderWindow* w, Player* main_character){
  for (auto& ittem: item_list){
    if (ittem.draw(w, main_character->get_pos(), main_character->get_x(), main_character->get_y(), main_character->get_height(), main_character->get_width(), level)){
      main_character->add_item(&ittem);
    }
  }
}

void changeBackground(short level){
  if (level== 3){
    BackgroundSprite.setTexture(Background2);
    BackgroundSprite.setScale(0.5,1.2);
  }
  else if (level == 5){
    BackgroundSprite.setTexture(Background3);
  }
  else if (level == 7){
    BackgroundSprite.setTexture(Background4);
  }
}

bool progress_handler(short* level, Player* main_character){
  if (*level == 1 && main_character->holding_item(&item_list.at(0))){
    return true;
  }
  if (*level == 2 && main_character->holding_item(&item_list.at(1))){
    return true;
  }
  if (*level == 3){
    return true;
  }
  return false;
}

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
      case TutorialScreen:
        return TitleScreen; 
    default:
      return current;
    }
  }
  else if (key == sf::Keyboard::P){
    switch (current)
    {
    case TitleScreen:
      return TutorialScreen;
    case TutorialScreen:
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
  srand(time(NULL)); 
  //Initialize assets and Load from assets folder
  const std:: string ast_path = "../assets/";
  if (!font.loadFromFile(ast_path + "fonts/font.ttf")){
    return -1;
  }
  if (!Texture1.loadFromFile(ast_path + "img/kfc_goku.jpg")){
    return -1;
  }
  if (!Texture2.loadFromFile(ast_path + "img/key.jpg")){
    return -1;
  }
  if (!Background1.loadFromFile(ast_path + "img/windows.jpg")){
    return -1;
  }
  if (!Background2.loadFromFile(ast_path + "img/windows2.jpg")){
    return -1;
  }
  if (!Background3.loadFromFile(ast_path + "img/windows3.jpg")){
    return -1;
  }
  if (!Background4.loadFromFile(ast_path + "img/windows4.jpg")){
    return -1;
  }
  

  BackgroundSprite.setTexture(Background1);
  BackgroundSprite.setScale(0.5,0.65);

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

  //text5 setup
  sf::Thread t5(std::bind(&string_setup,&text5, "Esc to stop questions", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f) ));
  t5.launch();
  // string_setup(&text5, "Esc to stop questions", font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f));

  //text7 setup 
  sf::Thread t7(std::bind(&string_setup, &text7, "M to change music. Its On", font, sf::Vector2f(SCRWIDTH/2.0f, SCRHEIGHT/2.0f - SCRHEIGHT/5.0f + 2)));
  t7.launch();

  //text8
  sf::Thread t8(std::bind(&string_setup, &text8, "W to play with WASD", font, sf::Vector2f(SCRWIDTH/2.0f, SCRHEIGHT/2.0f)));
  t8.launch();

  //Sprite Setup
  Player main_character(&Sprite1, Texture1);
  sf::Thread t6(std::bind(&string_setup, &text6, std::to_string(main_character.get_xPosition()) + "," + std::to_string(main_character.get_yPosition()), font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f)));
  t6.launch();
  // string_setup(&text6, pos_string, font, sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f + SCRHEIGHT/4.0f));

  //Titlemusic and Gamemusic set up  
  if (!Titlemusic.openFromFile(ast_path + "music/fnaf_title.ogg")){
    return -1;
  }
  if (!Gamemusic.openFromFile(ast_path + "music/bonnie.ogg")){
    return -1;
  }
  Titlemusic.setLoop(true);
  Titlemusic.play();
  Gamemusic.setLoop(true);
  
  t1.wait();
  t2.wait();
  t3.wait();

  //Key Item setup
  Sprite2.setTexture(Texture2);
  Item key(&Sprite2, {SCRWIDTH / 2, SCRHEIGHT / 2}, {6,6}, 1);
  // Item key2(&Sprite2, {SCRWIDTH / 2, SCRHEIGHT / 2}, {1,1}, 2);
  position key2pos = {static_cast<short>(rand()%10 + 1),static_cast<short>(rand()%10 + 1)};
  Item key2(&Sprite2, {SCRWIDTH / 2, SCRHEIGHT / 2}, key2pos, 2);
  item_list.push_back(key);
  item_list.push_back(key2);
  
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
        if (event.key.code == sf::Keyboard::Enter && progressed){
          main_character.level_up();
          progressed = false;
          level ++;
          changeBackground(level);
        }
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
          text1.setString("Settings");
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
          window.draw(text1);
          window.draw(text5);
          window.draw(text7);
          window.draw(text8);
          window.display();
          break;
        case TutorialScreen:
            text1.setString("Tutorial");
            text5.setString("\nGrab keys to progress\nthrough levels");
            text5.setPosition({SCRWIDTH/2 , SCRHEIGHT/2});
            text7.setString("P to play");
            text8.setString("Q to title screen");
            window.clear();
            window.draw(text1);
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
          window.draw(BackgroundSprite);
          window.draw(main_character.get_sprite());
          drawAllItems(&window, &main_character);
          can_progress = progress_handler(&level, &main_character);
          if (main_character.get_xPosition() == 10 && main_character.get_yPosition() == 10){
            if (can_progress){
              progressed = true;
              next_level = "Enter -> Level " + std::to_string(level  + 1);
              text1.setString(next_level);
            }else{
              text1.setString("Go get the items");
            }
            window.draw(text1);
          }
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