#pragma once
#include <iostream>
#include <map>
#include <typeinfo>
#include <typeindex>

#include "SDL.h"
#include "SDL_image.h"
#include "Characters.h"


// Class wrapper over SDL_Texture
class Texture {
public:
	Texture() = default;
	Texture(SDL_Texture* texture);
	Texture(Texture&& obj) noexcept;
	Texture& operator=(Texture&& obj) noexcept;
	~Texture();
	SDL_Texture* getTexture();
private:
	Texture(const Texture&) = delete;;
	Texture& operator=(const Texture&) = delete;

	SDL_Texture* texture_ = nullptr;
};


// The class responsible for drawing graphics
class  Painter {
public:

	// Constructor/Destructor
	Painter(size_t width, size_t height);
	~Painter();

	// Method that sets the relationship between window resolution and field size
	void setRes(int wRes, int hRes);
	// Character rendering method
	bool Paint_ch(std::shared_ptr<Character> pChar);
	// Font creating method
	bool Create_font(const std::string& file);
	// Font rendering method
	bool Render_font();
	// Window refresh method
	void Update();
	// Method for adding texture to the character
	bool addTexture(std::type_index indexCha, const std::string& file);


private:
	// Block
	Painter(Painter& rsh) = delete;
	Painter(Painter&& rsh) = delete;
	Painter& operator=(Painter& rsh) = delete;
	Painter& operator=(Painter&& rsh) = delete;

	SDL_Window* window_ = nullptr;
	SDL_Renderer* render_ = nullptr;
	SDL_Texture* textureFont_ = nullptr;

	std::map<std::type_index, Texture> textureMap_;
	size_t width_ = 0;
	size_t height_ = 0;
	int wRes_ = 0;
	int hRes_ = 0;
	size_t init_ = 0;
};