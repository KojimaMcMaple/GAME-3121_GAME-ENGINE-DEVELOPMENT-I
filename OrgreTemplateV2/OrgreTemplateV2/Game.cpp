#include "Game.h"

Game::Game()
    : ApplicationContext("TrungLe101264698_GAME3121_A1")
{
}

void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);


    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(20, 80, 50);
    //! [lightpos]

    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);
    //! [camera]

    //! [cameramove]
    camNode->setPosition(0, 47, 222);
    //! [cameramove]

    OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());

    //you must add this in order to add a tray
    scnMgr->addRenderQueueListener(mOverlaySystem);
    //Once you have your tray manager, make sure you relay input events to it.
    addInputListener(mTrayMgr);

    //mTrayMgr->showLogo(TL_TOPRIGHT);
    mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
    //mTrayMgr->toggleAdvancedFrameStats();

    mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "My Game Engine", 350);
    mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score:", 150);
    mScore = mTrayMgr->createLabel(TL_TOPLEFT, "score", "0", 150);
    mTpuLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Time/Update", "Time/Update:", 150);
    mTpu = mTrayMgr->createLabel(TL_TOPRIGHT, "tpu", "0", 150);
    mLivesLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Lives", "Lives:", 150);
    mLives = mTrayMgr->createLabel(TL_TOPLEFT, "lives", "5", 150);

    //// a friendly reminder
    //StringVector names;
    //names.push_back("Help");
    //mTrayMgr->createParamsPanel(TL_TOPLEFT, "Help", 100, names)->setParamValue(0, "H/F1");

    Ogre::Entity* ballEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_SPHERE);
    ballNode = new Ball();
    ballNode->SetSpeed(20);
    //ballNode->SetDir(Ogre::Vector3(0, -1, 0));
    ballNode->SetDir(Ogre::Vector3(0.5, -0.5, 0));
    ballNode->SetNode(scnMgr->getRootSceneNode()->createChildSceneNode());
    ballNode->GetNode()->setPosition(0, 70, 0);
    ballNode->GetNode()->setScale(0.1f, 0.1f, 0.1f);
    ballNode->GetNode()->attachObject(ballEntity);

    Ogre::Entity* paddleEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_PLANE);
    paddleNode = new Paddle();
    paddleNode->SetSpeed(300);
    paddleNode->SetNode(scnMgr->getRootSceneNode()->createChildSceneNode());
    paddleNode->GetNode()->setPosition(0, -10, 0);
    paddleNode->GetNode()->setScale(0.2f, 0.05f, 1.0f);
    paddleNode->GetNode()->attachObject(paddleEntity);

    scnMgr->showBoundingBoxes(true);

    createFrameListener();
}


bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;
    case SDLK_LEFT:
    case 'a':
    case 'A':
        //translate = Ogre::Vector3(-300, 0, 0);
        paddleNode->SetDir(Ogre::Vector3(-1, 0, 0));
        break;
    case SDLK_RIGHT:
    case 'd':
    case 'D':
        //translate = Ogre::Vector3(300, 0, 0);
        paddleNode->SetDir(Ogre::Vector3(1, 0, 0));
        break;
    default:
        break;
    }
    return true;
}

void Game::createFrameListener()
{
    Ogre::FrameListener* frameListener = new GameFrameListener(cam, paddleNode, ballNode);
    mRoot->addFrameListener(frameListener);
}
