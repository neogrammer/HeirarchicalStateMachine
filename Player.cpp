#include "Player.h"
#include "PlayerCore.h"
#include <iostream>
Player::Player()
{
	core = std::make_unique<PlayerCore>();

}

Player::~Player() 
{

}

void Player::input()
{
	// must call in this order! one updates the actual device input state core->input->updateState() only knows if key is currently pressed, 
	//  then the keys read by object updates complete state over time, updateKeyState() allows you to know if isLeftPressed() or isLeftHeld()
	core->input->updateState();
	updateKeyState();

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

