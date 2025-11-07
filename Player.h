#pragma once
#include "Obj.h"

#include <SFML/Graphics.hpp>
#include <memory>
class Player : public Obj
{

	const float runSpeed{ 350.f };



public:

	Player();
	~Player();

	void input();
	void update(float dt_);
	void render(sf::RenderWindow& wnd, float dt_);
	void updateAnimations(float dt_);


};