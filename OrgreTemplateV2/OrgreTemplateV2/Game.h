#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>
#include "Ball.h"
#include "Paddle.h"

using namespace Ogre;
using namespace OgreBites;

class GameFrameListener : public Ogre::FrameListener
{
private:
    Paddle* paddle_node_;
    Ball* ball_node_;
    Camera* cam_;
public:

    GameFrameListener(Camera* cam, Paddle* paddle, Ball* ball)
    {
        cam_ = cam;
        paddle_node_ = paddle;
        ball_node_ = ball;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        //paddle_node_->translate(translate * evt.timeSinceLastFrame);
        //translate = Ogre::Vector3(0, 0, 0);
        paddle_node_->Move(evt);
        paddle_node_->ResetDir();
        //ball_node_->translate(translate2 * evt.timeSinceLastFrame);
        ball_node_->Move(evt);

        Ogre::Vector3 ball_screen_pos = cam_->getProjectionMatrix() * cam_->getViewMatrix() *
            ball_node_->GetNode()->convertLocalToWorldPosition(ball_node_->GetNode()->getPosition());
        //printf(">>> %f\n", ball_screen_pos.x);
        if (ball_node_->GetNode()->_getWorldAABB().intersects(paddle_node_->GetNode()->_getWorldAABB()))
        {
            ball_node_->ResetDir();
        }

        return true;
    }
};

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    OgreBites::Label* mScoreLabel;
    OgreBites::Label* mScore;
    OgreBites::Label* mTpuLabel;
    OgreBites::Label* mTpu;
    OgreBites::Label* mLivesLabel;
    OgreBites::Label* mLives;
    
    Camera* cam;
    Ball* ballNode;
    Paddle* paddleNode;

public:
    Game();
    virtual ~Game() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    void createFrameListener();
    OgreBites::TrayListener myTrayListener;
    OgreBites::Label* mInfoLabel;
};

//! [fullsource]
