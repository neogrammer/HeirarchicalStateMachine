#pragma once
#include "Cfg.h"

class Tileset
{
	friend class Tilemap;

	const Cfg::Textures texID;
public:
	Tileset(Cfg::Textures texID);
	~Tileset();
	Tileset(const Tileset& o);
	Tileset& operator=(const Tileset& o);
	Tileset(Tileset&& o) noexcept;
	Tileset& operator=(Tileset&& o) noexcept;


};