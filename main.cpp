

#include <optional>
#include "Util.h"
#include "Animation.h"
#include "Animator.h"

#include "Player.h"

sf::RenderWindow wnd{ sf::VideoMode{{1920, 1080}, 32U}, "Heirarchical Animation State Machine" };

sf::Texture playerTex;

using namespace util;

int main()
{
	if (!playerTex.loadFromFile("assets/PlayerAtlas.png"))
	{
		// oh well
	}

	Player player{ playerTex };

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

		// player updates keys pressed, and all inputs are passed to other Objs,
		// then all Objs, without then with cores, are updated, then after that only velocity is updated, 
		// not positions. here is where collision occurs for all using future position using the current 
		// velocities for the checks and then the entities are put in the right position for the frame

		//update the animator to get the right animation frame then set the texture rect for the sprite so that the correct frame is drawn

		player.update(0.016f);

		// move the view to keep player in the middle 1/3rd of the screen if needed,, set this view back to the window, then clear draw and display 

		wnd.clear(sf::Color(sf::Color::White));


		player.render(wnd);

		wnd.display();
	}

	return 0;
}