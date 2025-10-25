#include "InputSource.h"

void InputSource::clearKeys()
{
	for (auto i = 0; i < keys->size(); i++)
	{
		(*keys)[i] = false;
	}
}

InputSource::InputSource()
{

}

InputSource::InputSource(std::array<bool, (size_t)(int(io::Key::Count))>* keys_)
	: keys{keys_}
{
}



InputSource::~InputSource()
{

}