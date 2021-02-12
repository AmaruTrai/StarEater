#include "Characters.h"


// Destructor
Character::~Character() {
}

// Method describing the reaction to an event
bool Character::react(SDL_Event key) {
	return false;
}

bool Character::update() {
	return false;
}

// Standard character constructor 
MY_Hero::MY_Hero(std::shared_ptr<GameSpace> map) :map_(map) {
	shell_ = ObjectPointMatrix(4, std::vector<ObjectPoint>(MY_HERO_SIZE-1, {this}));
	int myHeroHalf = MY_HERO_SIZE / 2;
	for (int j = 0; j < MY_HERO_SIZE-1; ++j) {
		shell_[0][j].pos_ = Position{-myHeroHalf + j, myHeroHalf};
	}
	for (int  j = 0; j < MY_HERO_SIZE - 1; ++j) {
		shell_[1][j].pos_ = Position{ myHeroHalf, myHeroHalf - j};
	}
	for (int  j = 0; j < MY_HERO_SIZE - 1; ++j) {
		shell_[2][j].pos_ = Position{ myHeroHalf - j,-myHeroHalf };
	}
	for (int  j = 0; j < MY_HERO_SIZE - 1; ++j) {
		shell_[3][j].pos_ = Position{ -myHeroHalf, -myHeroHalf + j};
	}
}

bool MY_Hero::update() {
	bool reply = false;
	if (fLeft_ && fRight_) {
	}
	else if (fLeft_) {
		reply = move(pos_.x_ - 1, pos_.y_);
	}
	else if (fRight_) {
		reply = move(pos_.x_ + 1, pos_.y_);
	}
	if (fJump_) {
		reply = move(pos_.x_, pos_.y_ - 1);
		reply == false ? fJump_ = 0 : --fJump_;
	}
	else {
		reply = move(pos_.x_, pos_.y_ + 1);
	}
	return reply;
}

// Method describing the reaction to an event
bool MY_Hero::react(SDL_Event key) {
	bool reply = false;
	//(key.key.keysym.sym)
	switch (key.type) {
	case SDL_KEYDOWN:
		switch (key.key.keysym.sym) {
		case SDLK_a:
			fLeft_ = true;
			break;
		case SDLK_d:
			fRight_ = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (key.key.keysym.sym) {
		case SDLK_SPACE:
			jump();
			break;
		case SDLK_a:
			fLeft_ = false;
			break;
		case SDLK_d:
			fRight_ = false;
			break;
		}
		break;
	}
	return reply;
}





void MY_Hero::jump() {
	fJump_ = WALL_SIZE;
}


bool MY_Hero::move(size_t x, size_t y) {
	return map_->setPos(this, x, y);
}


Wall::Wall(){
	shell_ = ObjectPointMatrix(4, std::vector<ObjectPoint>(WALL_SIZE - 1, { this }));
	int myWallHalf = WALL_SIZE / 2;
	for (int j = 0; j < WALL_SIZE - 1; ++j) {
		shell_[0][j].pos_ = Position{ -myWallHalf + j, myWallHalf };
	}
	for (int j = 0; j < WALL_SIZE - 1; ++j) {
		shell_[1][j].pos_ = Position{ myWallHalf, myWallHalf - j };
	}
	for (int j = 0; j < WALL_SIZE - 1; ++j) {
		shell_[2][j].pos_ = Position{ myWallHalf - j,-myWallHalf };
	}
	for (int j = 0; j < WALL_SIZE - 1; ++j) {
		shell_[3][j].pos_ = Position{ -myWallHalf, -myWallHalf + j };
	}
}

// Method describing the reaction to an event
bool Wall::react(SDL_Event key){
	return false;
}

// Method describing the action of the object
bool Wall::update(){
	return false;
}

// Constructor/Destructor
Key::Key() {
	shell_ = ObjectPointMatrix(1, std::vector<ObjectPoint>(KEY_SIZE - 1, { this }));
	for (int i = 0; i < KEY_SIZE - 1; ++i) {
		shell_[0][i].pos_ = Position{ 0, KEY_SIZE / 2 - i };
	}
}

// Method describing the reaction to an event
bool Key::react(SDL_Event key) {
	return false;
}

// Method describing the action of the object
bool Key::update() {
	return false;
}

