#include "Ball.h"

void Ball::RefectX()
{
	dir_ = Vector3(-dir_.x, dir_.y + Ogre::Math::RangeRandom(-0.2, 0.2), dir_.z).normalisedCopy();
}

void Ball::RefectX(float range)
{
	dir_ = Vector3(-dir_.x, dir_.y + Ogre::Math::RangeRandom(-range, range), dir_.z).normalisedCopy();
}

void Ball::RefectY()
{
	dir_ = Vector3(dir_.x + Ogre::Math::RangeRandom(-0.2, 0.2), -dir_.y, dir_.z).normalisedCopy();
}

void Ball::RefectY(float range)
{
	dir_ = Vector3(dir_.x + Ogre::Math::RangeRandom(-range, range), -dir_.y, dir_.z).normalisedCopy();
}