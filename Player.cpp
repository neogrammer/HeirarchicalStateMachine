#include "Player.h"
#include "PlayerCore.h"

Player::Player()
{
	core = std::make_unique<PlayerCore>();

}

Player::~Player() 
{

}

void Player::input()
{
}
void Player::update(float dt_)
{
	core->body->update(dt_);
	
	// collisions can happen in caller after this before drawing
}
void Player::render(sf::RenderWindow& wnd)
{
	// in final positions for this frame, lets update to correct animation and render
	core->animator->update();

	sf::Sprite sprite{ core->animator->getTexture() };
	sprite.setTextureRect(core->animator->frame());
	sprite.setOrigin(sf::Vector2f(sprite.getTextureRect().size) / 2.f);
	auto centerPos = core->body->topLeft() - (sf::Vector2f)core->body->texOff + (sprite.getOrigin());
	sprite.setPosition(centerPos);

	wnd.draw(sprite);
}