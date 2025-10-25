#include "Scripted.h"

Scripted::Scripted()
	: InputSource{}
{
}

Scripted::Scripted(std::array<bool, (size_t)(int(io::Key::Count))>* keys_)
	: InputSource{keys_}
{
}

Scripted::~Scripted()
{
}

void Scripted::update()
{
	clearKeys();
	//activeBehavior(keys);
}