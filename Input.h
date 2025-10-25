#pragma once

#include <memory>
#include "InputSourceTypes.h"
#include "GameKeyEnum.h"
#include <array>
class InputSource;

class Input
{
protected:
	std::array<bool, (size_t)(int(io::Key::Count))> keys { false, };

	std::unique_ptr<InputSource> inputSource;
public:
	Input();
	Input(input::SourceType type_);
	~Input();

	void updateState();

	bool isLeftHeld();
	bool isRightHeld();
	bool isShootHeld();
	bool isJumpHeld();

};