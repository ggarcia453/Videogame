#include <gtest/gtest.h>
#include "../inc/player.hpp"
#include <string>
#include <iostream>

sf::Sprite TestSprite;
sf::Texture TestTexture;
sf::Texture ItemTexture;
const std:: string ast_path = "../assets/";

TEST(PLAYERTEST, GETTERS_TEST){
   if (!TestTexture.loadFromFile(ast_path + "img/kfc_goku.jpg")){
      std::cout << "Reduced Test suite due to load error";
      Player testplayer;
      EXPECT_EQ(testplayer.get_xPosition(), 1);
      EXPECT_EQ(testplayer.get_yPosition(), 1);
   }
   else{
      Player player(&TestSprite, TestTexture);
      //The next values depend on the image being loaded as the asset.
      EXPECT_EQ(player.get_xlimit(), 24);
      EXPECT_EQ(player.get_ylimit(), 25);
      const int testx = player.get_xlimit();
      const int testy = SCRHEIGHT - player.get_ylimit();
      EXPECT_EQ(player.get_x(), testx);
      EXPECT_EQ(player.get_y(), testy);
   }
}


TEST(PLAYERTEST, SPRITESETTEST){
   if (!TestTexture.loadFromFile(ast_path + "img/kfc_goku.jpg")){
    GTEST_SKIP() << "Cannot load test asset";
  }
  Player player(&TestSprite, TestTexture);
  EXPECT_EQ(player.get_sprite().getTexture(), &TestTexture);
}

TEST(PLAYERTEST, MOVEMENT_WASD) {
   if (!TestTexture.loadFromFile(ast_path + "img/kfc_goku.jpg")){
      GTEST_SKIP() << "Cannot load test asset";
   }
   Player player(&TestSprite, TestTexture);
   player.set_wasd(true);
   float initx = player.get_x();
   float inity = player.get_y();
   player.move_test(sf::Keyboard::W);
   EXPECT_LT(player.get_y(), inity);
   player.move_test(sf::Keyboard::D);
   EXPECT_GT(player.get_x(), initx);
   player.move_test(sf::Keyboard::A);
   EXPECT_EQ(player.get_x(), initx);
   player.move_test(sf::Keyboard::S);
   EXPECT_EQ(player.get_y(), inity);
}

TEST(PLAYERTEST, MOVEMENT_ARROW) {
   if (!TestTexture.loadFromFile(ast_path + "img/kfc_goku.jpg")){
      GTEST_SKIP() << "Cannot load test asset";
   }
   Player player(&TestSprite, TestTexture);
   player.set_wasd(false);
   float initx = player.get_x();
   float inity = player.get_y();
   player.move_test(sf::Keyboard::Up);
   EXPECT_LT(player.get_y(), inity);
   player.move_test(sf::Keyboard::Right);
   EXPECT_GT(player.get_x(), initx);
   player.move_test(sf::Keyboard::Left);
   EXPECT_EQ(player.get_x(), initx);
   player.move_test(sf::Keyboard::Down);
   EXPECT_EQ(player.get_y(), inity);
}

TEST(PLAYERTEST, BOUNDARY_CHECK) {
    if (!TestTexture.loadFromFile(ast_path + "img/kfc_goku.jpg")){
        GTEST_SKIP() << "Cannot load test asset";
    }
    Player player(&TestSprite, TestTexture);
    for(int i = 0; i < 1000; i++) {
        player.move_test(sf::Keyboard::Right);
    }
    EXPECT_LE(player.get_x(), SCRWIDTH);
    for(int i = 0; i < 1000; i++) {
        player.move_test(sf::Keyboard::Down);
    }
    EXPECT_LE(player.get_y(), SCRHEIGHT);
}

TEST(PLAYERTEST, LEVEL_PROGRESSION) {
   if (!TestTexture.loadFromFile(ast_path + "img/kfc_goku.jpg")){
      GTEST_SKIP() << "Cannot load test asset";
   }
   Player player(&TestSprite, TestTexture);
   position initial_pos = player.get_pos();
   player.level_up();
   position new_pos = player.get_pos();
   EXPECT_EQ(initial_pos.x, new_pos.x);
   EXPECT_EQ(initial_pos.y, new_pos.y);
}

TEST(PLAYERTEST, DIMENSION_GETTERS) {
    if (!TestTexture.loadFromFile(ast_path + "img/kfc_goku.jpg")){
        GTEST_SKIP() << "Cannot load test asset";
    }
    Player player(&TestSprite, TestTexture);
    
    EXPECT_GT(player.get_width(), 0);
    EXPECT_GT(player.get_height(), 0);
}