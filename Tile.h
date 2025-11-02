#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "TileTypes.h"
class Tileset;
class Tile
{
	friend class Tilemap;
	const sf::IntRect texRect;
	int tileNum;
	TileType type;
public:
	Tile(TileType type_, sf::IntRect rect_, int tileNum_);
	~Tile();
	Tile(const Tile& o);
	Tile& operator=(const Tile& o);
	Tile(Tile&& o) noexcept;
	Tile& operator=(Tile&& o) noexcept;

	const sf::IntRect& getRect() const;
	int getTileNum();
};