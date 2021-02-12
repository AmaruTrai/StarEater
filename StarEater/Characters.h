#pragma once
#include <memory>
#include <vector>
#include <string>

#include "GameSpace.h"
#include "SDL.h"
#include "SDL_image.h"


static constexpr int MY_HERO_SIZE = 9;
static constexpr int WALL_SIZE = 9;
static constexpr int KEY_SIZE = 3;

// A class describes the general structure of any character
class  Character : public Object {

public:
	// Constructor/Destructor
	Character() = default;
	virtual ~Character();
	// Method describing the reaction to an event
	virtual bool react(SDL_Event key);
	// Method describing the action of the object
	virtual bool update();

};


class MY_Hero : public Character {
public:
	// Constructor/Destructor
	MY_Hero(std::shared_ptr<GameSpace> map);
	virtual ~MY_Hero() = default;

	// Method describing the reaction to an event
	virtual bool react(SDL_Event key) override;

	// Method describing the action of the object
	virtual bool update() override;

	bool move(size_t x, size_t y);

private:
	// Copy constructor
	MY_Hero(const MY_Hero& obj) = delete;

	// Move constructor
	MY_Hero(MY_Hero&& obj) = delete;

	// Overloading the operator =
	MY_Hero& operator=(const MY_Hero& rhs) = delete;

	// Overloading the move operator =
	MY_Hero& operator=(MY_Hero&& rhs) = delete;



	// Variables describing the state of the character
	size_t fJump_ = 0;
	bool fLeft_ = false;
	bool fRight_ = false;

	std::shared_ptr<GameSpace> map_;

	//Method implementing map step
	void jump();
};

class Wall : public Character {
public:
	// Constructor/Destructor
	Wall();
	virtual ~Wall() = default;

	// Method describing the reaction to an event
	virtual bool react(SDL_Event key) override;

	// Method describing the action of the object
	virtual bool update() override;

};

class Key : public Character {
public:
	// Constructor/Destructor
	Key();
	virtual ~Key() = default;

	// Method describing the reaction to an event
	virtual bool react(SDL_Event key) override;

	// Method describing the action of the object
	virtual bool update() override;

};