#include <gtest/gtest.h>
#include "../inc/player.hpp"
#include <string>
#include <iostream>

sf::Sprite TestSprite;
sf::Texture TestTexture;
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