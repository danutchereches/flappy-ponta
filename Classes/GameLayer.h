#pragma once

#include "cocos2d.h"
#include "AppDelegate.h"
#include "UserRecord.h"
#include "OptionLayer.h"
#include "BirdSprite.h"
#include "BackgroundLayer.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

#define min(X,Y) ((X) < (Y) ? (X) : (Y)) 
#define max(X,Y) ((X) > (Y) ? (X) : (Y)) 

const int UP_PIP = 21;

const int DOWN_PIP = 12;
const int MILITIA = 13;

const int PIP_PASS = 30;

const int PIP_NEW = 31;

const int GROUND_TAG = 90;
const int BANUTZ_TAG = 91;
const int BANUTZ_LUAT_TAG = 92;

/**
 * The radius of the bird
 */
const int BIRD_RADIUS = 7;

/**
 * The height of the pips
 */
const int PIP_HEIGHT = 100;

const int MILITIA_HEIGHT = 20;

/**
 * The width of the pips
 */
const int PIP_WIDTH = 10;

/**
 * Pip shift speed
 */
const float PIP_SHIFT_SPEED = 80.0f;

/**
 * The distance between the down pip and up pip
 */
const int PIP_DISTANCE = 40;

/**
 * The distance between the pips vertical
 */
const int PIP_INTERVAL = 100;

/**
 * The number of pip pairs display in the screen in the same time
 */
const int PIP_COUNT = 3;

/**
 * The distance that the pip will display in the screen, for player to ready
 */
const int WAIT_DISTANCE = 40;

/**
* Define the game status
* GAME_STATUS_READY game is not start, just ready for payer to start.
* GAME_STATUS_START the game is started, and payer is paying this game.
* GAME_STATUS_OVER the player is lose this game, the game is over.
*/
typedef enum _game_status {
	GAME_STATUS_READY = 1,
	GAME_STATUS_START,
	GAME_STATUS_OVER
} GameStatus;


class GameLayer : public Layer, public OptionDelegate
{
public:
	GameLayer();

	~GameLayer();

	bool virtual init();

	CREATE_FUNC(GameLayer);

	/**
	* According to current game status, give the order to delegate.
	*/
	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

	/**
	* @Override 
	* To see @OptionDelegate::onTouch 
	* User have touched the screen
	* This game, user just need only this method to control game
	*/
	void onTouch();

	/**
	* This layer need physical engine work
	*/
	void setPhyWorld(PhysicsWorld* world){this->world = world;}
    
    void update(float delta);

private:
    /**
     * Set the rotate for the bird,let it looks like the head is very heavy.
     */
    void rotateBird();
    
    /**
     * create new pips and make it move from left to right then remove from parent
     */
    void createPips();
    
    /**
     * get a random number that can set the pip height
     */
    int getRandomHeight();
    
    /**
     * Check the if the bird have hit anything
     */
    void checkHit();
    
	/**
	 * Since the only global bird can not be addChilded to two layers
	 * we must delete it from one layer,and then add it to another layer
	 * Here we use the fadeout animation to delete it from the gamelayer, so when the player 
	 * press the restart button, the bird can be added successfully
	 */
	void birdSpriteFadeOut();

	 /*
	 * After running the fadeout animation, delete the bird from current layer
	 */
	void birdSpriteRemove();

	cocos2d::Size mScreenSize;
	cocos2d::Size mVisibleSize;
	cocos2d::Vec2 mOrigin;

    PhysicsWorld *world;

    GameStatus gameStatus;

    int mScore;

    BirdSprite *bird;
    
    Node *groundNode;
    
    cocos2d::Vector<Node*> pips;
    cocos2d::Vector<Sprite*> banutzs;
    BanutzPool mBanutPool;
    
    Sprite *landSpite1,*landSpite2;

	SEL_SCHEDULE  shiftLand;
    
	void scrollLand(float dt);

	bool onContactBegin(const PhysicsContact& contact);

	void gameOver();
	
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};
