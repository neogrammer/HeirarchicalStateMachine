#pragma once
#include <SFML/Graphics.hpp>


#include "Body.h"
#include "Input.h"
#include <memory>
class Animator;
class Core
{
public:
	std::unique_ptr<Animator> animator;
	std::unique_ptr<Body> body;
	std::unique_ptr<Input> input;

	Core();
	virtual ~Core() = 0;
	virtual void AssignAnimations(sf::Texture& tex_) = 0;
};