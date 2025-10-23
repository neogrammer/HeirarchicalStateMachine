#include "Player.h"
#include "PlayerCore.h"
Player::Player()
{

}

Player::Player(sf::Texture& tex_)
{
	core = std::make_unique<PlayerCore>(tex_);

}

Player::~Player() 
{

}

void Player::input()
{
}
void Player::update(float dt_)
{
	core->animator->update();
	
}
void Player::render(sf::RenderWindow& wnd)
{
	sf::Sprite sprite{ core->animator->getTexture() };
	sprite.setTextureRect(core->animator->frame());
	sprite.setOrigin(sf::Vector2f(sprite.getTextureRect().size) / 2.f);
	auto centerPos = core->body->topLeft() - (sf::Vector2f)core->body->texOff + (sprite.getOrigin());
	sprite.setPosition(centerPos);

	wnd.draw(sprite);
}