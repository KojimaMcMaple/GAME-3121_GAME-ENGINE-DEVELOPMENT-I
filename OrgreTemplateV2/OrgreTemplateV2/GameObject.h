#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class GameObject
{
protected:
    Ogre::SceneNode* node_;
    float speed_;
    Ogre::Vector3 dir_;

public:
    GameObject();
    virtual ~GameObject();

    Ogre::SceneNode* GetNode() const;
    void SetNode(Ogre::SceneNode* node);
    void SetSpeed(float value);
    void SetDir(Ogre::Vector3 value);
    void ResetDir();

    void Move(const Ogre::FrameEvent& evt);
};