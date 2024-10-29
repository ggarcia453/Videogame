#include <gtest/gtest.h>
#include "../inc/items.hpp"


sf::Sprite TestSprite1;
sf::Texture TestTexture1;
sf::Sprite TestSprite2;
sf::Texture TestTexture2;

const std:: string ast_path = "../assets/";
TEST(ITEMS, ITEMS_DISTINCT){
    if (!TestTexture1.loadFromFile(ast_path + "img/kfc_goku.jpg") || !TestTexture2.loadFromFile(ast_path + "img/key.jpg")){
        GTEST_SKIP() << "Could not load assets. SKipp;ing tests";
    }
    TestSprite1.setTexture(TestTexture1);
    TestSprite2.setTexture(TestTexture2);
    Item item1(&TestSprite1, {0,0}, {4,4}, 2);
    Item item2(&TestSprite1, {1,1}, {5,5}, 2);
    Item item3(&TestSprite2, {0,0}, {4,4}, 2);
    EXPECT_EQ(item1, item2);
    EXPECT_NE(item1, item3);
}

TEST(ITEMS, VISIBILITYTESTS){
    if (!TestTexture1.loadFromFile(ast_path + "img/kfc_goku.jpg") || !TestTexture2.loadFromFile(ast_path + "img/key.jpg")){
        GTEST_SKIP() << "Could not load assets. SKipp;ing tests";
    }
    TestSprite1.setTexture(TestTexture1);
    Item item1(&TestSprite1, {0,0}, {4,4}, 2);
    EXPECT_TRUE(item1.show());
}