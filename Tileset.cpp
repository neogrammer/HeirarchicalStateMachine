#include "Tileset.h"

Tileset::Tileset(Cfg::Textures texID_)
	: texID{texID_}
{
}

Tileset::~Tileset()
{
}

Tileset::Tileset(const Tileset& o) : texID{ o.texID }
{
}

Tileset& Tileset::operator=(const Tileset& o)
{
	// TODO: insert return statement here
	if (this == &o) { return *this; }
	this->~Tileset();
	return *new(this) Tileset(o);
}

Tileset::Tileset(Tileset&& o) noexcept
	: texID{o.texID}
{
}

Tileset& Tileset::operator=(Tileset&& o) noexcept
{
	// TODO: insert return statement here
	if (this == &o) { return *this; }
	this->~Tileset();
	return *new(this) Tileset{ std::move(o) };
}
