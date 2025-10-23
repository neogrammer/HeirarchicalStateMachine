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
	animator->addAnimation(tex_, "Idle", 3, { 130,160 }, { 0,160 }, .6f, true, 2.f);
	animator->addAnimation(tex_, "Running", 10, { 130,160 }, { 130 * 2,160 * 2 }, 0.07f, false, 0.f, "Idle");
	animator->setAnimation("Running");
}
