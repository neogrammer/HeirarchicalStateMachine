#include "Player.h"
#include "PlayerCore.h"
#include <iostream>
Player::Player()
{
	core = std::make_unique<PlayerCore>(this);

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
	
	if (isSpaceKeyPressed() && core->body->grounded == true)
	{
		// player started jump
		 //core->body->grounded = false;
		core->body->landing = false;
		core->body->impulse({0.f, -600.f});
	}

	if ((isLeftKeyPressed() || isLeftKeyHeld()) && !core->input->isRightHeld())
	{
		core->animator->setFacingRight(false);
		if (core->body->vel.x >= -5.f)
		{
			core->body->impulse({ -600.f,0.f });
		}
		core->body->accel.x = -300.f;
		//	core->animator->setAnimation("Running_Left");
	}
	else if (isLeftKeyReleased())
	{
		core->body->vel.x = 0.f;
		//	core->animator->setAnimation("Idle_Left");
	}

	if ((isRightKeyPressed() || isRightKeyHeld()) && !core->input->isLeftHeld())
	{
		core->animator->setFacingRight(true);
		if (core->body->vel.x <= 5.f)
		{
			core->body->impulse({ 600.f,0.f });
		}
		core->body->accel.x = 300.f;
		//	core->animator->setAnimation("Running_Right");
	}                
	else if (isRightKeyReleased())
	{
   		core->body->vel.x = 0.f;
		//	core->animator->setAnimation("Idle_Right");
	}

	
	core->body->update(dt_);

	// collisions can happen in caller after this before drawing
}
void Player::render(sf::RenderWindow& wnd, float dt_)
{
	

	// in final positions for this frame, lets update to correct animation and render
	core->animator->update(dt_);

	sf::Sprite sprite{ core->animator->getTexture() };
	sprite.setTextureRect(core->animator->frame());
	sprite.setOrigin(sf::Vector2f(sprite.getTextureRect().size) / 2.f);
	auto centerPos = core->body->topLeft() - (sf::Vector2f)core->body->texOff + (sprite.getOrigin());
	sprite.setPosition(centerPos);

	wnd.draw(sprite);
}

