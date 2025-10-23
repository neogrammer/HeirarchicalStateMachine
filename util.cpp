

#include <SFML/Graphics.hpp>
namespace util {
	float CenterScreenX(sf::RenderWindow& wnd)
	{
		return (float)wnd.getSize().x / 2.f;
	}
	float CenterScreenY(sf::RenderWindow& wnd)
	{
		return (float)wnd.getSize().y / 2.f;
	}
	sf::Vector2f CenterScreen(sf::RenderWindow& wnd)
	{
		return { CenterScreenX(wnd), CenterScreenY(wnd) };
	}


	float CenterSpriteX(sf::Sprite* spr_)
	{
		return (float)spr_->getTextureRect().size.x / 2.f;
	}
	float CenterSpriteY(sf::Sprite* spr_)
	{
		return (float)spr_->getTextureRect().size.y / 2.f;
	}
	sf::Vector2f CenterSprite(sf::Sprite* spr_)
	{
		return { CenterSpriteX(spr_), CenterSpriteY(spr_) };
	}
}