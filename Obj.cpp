#include "Obj.h"



Obj::Obj(int maxHealth_)
	: core{nullptr}
	, maxHealth{maxHealth_}
	, health{maxHealth_}
{
}

Obj::~Obj() {

}

void Obj::updateKeyState()
{
	// left key
	leftPressed = false; leftHeld = false; leftReleased = false;
	if (core->input->isLeftHeld() && !leftHeldCheck)
	{   leftPressed = true;
		leftHeldCheck = true; 
	}
	else if (core->input->isLeftHeld())
	{
		leftHeld = true;
	}
	else if (leftHeldCheck)
	{   leftReleased = true;
		leftHeldCheck = false;
	}

	// right key
	rightPressed = false; rightHeld = false; rightReleased = false;
	if (core->input->isRightHeld() && !rightHeldCheck)
	{
		rightPressed = true;
		rightHeldCheck = true;
	}
	else if (core->input->isRightHeld())
	{
		rightHeld = true;
	}
	else if (rightHeldCheck)
	{
		rightReleased = true;
		rightHeldCheck = false;
	}
	
}

bool Obj::isLeftKeyPressed()
{
	return leftPressed;
}

bool Obj::isLeftKeyHeld()
{
	return leftHeld;
}

bool Obj::isLeftKeyReleased()
{
	return leftReleased;
}

bool Obj::isRightKeyPressed()
{
	return rightPressed;
}

bool Obj::isRightKeyHeld()
{
	return rightHeld;
}

bool Obj::isRightKeyReleased()
{
	return rightReleased;
}

int Obj::getHealth()
{
	return health;
}

void Obj::takeHit(int damage_)
{
	wasJustHit = true;
	health -= damage_;
}

bool Obj::tookAHit()
{
	if (wasJustHit)
	{
		wasJustHit = false;
		return true;
	}
	return false;
}

const sf::Vector2f Obj::getPos() const
{
	return {core->body->left(), core->body->top()};
}

const sf::Vector2f Obj::getSize() const
{
	return { core->body->width(), core->body->height() };
}

bool Obj::isAlive()
{
	return alive;
}

void Obj::move(sf::Vector2f amt_)
{
	core->body->move(amt_);
}
