#include "Master.h"
#include "MapReader.h"


// Constructor
Virtual_Master::Virtual_Master(size_t x, size_t y) {
	std::string mapFile = "Image\\Map.bmp";
	space_ = std::shared_ptr<GameSpace>(new GameSpace(x, y));
	creatWall(mapFile);

	cha_list.push_back(std::shared_ptr<Character>(new MY_Hero(space_)));
	hero_list.push_back(cha_list.at(cha_list.size() - 1));
	space_->setPos(cha_list[cha_list.size() - 1].get(), 25, 20);

	cha_list.push_back(std::shared_ptr<Character>(new Key()));
	key_list.push_back(cha_list.at(cha_list.size() - 1));
	space_->setPos(cha_list[cha_list.size() - 1].get(), 190, 200);

	cha_list.push_back(std::shared_ptr<Character>(new Key()));
	key_list.push_back(cha_list.at(cha_list.size() - 1));
	space_->setPos(cha_list[cha_list.size() - 1].get(), 50, 200);

}


std::shared_ptr<Character> Virtual_Master::get_char(int i) {

	return cha_list.at(i);
}

size_t  Virtual_Master::get_char_num() {
	return cha_list.size();
}

// Method that updates the state of all characters
void Virtual_Master::update() {
	size_t size = cha_list.size();
	for (size_t i = 0; i < size; ++i) {
		cha_list.at(i)->update();
	}
	int check = checkInteraction();
	if (check != -1) {
		space_->deleteFromSpace(key_list.at(check).get());
		auto res = std::find(cha_list.begin(), cha_list.end(), key_list.at(check));
		if (res != cha_list.end()) {
			cha_list.erase(res);
		}
		key_list.erase(key_list.begin() + check);
	}
}

// The method checks the reaction of the characters to the command
void Virtual_Master::react(SDL_Event com) {
	size_t size = cha_list.size();
	for (size_t i = 0; i < size; ++i) {
		cha_list.at(i)->react(com);
	}
}

//Method for creating a map wall
bool Virtual_Master::creatWall(std::string& file) {
	matrixRGB mRGB = read(file);
	size_t width = mRGB.size();
	if (!width) {
		return false;
	}
	size_t chaCounter = 0;
	size_t height = mRGB[0].size();
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			if (mRGB[i][j].rgbBlue == 0 && mRGB[i][j].rgbRed == 0 && mRGB[i][j].rgbGreen == 0) {
				cha_list.push_back(std::shared_ptr<Character>(new Wall()));
				space_->setPos(cha_list[chaCounter].get(), (i)*10+ WALL_SIZE/2, (j)*10 + WALL_SIZE / 2);
				chaCounter++;
			}
		}
	}
	return true;
}

// Method that returns cha_list&
std::vector<std::shared_ptr<Character>>& Virtual_Master::get_list() {
	return cha_list;
}

// Method checks the interaction of characters
int Virtual_Master::checkInteraction() {
	for (size_t i = 0; i < key_list.size(); ++i) {
		if (space_->findNear(hero_list.at(0).get(), key_list.at(i).get())) {
			return i;
		}
	}
	return -1;
}
