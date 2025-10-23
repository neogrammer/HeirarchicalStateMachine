#include <SFML/Graphics.hpp>

#pragma once
namespace util {
	float CenterScreenX(sf::RenderWindow& wnd);
	float CenterScreenY(sf::RenderWindow& wnd);
	sf::Vector2f CenterScreen(sf::RenderWindow& wnd);
	float CenterSpriteX(sf::Sprite* spr_);
	float CenterSpriteY(sf::Sprite* spr_);
	sf::Vector2f CenterSprite(sf::Sprite* spr_);
};