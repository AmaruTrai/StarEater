#pragma once
#include <vector>
#include <stdlib.h>
#include <algorithm>

#include "SDL.h"
#include "SDL_image.h"
#include "Characters.h"




class  Virtual_Master {
public:
	Virtual_Master(size_t x, size_t y);
	~Virtual_Master() = default;

	// Method returns a pointer to a character from the list
	std::shared_ptr<Character> get_char(int i);
	// The method checks the reaction of the characters to the command
	void react(SDL_Event com);
	// Method that updates the state of all characters
	void update();
	// Method that returns the number of characters in the list
	size_t get_char_num();
	// Method that returns cha_list&
	std::vector<std::shared_ptr<Character>>& get_list();


private:
	// Method checks the interaction of characters
	int checkInteraction();
	//Method for creating a map wall
	bool creatWall(std::string& file);

	std::vector<std::shared_ptr<Character>> key_list;
	std::vector<std::shared_ptr<Character>> hero_list;
	std::vector<std::shared_ptr<Character>> cha_list;
	std::shared_ptr<GameSpace> space_;
	
};

