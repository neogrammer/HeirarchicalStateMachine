#pragma once
#include "Cfg.h"
class Tileset;
class Tilemap
{
	const int pitch, numTiles;
	Tileset* tileset;
	
public:
	Tilemap(Cfg::Textures texID_, int pitch_, int numTiles_);
	~Tilemap();
	Tilemap(const Tilemap& o);
	Tilemap& operator=(const Tilemap& o);
	Tilemap(Tilemap&& o) noexcept;
	Tilemap& operator=(Tilemap&& o) noexcept;

};