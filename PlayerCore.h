#pragma once
#include "Core.h"
class PlayerCore : public Core
{

public:
	PlayerCore();
	PlayerCore(sf::Texture& tex_);
	~PlayerCore();

	void AssignAnimations(sf::Texture& tex_);
};