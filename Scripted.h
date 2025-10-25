#pragma once
#include "InputSource.h"

class Scripted : public InputSource
{
	// Fn::activeBehavior
public:
	
	Scripted();
	Scripted(std::array<bool, (size_t)(int(io::Key::Count))>* keys_);

	~Scripted();

	void update() override;

	// setBehavior(Fn::Behavior)

};