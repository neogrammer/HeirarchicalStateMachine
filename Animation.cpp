#include "Animation.h"
#include <iostream>
#include "Animator.h"
#include "AnimStateMachine/all_anim_states.h"

Animation::Animation()
{

}

Animation::Animation(sf::Texture& textureSheet_, const std::string& name_, uint16_t numFrames_, sf::Vector2i frameSize_, sf::Vector2i startPxl_, float frameDelay_, bool loop_, float loopDelay_,const std::string& fallbackName_)
	: playing{true}
	, looping{loop_}
	, donePlaying{false}
	, loopDelay{loopDelay_}
	, totalTimer{}
	, frameTimer{}
	, textureSheet{ &textureSheet_ }
	, startPxl{startPxl_}
	, frameSize{frameSize_}
	, numFrames{numFrames_}
	, index{ 0 }
	, name{name_}
	, frameDelay{}
	, fallbackName{fallbackName_}
{
	frameDelay.clear();
	frameDelay.reserve(numFrames);
	for (int i = 0; i < numFrames; i++)
	{
		frameDelay.emplace_back(frameDelay_);
	}
	sheetWidthPxl = textureSheet->getSize().x;
	if (fallbackName == "NONE")
		fallbackName = name_;
}

Animation::~Animation()
{
	textureSheet = nullptr;
}

bool Animation::setFrameDelay(uint16_t index_, float delay_)
{
	if (index_ < 0 || index_ >= numFrames)
	{
		std::cout << "Index out of range for animation: " << name << std::endl;
		return false;
	}
	
	frameDelay[index_] = delay_;
	return true;
}

void Animation::nextFrame()
{
	if (frameTimer.getElapsedTime().asSeconds() >= frameDelay[index])
	{
		

		if (looping)
		{
			
			if ((loopDelay == 0.f || (frameTimer.getElapsedTime().asSeconds() >= frameDelay[index] + loopDelay)) && index == numFrames - 1)
			{
				frameTimer.restart();
				++index %= numFrames;
			}
			else
			{
				if (index < numFrames - 1)
				{
					frameTimer.restart();
					++index;
				}
			}
		}
		else
		{
			if (index < numFrames - 1)
			{
				frameTimer.restart();
				++index;
			}
			else
			{
				donePlaying = true;
				pause();
			}
		}
	}
}



void Animation::play()
{
	index = 0;
	playing = true;
	frameTimer.reset();
	frameTimer.start();
	totalTimer.reset();
	totalTimer.start();
}

void Animation::pause()
{
	playing = false;
	totalTimer.stop();
	frameTimer.stop();
}

void Animation::stop()
{
	index = 0;
	playing = false;
	totalTimer.reset();
	frameTimer.reset();
}

void Animation::resume()
{
	playing = true;
	totalTimer.start();
	frameTimer.start();
}


sf::IntRect Animation::frame()
{
	sf::IntRect r{};

	int offX = index * frameSize.x;
	if (startPxl.x + offX < ((int)sheetWidthPxl - startPxl.x + (int)sheetWidthPxl))
	{
		int realY = startPxl.y;
		if ((startPxl.x + offX) >= (int)sheetWidthPxl)
			startPxl.y += frameSize.y;
		int realX = (startPxl.x + offX) % (int)sheetWidthPxl;
		r = { {realX, realY}, {frameSize.x, frameSize.y} };
	}
	else
	{
		int times = ((startPxl.x + offX - ((int)sheetWidthPxl - ((int)sheetWidthPxl - startPxl.x))) / (int)sheetWidthPxl);
		int realY = startPxl.y + (frameSize.y * times);
		int realX = (startPxl.x + offX) % (int)sheetWidthPxl;
		r = { {realX, realY}, {frameSize.x, frameSize.y} };
	}
	return r;
}

float Animation::getTotalTime()
{
	return totalTimer.getElapsedTime().asSeconds();
}

void Animation::animate()
{
	if (!donePlaying && playing)
	{
		nextFrame();
	}
	else
	{
		if (donePlaying)
		{
			totalTimer.reset();
			frameTimer.reset();
		}
	}
}

