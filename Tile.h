#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "TileTypes.h"
class Tileset;
class Tile
{
	friend class Tilemap;
	const sf::IntRect texRect;
	int tileNum;
	TileType type;

	sf::Vector2f pos{};
	sf::Vector2f size{};

public:
	Tile(TileType type_, sf::IntRect rect_, int tileNum_);
	~Tile();
	Tile(const Tile& o);
	Tile& operator=(const Tile& o);
	Tile(Tile&& o) noexcept;
	Tile& operator=(Tile&& o) noexcept;


	const sf::IntRect& getRect() const;
	int getTileNum();
	TileType getTileType();

	void setPosFromTilemap(sf::Vector2f pos_);
	void setSizeFromTilemap(sf::Vector2f size_);

	const sf::Vector2f& getPosFromTilemap() const;
	const sf::Vector2f& getSizeFromTilemap() const;

	const sf::Vector2f& getPos() const;
};