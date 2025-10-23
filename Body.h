#pragma once
#include <SFML/Graphics.hpp>


struct Body
{


	// handle will be center of object same as rendered texture rectangle, no offset between the two needed
	sf::Vector2f pos;
	sf::Vector2f size;
	bool         affectedByGravity;
	float        gravity;
	sf::Vector2f vel;
	sf::Vector2f accel;
	sf::Vector2f prevPos;
	sf::Vector2f prevVel;
	sf::Vector2f prevAccel;
	float		 dt;
	float		 prevDT;

	Body(sf::Vector2f pos_, sf::Vector2f size_, bool affectedByGravity_ = true, float gravity_ = 400.f, sf::Vector2f vel_ = { 0.f,0.f }, sf::Vector2f accel_ = { 0.f,0.f });
	~Body() = default;

	float top();
	float left();
	float bottom();
	float right();
	sf::Vector2f topLeft();
	sf::Vector2f topRight();
	sf::Vector2f bottomLeft();
	sf::Vector2f bottomRight();

	float prevTop();
	float prevLeft();
	float prevBottom();
	float prevRight();
	sf::Vector2f prevTopLeft();
	sf::Vector2f prevTopRight();
	sf::Vector2f prevBottomLeft();
	sf::Vector2f prevBottomRight();

	float halfw();
	float halfh();
	float width();
	float height();


	sf::Vector2f nextPos();

	sf::Vector2f dir();
	sf::Vector2f prevDir();

	float len();
	float prevLen();

	void update(float dt_);

	void updateDT();
	void updateVel();
	void impulse(sf::Vector2f vel_, bool updatePrev_ = false);
	void applyFriction();
	void updatePos();
	void move(sf::Vector2f disp_, bool updatePrev_ = false);

	bool intersects(Body& other_);
	void resolve(Body& other_);
	bool intersects(sf::FloatRect other_);
	void resolve(sf::FloatRect other_);

};