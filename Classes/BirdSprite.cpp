#include "BirdSprite.h"

BirdSprite::BirdSprite() {}

BirdSprite::~BirdSprite() {}

BirdSprite* BirdSprite::shareBirdSprite = nullptr;
BirdSprite* BirdSprite::getInstance()
{
	if(shareBirdSprite == NULL)
	{
		shareBirdSprite = new BirdSprite();
		if(!shareBirdSprite->init())
		{
			delete(shareBirdSprite);
			shareBirdSprite = NULL;
			CCLOG("ERROR: Could not init shareBirdSprite");
		}
	}
	return shareBirdSprite;
}

bool BirdSprite::init()
{
	Sprite::initWithSpriteFrameName("ponta0.png");
	this->isFirstTime = 3;
	return true;
}

bool BirdSprite::createBird()
{
	// init idle status
	this->setOpacity(255);
	this->setVisible(true);
	this->setRotation(0);
	//create the bird animation
	Animation* animation = this->createAnimation("ponta%d.png", 3, 10);
	Animate* animate = Animate::create(animation);
	this->idleAction = RepeatForever::create(animate);
	
	// create the swing action
	ActionInterval *up = CCMoveBy::create(0.4f,Point(0, 8));
	ActionInterval *upBack= up->reverse();
	this->swingAction = RepeatForever::create(Sequence::create(up, upBack, NULL));
	
	return true;
}

void BirdSprite::idle()
{
	if (changeState(ACTION_STATE_IDLE))
	{
		this->runAction(idleAction);
		this->runAction(swingAction);
	}
}

void BirdSprite::fly()
{
	if(changeState(ACTION_STATE_FLY))
	{
		this->stopAction(swingAction);
		this->getPhysicsBody()->setGravityEnable(true);
	}
}

void BirdSprite::die()
{
	if(changeState(ACTION_STATE_DIE))
		this->stopAllActions();
}

Animation* BirdSprite::createAnimation(const char *fmt, int count, float fps)
{
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(1/fps);
	for (int i = 0; i < count; i++)
	{
		const char *filename = String::createWithFormat(fmt, i)->getCString();
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	return animation;
}

bool BirdSprite::changeState(ActionState state)
{
	//this->stopAllActions();
	currentStatus = state;
	return true;
}
