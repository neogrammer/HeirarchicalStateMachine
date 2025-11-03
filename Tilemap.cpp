#include "Tilemap.h"
#include "Tileset.h"
#include "Tile.h"
#include <fstream>

Tilemap::Tilemap(Tileset& tileset, int mapW_, int mapH_, const std::string& filename_)
	: mapW{ mapW_ }, mapH{ mapH_ }
	, tileset{ &tileset }
{

	std::ifstream file;
	file.open(filename_);

	if (file.is_open() && file.good())
	{
		for (int y = 0; y < mapH_; y++)
		{
			for (int x = 0; x < mapW; x++)
			{
				int tmp;
				file >> tmp;
				tilemap.push_back(tmp);
			}
		}
		file.close();
	}

}

Tilemap::~Tilemap()
{
	tileset = nullptr;
}

Tilemap::Tilemap(const Tilemap& o) 
	: mapW{ o.mapW }, mapH{ o.mapH }
	, tileset{ o.tileset }
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
	, mapW{ std::move(o.mapW) }, mapH{ std::move(o.mapH) }
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

void Tilemap::renderMap(sf::RenderWindow& window_)
{
	int counter = 0;
	for (int y = 0; y < mapH; y++)
	{
		for (int x = 0; x < mapW; x++)
		{
			int num = y * mapW + x;
			if (num >= mapW * mapH) { return; }
			if (getTile(tilemap[num]).type == TileType::Empty) { continue; }
			sf::Sprite&& spr = static_cast<sf::Sprite&&>(tileset->getSprite(tilemap[num]));
			int col = num % mapW;
			int row = num / mapW;
			int xpos = col * tile::tw;
			int ypos = row * tile::th;
			spr.setPosition({ (float)xpos,(float)ypos });
			window_.draw(spr);
			
		}
	}
}

Tile& Tilemap::getTile(int num_)
{
	return *tileset->tileset[num_];
}

Tile& Tilemap::getMapTile(int num_)
{
	return *tileset->tileset[tilemap[num_]];
}

sf::Sprite Tilemap::getSprite(int num_)
{
	return static_cast<sf::Sprite&&>(tileset->getSprite(num_));
}

sf::Sprite Tilemap::getSprite(int col_, int row_)
{
	return static_cast<sf::Sprite&&>(tileset->getSprite(col_, row_));
}

sf::Sprite Tilemap::getMapTileSprite(int num_)
{
	sf::Sprite&& spr = static_cast<sf::Sprite&&>(tileset->getSprite(tilemap[num_]));
	int col = num_ % mapW;
	int row = num_ / mapW;
	int xpos = col * tile::tw;
	int ypos = row * tile::th;
	spr.setPosition({ (float)xpos,(float)ypos });
	return static_cast<sf::Sprite&&>(spr);
}

int Tilemap::getNumTilesInMap()
{
	return mapW * mapH;
}
