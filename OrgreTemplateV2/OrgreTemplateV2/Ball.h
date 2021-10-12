#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>
#include "GameObject.h"

using namespace Ogre;
using namespace OgreBites;

class Ball : public GameObject
{
private:    
    //Ogre::SceneNode* node_;
    //float speed_;
    //Ogre::Vector3 dir_;

public:
    //Ball();
    //~Ball() {}

    //Ogre::SceneNode* GetNode() const;
    //void SetNode(Ogre::SceneNode* node);
    //void SetSpeed(float value);
    //void SetDir(Ogre::Vector3 value);
    //void ResetDir();
    void RefectX();
    void RefectX(float range);
    void RefectY();
    void RefectY(float range);

    //void Move(const Ogre::FrameEvent& evt);
};