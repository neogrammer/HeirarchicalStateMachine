#pragma once
#include "Cfg.h"
#include "TileTypes.h"
#include <string>
#include <memory>
#include <utility>
#include <SFML/Graphics.hpp>
class Tileset;
class Tile;
class Tilemap
{
	const int mapW, mapH;
	Tileset* tileset;
	std::vector<int> tilemap;
public:
	Tilemap(Tileset& tileset, int mapW_, int mapH_, const std::string& filename);
	~Tilemap();
	Tilemap(const Tilemap& o);
	Tilemap& operator=(const Tilemap& o);
	Tilemap(Tilemap&& o) noexcept;
	Tilemap& operator=(Tilemap&& o) noexcept;
	void update(float dt_);
	void renderMap(sf::RenderWindow& window_);
	Tile& getTile(int num_);
	Tile& getMapTile(int num_);

	sf::Sprite getSprite(int num_);
	sf::Sprite getSprite(int col_, int row_);
	int getNumTilesInMap();
	sf::Sprite getMapTileSprite(int num_);
};
