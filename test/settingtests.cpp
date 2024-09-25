#include <gtest/gtest.h>
#include "../inc/settings.hpp"

TEST(SETTINGS, INITALIZETESTS){
    Settings s;
    EXPECT_EQ(s.CharMove(), false);
    EXPECT_EQ(s.playMusic(), true);
}

TEST(SETTINGS, MUSICCHANGE){
    Settings s;
    s.check_changes(sf::Keyboard::M);
    EXPECT_EQ(s.playMusic(), false);
    s.check_changes(sf::Keyboard::M);
    EXPECT_EQ(s.playMusic(), true);
}

TEST(SETTINGS, MOVECHANGE){
    Settings s;
    s.check_changes(sf::Keyboard::W);
    EXPECT_EQ(s.CharMove(), true);
    s.check_changes(sf::Keyboard::W);
    EXPECT_EQ(s.CharMove(), false);
}