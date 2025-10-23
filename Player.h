#pragma once
#include "Obj.h"

#include <SFML/Graphics.hpp>
#include <memory>
class Player : public Obj
{
public:

	Player();
	~Player();

	void input();
	void update(float dt_);
	void render(sf::RenderWindow& wnd);

};