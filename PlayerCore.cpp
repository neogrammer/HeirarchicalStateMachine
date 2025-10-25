#include "PlayerCore.h"
#include "Cfg.h"


PlayerCore::PlayerCore()
{
	animator = std::make_unique<Animator>();
	AssignAnimations(Cfg::textures.get(Cfg::Textures::PlayerAtlas));
	input = std::make_unique<Input>(input::SourceType::Controlled);
	body = std::make_unique<Body>(sf::Vector2f{ 800.f,450.f }, sf::Vector2f{ 130.f,160.f }, sf::Vector2i{ 0,0 }, false);
}

PlayerCore::~PlayerCore() {}

void PlayerCore::AssignAnimations(sf::Texture& tex_)
{
	animator->addAnimation(tex_, "Idle_Right", 3, { 130,160 }, { 0,160 }, .6f, true, 2.f);
	animator->addAnimation(tex_, "Idle_Left", 3, { 130,160 }, { 0,14*160 }, .6f, true, 2.f);
	animator->addAnimation(tex_, "Running_Right", 10, { 130,160 }, { 130 * 2,160 * 2 }, 0.07f, true);
	animator->addAnimation(tex_, "Running_Left", 10, { 130,160 }, { 130 * 2,160 * 15 }, 0.07f, true);

	animator->setAnimation("Running_Right");
}
