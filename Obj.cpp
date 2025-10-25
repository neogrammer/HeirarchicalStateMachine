#include "Obj.h"



Obj::Obj()
	: core{nullptr}
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
