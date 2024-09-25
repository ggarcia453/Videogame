#include <gtest/gtest.h>
#include "../inc/player.hpp"

TEST(PLAYERTEST, GETTERS_TEST){
   Player player;
   EXPECT_EQ(player.get_xPosition(), 1);
   EXPECT_EQ(player.get_yPosition(), 1);
}

