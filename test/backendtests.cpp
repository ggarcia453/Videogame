#include <gtest/gtest.h>
#include "../inc/constants.hpp"
#include "../inc/player.hpp"

TEST(CONSTANTS, CONSTANTS_ARE_SET){
    EXPECT_EQ(SCRWIDTH, 420);
    EXPECT_EQ(SCRHEIGHT, 420);
}

TEST(CONSTANTS, ENUM_IS_VALID){
    EXPECT_NE(Exit, TitleScreen);
    EXPECT_NE(Exit, PauseScreen);
    EXPECT_NE(Exit, GameScreen);
    EXPECT_NE(Exit, Questions);
    EXPECT_NE(TitleScreen, PauseScreen);
    EXPECT_NE(TitleScreen, GameScreen);
    EXPECT_NE(TitleScreen, Questions);
    EXPECT_NE(PauseScreen, GameScreen);
    EXPECT_NE(PauseScreen, Questions);
    EXPECT_NE(GameScreen, Questions);
}

TEST(POSITIONTEST, POSITION_IS_VALID){
    position p = {1,1};
    EXPECT_EQ(p.x, 1);
    EXPECT_EQ(p.y, 1);
    p.x++;
    p.y = 10;
    EXPECT_EQ(p.x, 2);
    EXPECT_EQ(p.y, 10);
}
