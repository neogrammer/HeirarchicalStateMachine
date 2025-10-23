#pragma once
#include "InputSource.h"

class Controlled : public InputSource
{
public:
	using InputSource::InputSource;

	~Controlled();

};