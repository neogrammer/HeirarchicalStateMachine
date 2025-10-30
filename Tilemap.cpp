#include "Tilemap.h"
#include "Tileset.h"
Tilemap::Tilemap(Cfg::Textures texID_, int pitch_, int numTiles_)
	: tileset{ new Tileset{texID_} }
	, pitch{pitch_}
	, numTiles{numTiles_}
{



}

Tilemap::~Tilemap()
{
	if (tileset != nullptr)
		delete tileset;
}

Tilemap::Tilemap(const Tilemap& o) : tileset{ new Tileset(o.tileset->texID)}
, pitch{ o.pitch }
, numTiles{ o.numTiles }
{
}

Tilemap& Tilemap::operator=(const Tilemap& o)
{
	// TODO: insert return statement here
	if (this == &o) { return *this; }
	this->~Tilemap();
	return *new(this) Tilemap(o);
}

Tilemap::Tilemap(Tilemap&& o) noexcept
	: tileset{std::move(o.tileset)}
	, pitch{o.pitch}
	, numTiles{o.numTiles}
{
	o.tileset = nullptr;
}

Tilemap& Tilemap::operator=(Tilemap&& o) noexcept
{
	// TODO: insert return statement here
	if (this == &o) { return *this; }
	this->~Tilemap();
	return *new(this) Tilemap{ std::move(o) };
}
