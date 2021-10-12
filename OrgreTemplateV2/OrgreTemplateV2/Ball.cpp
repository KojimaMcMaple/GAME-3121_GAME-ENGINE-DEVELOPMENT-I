#include "Ball.h"

//Ball::Ball()
//{
//
//}

//Ogre::SceneNode* Ball::GetNode() const
//{
//	return node_;
//}
//
//void Ball::SetNode(Ogre::SceneNode* node)
//{
//	node_ = node;
//}
//
//void Ball::SetSpeed(float value)
//{
//	speed_ = value;
//}
//
//void Ball::SetDir(Ogre::Vector3 value)
//{
//	dir_ = value;
//}
//
//void Ball::ResetDir()
//{
//	dir_ = Ogre::Vector3(0, 0, 0);
//}

void Ball::RefectX()
{
	dir_ = Vector3(-dir_.x, dir_.y, dir_.z);
}

void Ball::RefectY()
{
	dir_ = Vector3(dir_.x, -dir_.y, dir_.z);
}

//void Ball::Move(const Ogre::FrameEvent& evt)
//{
//	node_->translate(dir_.normalisedCopy() * speed_ * evt.timeSinceLastFrame);
//}