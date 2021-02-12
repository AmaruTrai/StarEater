#pragma once

#include <vector>

// Declaring
struct ObjectPoint;
class Object;
using ObjectPointMatrix = std::vector<std::vector<ObjectPoint>>;

// The structure describing the position on the map
struct Position {
	int x_ = -1;
	int y_ = -1;
};

// Operator ==, !=, +, - overloading
bool operator==(const Position& lhs, const Position& rhs);
bool operator!=(const Position& lhs, const Position& rhs);
Position operator+(const Position& lhs, const Position& rhs);
Position operator-(const Position& lhs, const Position& rhs);

// The structure describing the position of a point of some object on the map
struct ObjectPoint {

	Object* ñurrentObject_ = nullptr;
	Position pos_;
};

// Definition a generic object class
class Object {
public:
	// Constructor/Destructor
	Object();
	virtual ~Object() = default;
	
	// Copy constructor
	Object(const Object& obj) = default;;

	// Move constructor
	Object(Object&& obj) = default;

	// Overloading the operator =
	Object& operator=(const Object& rhs) = default;

	// Overloading the move operator =
	Object& operator=(Object&& rhs) = default;

	// Getters
	Position& getPos();
	ObjectPointMatrix& getShell();

	// Method changes the position of the object
	void setPos(const Position& newPos);

protected:
	ObjectPointMatrix shell_;
	Position pos_;
};


// Class describing the game space
class GameSpace {

public:
	// Constructor/Destructor
	GameSpace(size_t xSize, size_t ySize);
	~GameSpace() = default;

	// Method that set the position of the Object on the map
	bool setPos(Object* obj, size_t x, size_t y);

	// Method that find target near obj
	bool findNear(Object* obj, Object* target);

	// Method to remove object and shell from space
	void deleteFromSpace(Object* obj);

private:
	// Helper method
	int absPlus(const int& num);

	// This method checks for the intersection of the obj with other objects.
	bool checkOffset(ObjectPointMatrix& objShell, size_t xBias, size_t yBias);

	// Method adding object to space
	void addToSpace(Object* obj, int xBias, int yBias);

	ObjectPointMatrix space_;
	size_t xSize_ = 0;
	size_t ySize_ = 0;
};