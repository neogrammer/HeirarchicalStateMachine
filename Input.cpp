#include "Input.h"
#include "Controlled.h"
#include "Scripted.h"

Input::Input()
	: inputSource{ nullptr }
{

}

Input::Input(input::SourceType type_)
	: inputSource{nullptr}
{
	switch (type_)
	{
	case input::SourceType::Controlled:
		inputSource = std::make_unique<Controlled>(&keys); break;
	case input::SourceType::Scripted:
		inputSource = std::make_unique<Scripted>(&keys); break;
	default:
		break;
	};
}

Input::~Input()
{
}

void Input::updateState()
{
	if (inputSource)
	{
		inputSource->update();
	}
}

bool Input::isLeftHeld()
{
	return keys[int(io::Key::Left)];
}

bool Input::isRightHeld()
{
	return keys[int(io::Key::Right)];
}

bool Input::isShootHeld()
{
	return false;
}

bool Input::isJumpHeld()
{
	return false;
}
