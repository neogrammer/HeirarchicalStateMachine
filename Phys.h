#ifndef PHYS_H__
#define PHYS_H__

// Physics module implementation for collision detection and resolution


#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "Player.h"

namespace phys
{

	bool AABB(const Obj& a, const Obj& b);
	bool AABB(const Obj& a, const Tile& b);

	bool AABB(const sf::FloatRect& a, const Obj& b);
	bool AABB(const sf::FloatRect& a, const Tile& b);

	float distSq(const Obj* a, const Obj* b);
	float distSq(const Obj* a, const Tile* b);


	void detectAndSave_Collidable(Obj& a, Obj& b, std::vector<Obj*>& outHits);
	void detectAndSave_Tile(Obj& a, Tile& b, std::vector<Tile*>& outHits);


	void sortCollided_Nearest(std::vector<Obj*>& hits,  Obj* reference = nullptr);
	void sortCollided_Nearest(std::vector<Tile*>& hits,  Obj* reference = nullptr);

	void detectAndResolve_Stage_Collidables(Obj& o, std::vector<Obj*>& hits);

	void detectAndResolve_Tilemap_Collisions(Obj& o, std::vector<Tile*>& solidTiles);

	void CollidePlayer_Collidables(Obj& player, std::vector<Obj*>& collidables);
	void CollidePlayer_Tiles(Obj& player, std::vector<Tile*>& tiles);



} // namespace phys

#endif
