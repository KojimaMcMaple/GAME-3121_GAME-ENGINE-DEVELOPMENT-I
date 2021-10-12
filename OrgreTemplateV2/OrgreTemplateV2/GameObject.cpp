#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
= default;

Ogre::SceneNode* GameObject::GetNode() const
{
	return node_;
}

void GameObject::SetNode(Ogre::SceneNode* node)
{
	node_ = node;
}

void GameObject::SetSpeed(float value)
{
	speed_ = value;
}

void GameObject::SetDir(Ogre::Vector3 value)
{
	dir_ = value;
}

void GameObject::ResetDir()
{
	dir_ = Ogre::Vector3(0, 0, 0);
}

void GameObject::Move(const Ogre::FrameEvent& evt)
{
	node_->translate(dir_ * speed_ * evt.timeSinceLastFrame);
}
