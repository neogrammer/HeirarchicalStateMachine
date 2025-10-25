#include "Controlled.h"
#include "SFML/Window/Keyboard.hpp"
Controlled::Controlled()
{
}

Controlled::Controlled(std::array<bool, (size_t)(int(io::Key::Count))>* keys_)
	: InputSource{keys_}
{
}

Controlled::~Controlled()
{
}

void Controlled::update()
{
	clearKeys();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		(*keys)[int(io::Key::Left)] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		(*keys)[int(io::Key::Right)] = true;
}
