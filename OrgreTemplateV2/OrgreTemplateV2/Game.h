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
    bool is_intersecting_;
    OgreBites::Label* mScore;
    int* score_;
    OgreBites::Label* mTpu;
    float* time_;
    OgreBites::Label* mLives;
    int* lives_;
public:

    GameFrameListener(Camera* cam, Paddle* paddle, Ball* ball, 
        OgreBites::Label* score_label, int& score,
        OgreBites::Label* tpu_label, float& time,
        OgreBites::Label* lives_label, int& lives)
    {
        cam_ = cam;
        paddle_node_ = paddle;
        ball_node_ = ball;
        mScore = score_label;
        score_ = &score;
        mTpu = tpu_label;
        time_ = &time;
        mLives = lives_label;
        lives_ = &lives;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        mTpu->setCaption(Ogre::StringConverter::toString(evt.timeSinceLastFrame));
        
        //paddle_node_->translate(translate * evt.timeSinceLastFrame);
        //translate = Ogre::Vector3(0, 0, 0);
        paddle_node_->Move(evt);
        paddle_node_->ResetDir();
        //ball_node_->translate(translate2 * evt.timeSinceLastFrame);
        ball_node_->Move(evt);

        Ogre::Vector3 ball_screen_pos = cam_->getProjectionMatrix() * cam_->getViewMatrix() *
            ball_node_->GetNode()->convertLocalToWorldPosition(ball_node_->GetNode()->getPosition());
        //printf(">>> %f\n", ball_screen_pos.x);
        if (ball_screen_pos.x >= 1 || ball_screen_pos.x <= -1)
        {
            ball_node_->RefectX();
        }
        else if (ball_screen_pos.y >= 1)
        {
            ball_node_->RefectY();
        }
        else if (ball_screen_pos.y <= -1) //DEATH
        {
            --(*lives_);
            mLives->setCaption(Ogre::StringConverter::toString(*lives_));
            
            ball_node_->GetNode()->setPosition(0, 100, 0);
            ball_node_->SetDir(Ogre::Vector3(Ogre::Math::RangeRandom(-0.7, 0.7),
                                Ogre::Math::RangeRandom(-1, -0.5),
                                0).normalisedCopy());
        }

        if (ball_node_->GetNode()->_getWorldAABB().intersects(paddle_node_->GetNode()->_getWorldAABB()))
        {
            if (!is_intersecting_)
            {
                is_intersecting_ = true;
                ++(*score_);
                mScore->setCaption(Ogre::StringConverter::toString(*score_));
                ball_node_->RefectY(0.4);
            }
        }
        else
        {
            is_intersecting_ = false;
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
    int score_ = 0;
    OgreBites::Label* mTpuLabel;
    OgreBites::Label* mTpu;
    float time_ = 0;
    OgreBites::Label* mLivesLabel;
    OgreBites::Label* mLives;
    int lives_ = 5;
    
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
