#pragma once

#include <memory>
#include "InputSourceTypes.h"

class InputSource;

class Input
{
protected:
	std::unique_ptr<InputSource> inputSource;
public:
	Input(input::SourceType type_);
	~Input();


};