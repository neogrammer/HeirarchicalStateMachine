#include "Tile.h"

Tile::Tile(int tw_, int th_, sf::IntRect rect_)
	: tw{tw_}
	, th{th_}
	, texRect{rect_}
{
}

Tile::~Tile()
{
}

Tile::Tile(const Tile& o) : tw{ o.tw }
, th{ o.th }
, texRect{ o.texRect }
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
	: tw{ o.tw }
	, th{ o.th }
	, texRect{ o.texRect }
{
}

Tile& Tile::operator=(Tile&& o) noexcept
{
	if (this == &o) { return *this; }
	this->~Tile();
	return *new(this) Tile{ std::move(o) };
}
