#include "Tile.h"
#include "Tileset.h"
Tile::Tile(TileType type_, sf::IntRect rect_, int tileNum_)
	: texRect{rect_}
	, tileNum{tileNum_}
	, type{type_}
{
}

Tile::~Tile()
{
}

Tile::Tile(const Tile& o) 
	: texRect{ o.texRect }
	, tileNum{ o.tileNum }
{
}

Tile& Tile::operator=(const Tile& o)
{
	// TODO: insert return statement here
	if (this == &o) { return *this; }
	this->~Tile();
	return *new(this) Tile(o);
}

Tile::Tile(Tile&& o) noexcept
	: texRect{ std::move(o.texRect) }
	, tileNum{ std::move(tileNum) }
{
}

Tile& Tile::operator=(Tile&& o) noexcept
{
	if (this == &o) { return *this; }
	this->~Tile();
	return *new(this) Tile{ std::move(o) };
}

const sf::IntRect& Tile::getRect() const
{
	return texRect;
}

int Tile::getTileNum()
{
	return tileNum;
}

TileType Tile::getTileType()
{
	return type;
}
