#pragma once

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "Graphics.h"
#include "Master.h"





class Game {
public:
	Game();
	~Game();
	unsigned int Game_main();
private:
	std::shared_ptr<Virtual_Master> master_;
	std::shared_ptr <Painter> window_;
	bool run = false;
};
