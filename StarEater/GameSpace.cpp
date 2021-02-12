#include "GameSpace.h"

// Operator == overloading
bool operator==(const Position& lhs, const Position& rhs) {
	return (lhs.x_ == rhs.x_) && (lhs.y_ == rhs.y_);
}

// Operator != overloading
bool operator!=(const Position& lhs, const Position& rhs) {
	return !(lhs == rhs);
}

// Operator + overloading
Position operator+(const Position& lhs, const Position& rhs) {
	return Position{ lhs.x_ + rhs.x_ , lhs.y_ + rhs.y_ };
}

// Operator - overloading
Position operator-(const Position& lhs, const Position& rhs) {
	return Position{ lhs.x_ - rhs.x_ , lhs.y_ - rhs.y_ };
}


// Constructor
Object::Object() {
	shell_ = ObjectPointMatrix(1, std::vector<ObjectPoint>(1, { this, {0,0} }));
}


// // Getters
Position& Object::getPos() {
	return pos_;
}

ObjectPointMatrix& Object::getShell() {
	return shell_;
}

// Method changes the position of the object and shell_
void Object::setPos(const Position& newPos) {
	pos_ = newPos;
}

// Constructor, creates a game space with a size x * y
GameSpace::GameSpace(size_t xSize, size_t ySize) : xSize_(xSize), ySize_(ySize) {
	space_ = ObjectPointMatrix(xSize_, std::vector<ObjectPoint>(ySize_));
}


// This method checks for the intersection of the obj with other objects.
bool GameSpace::checkOffset(ObjectPointMatrix& objShell, size_t xBias, size_t yBias) {
	size_t sizeX = objShell.size();
	if (!sizeX) {
		return false;
	}
	size_t sizeY = objShell[0].size();
	if (!sizeY) {
		return false;
	}
	if (!(xSize_ > xBias && xBias >= 0)) {
		return false;
	}
	if (!(ySize_ > yBias && yBias >= 0)) {
		return false;
	}
	for (size_t i = 0; i < sizeX; i++) {
		for (size_t j = 0; j < sizeY; j++) {
			int x = objShell[i][j].pos_.x_ + xBias;
			int y = objShell[i][j].pos_.y_ + yBias;
			if ((xSize_ > x > 0) && (ySize_ > y > 0)) {
				if (space_[x][y].ñurrentObject_) {
					if (space_[x][y].ñurrentObject_ != objShell[0][0].ñurrentObject_) {
						return false;
					}
				}
			}
		}
	}
	return true;
}


// Method to remove object and shell from space
void GameSpace::deleteFromSpace(Object* obj) {
	int xObj = obj->getPos().x_;
	int yObj = obj->getPos().y_;
	ObjectPointMatrix& objShell = obj->getShell();
	size_t sizeX = objShell.size();
	size_t sizeY = objShell[0].size();
	for (size_t i = 0; i < sizeX; i++) {
		for (size_t j = 0; j < sizeY; j++) {
			int x = objShell[i][j].pos_.x_ + xObj;
			int y = objShell[i][j].pos_.y_ + yObj;
			if ((xSize_ > x && x >= 0) && (ySize_ > y && y >= 0)) {
				space_[x][y].ñurrentObject_ = nullptr;
			}
		}
	}
	space_[xObj][yObj].ñurrentObject_ = nullptr;
}

// Method adding object to space
void GameSpace::addToSpace(Object* obj, int xBias, int yBias) {
	ObjectPointMatrix& objShell = obj->getShell();
	size_t sizeX = objShell.size();
	size_t sizeY = objShell[0].size();
	for (size_t i = 0; i < sizeX; i++) {
		for (size_t j = 0; j < sizeY; j++) {
			int x = objShell[i][j].pos_.x_ + xBias;
			int y = objShell[i][j].pos_.y_ + yBias;
			if ((xSize_> x && x >= 0) && (ySize_ > y && y >= 0)) {
				space_[x][y].ñurrentObject_ = obj;
			}
		}
	}
	space_[xBias][yBias].ñurrentObject_ = obj;
	obj->setPos({ xBias, yBias });
}


bool GameSpace::setPos(Object* obj, std::size_t x, std::size_t y) {
	if ((xSize_ > x && x >= 0) && (ySize_ > y && y >= 0)) {
		if (!space_[x][y].ñurrentObject_) {
			int xObj = obj->getPos().x_;
			int yObj = obj->getPos().y_;
			ObjectPointMatrix& objShell = obj->getShell();
			if (!checkOffset(objShell, x, y)) {
				return false;
			}
			if (xObj != -1 && yObj != -1) {
				deleteFromSpace(obj);
			}
			addToSpace(obj, x, y);
		}
	}
	return true;
}

// Method that find target near obj
bool GameSpace::findNear(Object* obj, Object* target) {
	ObjectPointMatrix& objShell = obj->getShell();
	int xObj = obj->getPos().x_;
	int yObj = obj->getPos().y_;
	size_t sizeX = objShell.size();
	size_t sizeY = objShell[0].size();
	for (size_t i = 0; i < sizeX; i++) {
		for (size_t j = 0; j < sizeY; j++) {
			int x = objShell[i][j].pos_.x_ + xObj;
			int y = objShell[i][j].pos_.y_ + yObj;
			x = absPlus(x);
			y = absPlus(y);
			if ((xSize_ > x > 0) && (ySize_ > y > 0)) {
				if (space_[x][y].ñurrentObject_ == target) {
					return true;
				}
			}
		}
	}
	return false;
}

// Helper method
int GameSpace::absPlus(const int& num) {
	int reply = num;
	if (reply > 0) {
		++reply;
	}
	else if (reply < 0) {
		--reply;
	}
	return reply;
}