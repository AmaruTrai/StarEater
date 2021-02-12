#include "Graphics.h"

Texture::Texture(SDL_Texture* texture): texture_(texture){
}

Texture::~Texture() {
	if (texture_) {
		SDL_DestroyTexture(texture_);
	}
}

SDL_Texture* Texture::getTexture() {
	return texture_;
}

Texture::Texture(Texture&& obj) noexcept {
	SDL_Texture* texture = texture_;
	texture_ = obj.texture_;
	obj.texture_ = texture;
}
Texture& Texture::operator=(Texture&& obj) noexcept {
	SDL_Texture* texture = texture_;
	texture_ = obj.texture_;
	obj.texture_ = texture;
	return *this;
}

// Constructor
Painter::Painter(size_t width, size_t height) {
	height_ = height;
	width_ = width;
	window_ = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_SHOWN);
	if (window_ == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		init_ = 1;
	}
	render_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render_ == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		init_ = 2;
	}
}

// Destructor
Painter::~Painter() {
	if (render_ != nullptr) { SDL_DestroyRenderer(render_); }
	if (textureFont_ != nullptr) { SDL_DestroyTexture(textureFont_); }
	if (window_ != nullptr) { SDL_DestroyWindow(window_); }
}


// Method that sets the relationship between window resolution and field size
void Painter::setRes(int wRes, int hRes) {
	wRes_ = wRes;
	hRes_ = hRes;
}

// Character rendering method
bool Painter::Paint_ch(std::shared_ptr<Character> pChar) {
	SDL_Rect pos;
	int posX = pChar->getPos().x_;
	int posY = pChar->getPos().y_;
	if (posX == -1 || posY == -1) {
		return false;
	}
	pos.x = posX * wRes_- WALL_SIZE ;
	pos.y = posY * hRes_ - WALL_SIZE;
	pos.w = WALL_SIZE * wRes_+3;
	pos.h = WALL_SIZE * wRes_+3;
	if (textureMap_.find(typeid(*pChar.get()))!= textureMap_.end()) {
		SDL_Texture* texture = textureMap_.at(typeid(*pChar.get())).getTexture();
		SDL_RenderCopy(render_, texture, NULL, &pos);
		return true;
	}
	return false;
}

// Window refresh method
void Painter::Update() {
	SDL_RenderPresent(render_);
	SDL_RenderClear(render_);
}

bool Painter::Create_font(const std::string& file) {
	bool reply = true;
	SDL_Surface* Font = IMG_Load(file.c_str());
	textureFont_ = SDL_CreateTextureFromSurface(render_, Font);
	if (textureFont_ == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		reply = false;
	}
	SDL_FreeSurface(Font);
	return reply;
}

// Font rendering method
bool Painter::Render_font() {
	SDL_Rect pos{ 0,0,width_,height_ };
	SDL_RenderCopy(render_, textureFont_, NULL, &pos);
	return true;
}

bool Painter::addTexture(std::type_index indexCha, const std::string& file) {
	SDL_Surface* Font = IMG_Load(file.c_str());
	if (Font == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	Uint32 colorkey = SDL_MapRGB(Font->format, 0, 0, 0);
	SDL_SetColorKey(Font, SDL_TRUE, colorkey);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render_, Font);
	if (textureFont_ == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	auto reply = textureMap_.emplace(indexCha, Texture(texture));
	return reply.second;
}
