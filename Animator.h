#pragma once

#include "Animation.h"
#include <string>
#include <unordered_map>
#include <memory>
class Animator
{
	std::unordered_map<std::string, std::unique_ptr<Animation>> animMap;
	std::string currAnim;
	std::string fallbackAnim;
public:

	Animator();
	~Animator();
	void addAnimation(sf::Texture& textureSheet_, const std::string& name_, uint16_t numFrames_, sf::Vector2i frameSize_, sf::Vector2i startPxl_ = { 0,0 }, float frameDelay_ = 0.1f, bool loop_ = false, float loopDelay_ = 0.f, const std::string& fallbackAnim_ = "NONE");
	bool setAnimation(const std::string& name_);

	
	

	void play();
	void pause();
	void stop();
	void resume();

	sf::IntRect frame();
	void update();
	sf::Texture& getTexture();

	void setFallbackName(const std::string& animName, const std::string& fallbackName);

};