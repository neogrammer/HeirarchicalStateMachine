#pragma once
#include "InputSource.h"

class Controlled : public InputSource
{
	

public:
	Controlled();
	Controlled(std::array<bool, (size_t)(int(io::Key::Count))>* keys_);
	~Controlled();

	void update() override;

};