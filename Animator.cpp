#include "Animator.h"
#include <iostream>
#include "AnimStateMachine/all_anim_states.h"

Animator::Animator(Obj* owner_)
	: animMap{}
	, currAnim{}
	, fallbackAnim{}
	, animMachine{owner_}
{
	
}
Animator::~Animator() {}

sf::IntRect Animator::frame()
{
	return animMap[currAnim]->frame();
}


void Animator::setFacingRight(bool cond_) { animMachine.setFacingRight(cond_); }
bool Animator::getFacingRight() { return animMachine.getFacingRight(); }

void Animator::update(float dt_)
{

	animMachine.update(dt_);
	if (currAnim != animMachine.getCurrAnim())
	{
		stop();
		currAnim = animMachine.getCurrAnim();
		play();
	}
	/*if (animMap[currAnim]->donePlaying)
	{
		stop();
		currAnim = animMap[currAnim]->fallbackName;
		play();
	}*/
	animMap[currAnim]->animate();
}

sf::Texture& Animator::getTexture()
{
	return *animMap[currAnim]->textureSheet;
}

bool Animator::isOnLastFrame()
{
	return (this->animMap[currAnim]->index == animMap[currAnim]->numFrames - 1);
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

const std::string& Animator::getCurrAnimName()
{

	return animMap[currAnim]->name;
	//return currAnim;
}

const std::string& Animator::getCurrFallbackName()
{
	return animMap[currAnim]->fallbackName;
}

void Animator::addAnimation(sf::Texture& textureSheet_, const std::string& name_, uint16_t numFrames_, sf::Vector2i frameSize_, sf::Vector2i startPxl_, float frameDelay_, bool loop_, float loopDelay_, const std::string& fallbackAnim_)
{
	animMap.insert_or_assign(name_, std::make_unique<Animation>(textureSheet_, name_, numFrames_, frameSize_, startPxl_, frameDelay_, loop_, loopDelay_, fallbackAnim_));
	if (currAnim == "")
	{
		currAnim = name_;
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

	if (currAnim != name_)
	{
		animMap[currAnim]->donePlaying = false;
		animMap[currAnim]->stop();
		currAnim = name_;
		fallbackAnim = animMap[currAnim]->fallbackName;
		animMap[currAnim]->donePlaying = false;
		animMap[currAnim]->play();
	}
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
