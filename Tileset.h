#pragma once
#include "Cfg.h"
#include <memory>
#include <vector>
#include <string>
class Tile;

class Tileset
{
	friend class Tilemap;
	const Cfg::Textures texID;
	std::vector<std::unique_ptr<Tile>> tileset;
	int pitch;
	int numTiles;
public:
	Tileset(Cfg::Textures texID_, const std::string& filename_);
	~Tileset();
	Tileset(const Tileset& o);
	Tileset& operator=(const Tileset& o);
	Tileset(Tileset&& o);
	Tileset& operator=(Tileset&& o) noexcept;

	sf::Sprite getSprite(int num_);
	sf::Sprite getSprite(int col_, int row_);

};