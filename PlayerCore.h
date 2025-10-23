#pragma once
#include "Core.h"
class PlayerCore : public Core
{

public:

	PlayerCore();
	~PlayerCore();

	void AssignAnimations(sf::Texture& tex_);
};