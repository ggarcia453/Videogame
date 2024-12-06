#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

const short SCRWIDTH = 420; 
const short SCRHEIGHT = 420;

const float player_scale = 0.105;
const float item_scale = 0.105;

typedef enum {Exit, TitleScreen, PauseScreen, GameScreen, TutorialScreen, Questions} States;

struct position{
    short x;
    short y;
};

#endif