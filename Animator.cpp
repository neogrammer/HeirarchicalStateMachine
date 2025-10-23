#include "Animator.h"
#include <iostream>

Animator::Animator()
	: animMap{}
	, currAnim{}
	, fallbackAnim{}
{
}
Animator::~Animator() {}

sf::IntRect Animator::frame()
{
	return animMap[currAnim]->frame();
}

void Animator::update()
{
	if (animMap[currAnim]->donePlaying)
	{
		stop();
		currAnim = animMap[currAnim]->fallbackName;
		play();
	}
	animMap[currAnim]->animate();
}

void Animator::setFallbackName(const std::string& animName_, const std::string& fallbackName_)
{
	if (animMap.find(animName_) == animMap.end())
	{
		std::cout << "unable to find animation " << animName_ << " in animator's animMap!  When calling setFallbackName()" << std::endl;
	}
	else
	{
		if (animMap.find(fallbackName_) == animMap.end())
		{
			std::cout << "unable to find fallback animation " << fallbackName_ << " in animator's animMap you are trying to set the fallback anim name for!  When calling setFallbackName()" << std::endl;
		}
		else
		{
			// ok, we good
			animMap[animName_]->fallbackName = fallbackName_;
		}
	}

	if (currAnim == animName_)
		fallbackAnim = animMap[animName_]->fallbackName;
}

void Animator::addAnimation(sf::Texture& textureSheet_, const std::string& name_, uint16_t numFrames_, sf::Vector2i frameSize_, sf::Vector2i startPxl_, float frameDelay_, bool loop_, float loopDelay_, const std::string& fallbackAnim_)
{
	animMap.insert_or_assign(name_, std::make_unique<Animation>(textureSheet_, name_, numFrames_, frameSize_, startPxl_, frameDelay_, loop_, loopDelay_, fallbackAnim_));
	if (currAnim == "")
	{
		currAnim = animMap[name_]->name;
	}
	if (fallbackAnim == "")
	{
		fallbackAnim = animMap[name_]->fallbackName;
	}
}

bool Animator::setAnimation(const std::string& name_)
{

	if (animMap.find(name_) == animMap.end())
	{
		std::cout << "unable to find animation " << name_ << " in animator's animMap!" << std::endl;
		return false;
	}

	currAnim = name_;
	fallbackAnim = animMap[currAnim]->fallbackName;
	return true;
}


void Animator::play() 
{
	animMap[currAnim]->play();
}
void Animator::pause() 
{
	animMap[currAnim]->pause();

}
void Animator::stop() 
{
	animMap[currAnim]->stop();

}
void Animator::resume() 
{
	animMap[currAnim]->resume();

}
