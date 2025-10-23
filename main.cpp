

#include <optional>
#include "Util.h"
#include "Animation.h"
#include "Animator.h"

sf::RenderWindow wnd{ sf::VideoMode{{1920, 1080}, 32U}, "Heirarchical Animation State Machine" };

sf::Texture playerTex;
sf::Sprite* sprite;

using namespace util;

int main()
{
	if (!playerTex.loadFromFile("assets/PlayerAtlas.png"))
	{
		// oh well
	}
	sprite = new sf::Sprite{ playerTex };
	sprite->setTextureRect({ {0,160}, {130,160} });
	sprite->setOrigin(CenterSprite(sprite));
	sprite->setPosition(CenterScreen(wnd));


	Animator animator{};
	animator.addAnimation(playerTex, "Idle", 3, { 130,160 }, { 0,160 }, .6f, true, 2.f);
	animator.addAnimation(playerTex, "Running", 10, { 130,160 }, { 130 * 2,160 * 2 }, 0.07f, false, 0.f, "Idle");
	animator.setAnimation("Running");

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
		animator.update();
		sprite->setTextureRect(animator.frame());

		// move the view to keep player in the middle 1/3rd of the screen if needed,, set this view back to the window, then clear draw and display 

		wnd.clear(sf::Color(sf::Color::White));

		wnd.draw(*sprite);

		wnd.display();
	}

	delete sprite;

	return 0;
}