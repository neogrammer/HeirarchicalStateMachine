#include "Tileset.h"
#include "Tile.h"
#include "TileTypes.h"
#include <fstream>
Tileset::Tileset(Cfg::Textures texID_, const std::string& filename_)
	: texID{texID_}
{
	std::ifstream file;
	file.open( filename_ );

	if (file.is_open() && file.good())
	{
		file >> pitch >> numTiles;

		int tilenum = 0;
		for (int y = 0; y < numTiles / pitch; y++)
		{
			for (int x = 0; x < pitch; x++)
			{
				int num;
				file >> num;
			
				//int num = y * pitch + x;
				sf::IntRect r = { {x*tile::tw,y*tile::th},{tile::tw,tile::th} };
				tileset.emplace_back(std::make_unique<Tile>((TileType)num,r, tilenum++));
			}
		}

		file.close();
	}

}

Tileset::~Tileset()
{
}

Tileset::Tileset(const Tileset& o) : texID{ o.texID }
 , pitch{o.pitch}, numTiles{o.numTiles}
{
}

Tileset& Tileset::operator=(const Tileset& o)
{
	// TODO: insert return statement here
	if (this == &o) { return *this; }
	this->~Tileset();
	return *new(this) Tileset(o);
}

Tileset::Tileset(Tileset&& o)
	: texID{o.texID}, pitch{ o.pitch }, numTiles{ o.numTiles }
{
}

Tileset& Tileset::operator=(Tileset&& o) noexcept
{
	// TODO: insert return statement here
	if (this == &o) { return *this; }
	this->~Tileset();
	return *new(this) Tileset{ std::move(o) };
}

sf::Sprite Tileset::getSprite(int num_)
{
	//int col = num_ % pitch;
	//int row = num_ / pitch;

	sf::Sprite spr{ Cfg::textures.get(texID) };
	spr.setTextureRect(tileset[num_]->getRect());
	


	return static_cast<sf::Sprite&&>(spr);
}

sf::Sprite Tileset::getSprite(int col_, int row_)
{
	//int col = num_ % pitch;
	//int row = num_ / pitch;
	int num = row_ * pitch + col_;

	sf::Sprite spr{ Cfg::textures.get(texID) };
	spr.setTextureRect(tileset[num]->getRect());



	return static_cast<sf::Sprite&&>(spr);
}


