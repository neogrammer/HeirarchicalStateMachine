#pragma once
#include "Core.h"
#include "Animator.h"
class Obj;

class PlayerCore : public Core
{

public:

	PlayerCore() = delete;
	PlayerCore(Obj* owner_);

	~PlayerCore();

	void AssignAnimations(sf::Texture& tex_);
};