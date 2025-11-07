

#include <optional>
#include "Util.h"
#include "Animation.h"
#include "Animator.h"

#include "Player.h"
#include "Cfg.h"
#include "Tileset.h"
#include "Tilemap.h"
#include "Tile.h"
#include "Phys.h"

sf::RenderWindow wnd{ sf::VideoMode{{1600, 900}, 32U}, "Heirarchical Animation State Machine" };


using namespace util;

int main()
{
	
	Cfg::Initialize();
	Player player{ };
	Tileset tileset{ Cfg::Textures::Tileset1, "assets/tilesets/tileset1.tst" };

	Tilemap tilemap{ tileset, 50, 30, "assets/tilemaps/tilemap1.map" };

	sf::Clock gameTimer;


	while (wnd.isOpen())
	{
		while (const std::optional event = wnd.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				wnd.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					wnd.close();
			}
		}

		player.input();

		// player updates keys pressed, and all inputs are passed to other Objs,
		// then all Objs, without then with cores, are updated, then after that only velocity is updated, 
		// not positions. here is where collision occurs for all using future position using the current 
		// velocities for the checks and then the entities are put in the right position for the frame

		//update the animator to get the right animation frame then set the texture rect for the sprite so that the correct frame is drawn
		float dt = gameTimer.restart().asSeconds();


		player.update(dt);

		
		auto tmp = tilemap.getTiles();

		phys::CollidePlayer_Tiles(player, tmp);


		for (auto* t : tmp)
		{
			if (t)
			{
				delete t;
				t = nullptr;
			}
		}

		//for (int i = 0; i < tilemap.getNumTilesInMap(); i++)
		//{
		//	if (tilemap.getMapTile(i).getTileType() == TileType::Empty) { continue; }
		//	sf::Sprite spr{ tilemap.getMapTileSprite(i) };
		//	player.core->body->resolve(spr.getGlobalBounds());
		//}

		// move the view to keep player in the middle 1/3rd of the screen if needed,, set this view back to the window, then clear draw and display 
		player.updateAnimations(dt);

		wnd.clear(sf::Color(sf::Color(47,147,247,255)));

		tilemap.renderMap(wnd);
		player.render(wnd, dt);

		wnd.display();
	}

	return 0;
}