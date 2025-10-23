#pragma once
#include <memory>
#include "Core.h"
class Obj
{

public:
	std::unique_ptr<Core> core;

	Obj();
	virtual ~Obj() = 0;

	virtual void input() = 0;
	virtual void update(float dt_) = 0;
	virtual void render(sf::RenderWindow& wnd) = 0;
};