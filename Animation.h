#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include <string>

struct Animation
{
	bool playing;
	bool looping;
	bool donePlaying;
	

	float loopDelay{};

	sf::Clock totalTimer;
	sf::Clock frameTimer;

	sf::Texture* textureSheet;
	unsigned int sheetWidthPxl;

	sf::Vector2i startPxl;
	sf::Vector2i frameSize;

	uint16_t numFrames;
	uint16_t index;

	std::string name;

	std::string fallbackName;

	std::vector<float> frameDelay;

	Animation();
	Animation(sf::Texture& textureSheet_, const std::string& name_, uint16_t numFrames_, sf::Vector2i frameSize_, sf::Vector2i startPxl_ = { 0,0 }, float frameDelay_ = 0.1f, bool loop_ = false, float loopDelay_ = 0.f, const std::string& fallbackName_ = "NONE");
	~Animation();
	[[nodiscard]] bool setFrameDelay(uint16_t index_, float delay_);

	void nextFrame();
	void reset();
	void play();
	void pause();
	void stop();
	void resume();

	sf::IntRect frame();
	float getTotalTime();

	void animate();

};