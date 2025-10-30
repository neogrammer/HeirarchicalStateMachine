#pragma once
#include <SFML/Graphics/Rect.hpp>

class Tile
{
	const int tw, th;
	const sf::IntRect texRect;

public:
	Tile(int tw_, int th_, sf::IntRect rect_);
	~Tile();
	Tile(const Tile& o);
	Tile& operator=(const Tile& o);
	Tile(Tile&& o) noexcept;
	Tile& operator=(Tile&& o) noexcept;


};