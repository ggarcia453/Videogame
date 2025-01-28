#include <gtest/gtest.h>
#include "../inc/items.hpp"


sf::Sprite TestSprite1;
sf::Texture TestTexture1;
sf::Sprite TestSprite2;
sf::Texture TestTexture2;
const std::string ast_path = "../assets/";

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

TEST(ITEMS, COLLISIONTESTS) {
    if (!TestTexture1.loadFromFile(ast_path + "img/kfc_goku.jpg")) {
        GTEST_SKIP() << "Could not load assets. Skipping tests";
    }
    TestSprite1.setTexture(TestTexture1);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window", sf::Style::None);
    window.setActive(false);
    Item item(&TestSprite1, {0,0}, {4,4}, 2);
    EXPECT_TRUE(item.draw(&window, {4,4}, 0, 0, 100, 100, 2));
    EXPECT_FALSE(item.draw(&window, {20,20}, 0, 0, 100, 100, 2));
    EXPECT_FALSE(item.draw(&window, {4,4}, 0, 0, 100, 100, 1));
    window.close();
}

TEST(ITEMS, MAPPOSITIONGETTERS) {
    if (!TestTexture1.loadFromFile(ast_path + "img/kfc_goku.jpg")) {
        GTEST_SKIP() << "Could not load assets. Skipping tests";
    }
    TestSprite1.setTexture(TestTexture1);
    position expectedPos = {4,4};
    Item item(&TestSprite1, {0,0}, expectedPos, 2);
    position actualPos = item.get_map_pos();
    EXPECT_EQ(actualPos.x, expectedPos.x);
    EXPECT_EQ(actualPos.y, expectedPos.y);
}

TEST(ITEMS, LEVELVISBILITY_TESTS) {
    if (!TestTexture1.loadFromFile(ast_path + "img/kfc_goku.jpg")) {
        GTEST_SKIP() << "Could not load assets. Skipping tests";
    }
    TestSprite1.setTexture(TestTexture1);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window", sf::Style::None);
    window.setActive(false);
    Item item(&TestSprite1, {0,0}, {4,4}, 2);
    EXPECT_TRUE(item.draw(&window, {4,4}, 0, 0, 100, 100, 2));
    EXPECT_FALSE(item.draw(&window, {4,4}, 0, 0, 100, 100, 1));
    EXPECT_FALSE(item.draw(&window, {4,4}, 0, 0, 100, 100, 3));

    window.close();
}

TEST(ITEMS, BOUNDARYTESTS) {
    if (!TestTexture1.loadFromFile(ast_path + "img/kfc_goku.jpg")) {
        GTEST_SKIP() << "Could not load assets. Skipping tests";
    }
    TestSprite1.setTexture(TestTexture1);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window", sf::Style::None);
    window.setActive(false);
    Item item(&TestSprite1, {0,0}, {0,0}, 0);
    EXPECT_TRUE(item.draw(&window, {0,0}, 0, 0, 100, 100, 0));
    Item negativeItem(&TestSprite1, {-1,-1}, {-1,-1}, 0);
    EXPECT_TRUE(negativeItem.draw(&window, {-1,-1}, 0, 0, 100, 100, 0));
    window.close();
}

TEST(ITEMS, EQUALITYTESTS2) {
    if (!TestTexture1.loadFromFile(ast_path + "img/kfc_goku.jpg")) {
        GTEST_SKIP() << "Could not load assets. Skipping tests";
    }
    TestSprite1.setTexture(TestTexture1);
    Item item1(&TestSprite1, {0,0}, {4,4}, 2);
    Item item2(&TestSprite1, {0,0}, {4,4}, 2);
    Item item3(&TestSprite1, {0,0}, {4,4}, 3);
    EXPECT_EQ(item1, item2);
    EXPECT_NE(item1, item3);
    EXPECT_EQ(item1, item1);
}