#pragma once
#include <memory>
#include "Core.h"
class Obj
{
	// Key Checks
	bool leftHeldCheck{ false }, rightHeldCheck{ false };

	// Key state holders
	bool leftPressed{ false }, leftHeld{ false }, leftReleased{ false };
	bool rightPressed{ false }, rightHeld{ false }, rightReleased{ false };
protected:
	void updateKeyState();
	const int maxHealth;
	bool wasJustHit{ false };
	int health;
public:


	std::unique_ptr<Core> core;
	Obj(int maxHealth_ = 0);
	virtual ~Obj() = 0;

	virtual void input() = 0;
	virtual void update(float dt_) = 0;

	virtual void render(sf::RenderWindow& wnd, float dt_) = 0;

	bool isLeftKeyPressed();
	bool isLeftKeyHeld();
	bool isLeftKeyReleased();

	bool isRightKeyPressed();
	bool isRightKeyHeld();
	bool isRightKeyReleased();

	int getHealth();
	void takeHit(int damage_ = 0);
	bool tookAHit();

	
};