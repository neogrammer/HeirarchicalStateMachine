#include "Body.h"

Body::Body()
{

}

Body::Body(sf::Vector2f pos_, sf::Vector2f size_,sf::Vector2i texOff_, bool affectedByGravity_, float gravity_, sf::Vector2f vel_, sf::Vector2f accel_)
	: pos{ pos_ }
	, size{ size_ }
	, texOff{ texOff_ }
	, affectedByGravity{ affectedByGravity_ }
	, gravity{ gravity_ }
	, vel{ vel_ }
	, accel{ accel_ }
	, prevPos{ pos_ }
	, prevVel{ vel_ }
	, prevAccel{ accel_ }
	, dt{ 0.f }
	, prevDT{ 0.f }
{
}

float Body::top()
{
   return pos.y - size.y / 2.f;
}

float Body::left()
{
	return pos.x - size.x / 2.f;
}

float Body::bottom()
{
	return pos.y + size.y / 2.f;
}

float Body::right()
{
	return pos.x + size.x / 2.f;
}

sf::Vector2f Body::topLeft()
{
	return { left(), top()};
}

sf::Vector2f Body::topRight()
{
	return { right(), top() };
}

sf::Vector2f Body::bottomLeft()
{
	return {left(), bottom()};
}

sf::Vector2f Body::bottomRight()
{
	return { right(), bottom() };
}

float Body::prevTop()
{
	return prevPos.y - size.y / 2.f;
}

float Body::prevLeft()
{
	return prevPos.x - size.x / 2.f;
}

float Body::prevBottom()
{
	return prevPos.y + size.y / 2.f;
}

float Body::prevRight()
{
	return prevPos.x + size.x / 2.f;
}

sf::Vector2f Body::prevTopLeft()
{
	return {prevTop(),prevLeft()};
}

sf::Vector2f Body::prevTopRight()
{
	return { prevTop(),prevRight() };

}

sf::Vector2f Body::prevBottomLeft()
{
	return { prevBottom(),prevLeft() };

}

sf::Vector2f Body::prevBottomRight()
{
	return { prevBottom(),prevRight() };

}

float Body::halfw()
{
	return size.x / 2.f;
}

float Body::halfh()
{
	return size.y / 2.f;
}

float Body::width()
{
	return size.x;
}

float Body::height()
{
	return size.y;
}

sf::Vector2f Body::nextPos()
{
	return {pos + vel * dt};
}

void Body::applyFriction()
{
	vel *= 0.9998f;
}

sf::Vector2f Body::dir()
{
	return {vel.x / len(), vel.y / len()};
}

sf::Vector2f Body::prevDir()
{
	return { prevVel.x / prevLen(), prevVel.y / prevLen() };
}

float Body::len()
{
	return sqrtf(vel.x * vel.x + vel.y * vel.y);
}

float Body::prevLen()
{
	return sqrtf(prevVel.x * prevVel.x + prevVel.y * prevVel.y);
}



void Body::update(float dt_)
{
	prevDT = dt;
	dt = dt_;

	if (affectedByGravity)
	{
		accel.y += gravity;
	}
	updateVel();

	if (affectedByGravity && vel.x > 0.f && fabsf(vel.y) < 0.001f)
	{
		applyFriction();
	}

	updatePos();
}


void Body::updateVel()
{
	prevVel = vel;
	vel += accel * dt;
	// we just updated for the frame, so now any acceleration adding accumulates for next frame.  with no force pushing on entity acceleration force is zero, must constantly apply force to accelerate
	accel = { 0.f,0.f };
}

void Body::impulse(sf::Vector2f vel_, bool updatePrev_)
{
	if (updatePrev_)
	{
		prevVel = vel;
	}
	vel += vel_;
}

void Body::updatePos()
{
	prevPos = pos;
	pos += vel * dt;
}

void Body::move(sf::Vector2f disp_, bool updatePrev_)
{
	if (updatePrev_)
	{
		prevPos = pos;
	}
	pos += disp_;
}

bool Body::intersects(Body& other_)
{
	float aleft{ left() }, aright{ right() }, bleft{ other_.left() }, bright{ other_.right() }, atop{ top() }, abottom{ bottom() }, btop{ other_.top() }, bbottom{ other_.bottom() };
	

	return (aleft < bright && aright >= bleft && atop < bbottom && abottom >= btop);
}

void Body::resolve(Body& other_)
{
	if (intersects(other_))
	{

		if (dir().x > 0.f)
		{
			float offset = right() - other_.left();
			move({ -offset, 0.f });
		}
		else if (dir().x < 0.f)
		{
			float offset = other_.right() - left();
			move({ offset, 0.f });

		}
		else
		{
			// dir().x == 0.f no change in x, unless aright == bleft, in which case move left one pixel
			if (right() == other_.left())
			{
				move({ -1.f, 0.f });
			}
			else if (other_.right() == left())
			{
				move({ 1.f, 0.f });
			}
		}

		if (dir().y > 0.f)
		{
			float offset = bottom() - other_.top();
			move({ 0.f, -offset });
		}
		else if (dir().y < 0.f)
		{
			float offset = other_.bottom() - top();
			move({ 0.f, offset });
		}
		else
		{
			// dir().x == 0.f no change in x, unless aright == bleft, in which case move left one pixel
			if (bottom() == other_.top())
			{
				move({ 0.f, -1.f });
			}
			else if (other_.bottom() == top())
			{
				move({ 0.f, 1.f });
			}
		}
	}

}

bool Body::intersects(sf::FloatRect other_)
{
	float aleft{ left() }, aright{ right() }, bleft{ other_.position.x }, bright{ other_.position.x + other_.size.x }, atop{ top() }, abottom{ bottom() }, btop{ other_.position.y }, bbottom{ other_.position.y + other_.size.y };


	return (aleft < bright && aright >= bleft && atop < bbottom && abottom >= btop);
}

void Body::resolve(sf::FloatRect other_)
{
	// tiles represented here are not calculated by center, this is however
	if (intersects(other_))
	{

		if (dir().x > 0.f)
		{
			float offset = right() - other_.position.x;
			move({ -offset, 0.f });
		}
		else if (dir().x < 0.f)
		{
			float offset = other_.position.x + other_.size.x - left();
			move({ offset, 0.f });

		}
		else
		{
			// dir().x == 0.f no change in x, unless aright == bleft, in which case move left one pixel
			if (right() == other_.position.x)
			{
				move({ -1.f, 0.f });
			}
			else if (other_.position.x + other_.size.x == left())
			{
				move({ 1.f, 0.f });
			}
		}

		if (dir().y > 0.f)
		{
			float offset = bottom() - other_.position.y;
			move({ 0.f, -offset });
		}
		else if (dir().y < 0.f)
		{
			float offset = other_.position.y + other_.size.y - top();
			move({ 0.f, offset });
		}
		else
		{
			// dir().x == 0.f no change in x, unless aright == bleft, in which case move left one pixel
			if (bottom() == other_.position.y)
			{
				move({ 0.f, -1.f });
			}
			else if (other_.position.y + other_.size.y == top())
			{
				move({ 0.f, 1.f });
			}
		}
	}

}
