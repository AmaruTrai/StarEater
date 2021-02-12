#include "Game.h"






// Game
Game::Game() {
	run = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		run = false;
	}
	std::string heroFile = "Image\\Character.png";
	std::string wallFile = "Image\\Wall.png";
	std::string keyFile = "Image\\Key.png";
	std::string fontFile = "Image\\1876.png";

	size_t x = 300;
	size_t y = 300;
	size_t width = 900;
	size_t height = 900;
	window_ = std::shared_ptr<Painter>(new Painter(width, height));
	window_->setRes(width/x, height/y);
	master_ = std::shared_ptr<Virtual_Master>(new Virtual_Master(x, y));
	window_->Create_font(fontFile);
	window_->addTexture(typeid(MY_Hero), heroFile);
	window_->addTexture(typeid(Wall), wallFile);
	window_->addTexture(typeid(Key), keyFile);
}

Game::~Game() {
	IMG_Quit();
	SDL_Quit();
}

unsigned int Game::Game_main() {

	int reply = 0;
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			default:
				master_->react(event);
				break;
			}
		}
		master_->update();
		window_->Render_font();
		size_t charNum = master_->get_char_num();
		for (size_t i = 0; i < charNum; i++) {
			window_->Paint_ch(master_->get_char(i));
		}
		window_->Update();
		SDL_Delay(5);
	}
	return reply;
}
