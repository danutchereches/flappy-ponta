#include "GameLayer.h"

GameLayer::GameLayer(){}

GameLayer::~GameLayer(){}

cocos2d::Animation* banutzAnumation;

bool GameLayer::init()
{
	if (!Layer::init())
		return false;
	
	//get the mOrigin point of the X-Y axis, and the visiable size of the screen
	mScreenSize = Director::getInstance()->getWinSize();
	mVisibleSize = Director::getInstance()->getVisibleSize();
	mOrigin = Director::getInstance()->getVisibleOrigin();
	
	this->gameStatus = GAME_STATUS_READY;
	this->mScore = 0;
	
	// Add the bird
	this->bird = BirdSprite::getInstance();
	this->bird->createBird();
	PhysicsBody *body = PhysicsBody::create();
	body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(false);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->setPositionOffset(cocos2d::Vec2(2.5f, 0));
	this->bird->setPhysicsBody(body);
	this->bird->setPosition(mOrigin.x + mVisibleSize.width*1/3 - 5,mOrigin.y + mVisibleSize.height/2 + 5);
	this->bird->idle();
	this->addChild(this->bird);
	
	// Add the ground
	this->groundNode = Node::create();
	float landHeight = BackgroundLayer::getLandHeight();
	auto groundBody = PhysicsBody::create();
	groundBody->addShape(PhysicsShapeBox::create(Size(288, landHeight)));
	groundBody->setDynamic(false);
	groundBody->setLinearDamping(0.0f);
	groundBody->setContactTestBitmask(0xFFFFFFFF);
	this->groundNode->setPhysicsBody(groundBody);
	this->groundNode->setPosition(144, landHeight/2);
	this->groundNode->setTag(GROUND_TAG);
	this->addChild(this->groundNode);
	
	// init land
	this->landSpite1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("land.jpg"));
	this->landSpite1->setAnchorPoint(Point::ZERO);
	this->landSpite1->setPosition(Point::ZERO);
	this->addChild(this->landSpite1, 30);
	
	this->landSpite2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("land.jpg"));
	this->landSpite2->setAnchorPoint(Point::ZERO);
	this->landSpite2->setPosition(this->landSpite1->getContentSize().width-2.0f,0);
	this->addChild(this->landSpite2, 30);
	
	Vector<SpriteFrame*> frames;
	frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("banut1.png"));
	frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("banut2.png"));
	frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("banut3.png"));
	frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("banut4.png"));
	banutzAnumation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1f);
	banutzAnumation->retain();
	
	SpriteFrame* banutFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("banut1.png");
	
	mBanutPool.init(5, banutFrame, this);
	
	shiftLand = schedule_selector(GameLayer::scrollLand);
	this->schedule(shiftLand, 0.01f);
	
	this->scheduleUpdate();
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}

bool GameLayer::onContactBegin(const PhysicsContact& contact)
{
	cocos2d::log("contact tag %d - %d",
			contact.getShapeA()->getBody()->getNode()->getTag(),
			contact.getShapeB()->getBody()->getNode()->getTag()
	);
	
	if (this->gameStatus == GAME_STATUS_START)
	{
		if (contact.getShapeA()->getBody()->getNode()->getTag() == GROUND_TAG
		 || contact.getShapeB()->getBody()->getNode()->getTag() == GROUND_TAG)
		{
			this->bird->getPhysicsBody()->setVelocity(Vect(0, 40));
		}
		else/* if (contact.getShapeA()->getBody()->getNode()->getTag() == PIP_NEW
		 || contact.getShapeB()->getBody()->getNode()->getTag() == PIP_NEW)*/
		{
			this->gameOver();
		}
	}
	
	return true;
}

void GameLayer::scrollLand(float dt)
{
	this->landSpite1->setPositionX(this->landSpite1->getPositionX() - 0.7f);
	this->landSpite2->setPositionX(this->landSpite1->getPositionX() + this->landSpite1->getContentSize().width - 0.7f);
	if (this->landSpite2->getPositionX() <= 0)
		this->landSpite1->setPositionX(0);
	
	// move the pips
	Node* pip;
	for (cocos2d::Vector<Node*>::iterator iter = this->pips.begin(); iter != this->pips.end(); iter++)
	{
		pip = *iter;
		pip->setPositionX(pip->getPositionX() - 0.7f);
		
		if (pip->getTag() == PIP_NEW && pip->getPositionX() < mScreenSize.width)
		{
			Sprite* banutz = mBanutPool.obtainPoolItem();
			banutz->setVisible(true);
			banutz->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(banutzAnumation)));
			banutz->setPosition(cocos2d::Vec2(pip->getPositionX() + PIP_INTERVAL * 0.5f, mScreenSize.height * 0.3f + rand() % (int) (mScreenSize.height * 0.6f)));
			banutz->setTag(BANUTZ_TAG);
			banutz->resume();
			banutzs.pushBack(banutz);
			
			pip->setTag(PIP_PASS);
		}
	}
	
	if (this->pips.size() > 1)
	{
		auto front = this->pips.front();
		if(front->getPositionX() < -PIP_WIDTH)
		{
			front->setTag(PIP_NEW);
			front->setPositionX(this->pips.back()->getPositionX() + PIP_INTERVAL * 0.8f + rand() % (int) (PIP_INTERVAL * 0.3f));
			front->setPositionY(this->getRandomHeight());
			this->pips.erase(this->pips.begin());
			this->pips.pushBack(front);
		}
	}
	
	// move the banutzs
	Node* banutz;
	for (cocos2d::Vector<Sprite*>::iterator iter = this->banutzs.begin(); iter != this->banutzs.end(); iter++)
	{
		banutz = *iter;
		banutz->setPositionX(banutz->getPositionX() - 0.7f);
	}
	
	if (this->banutzs.size() > 1)
	{
		auto front = this->banutzs.front();
		if(front->getPositionX() < -PIP_WIDTH)
		{
			front->setTag(BANUTZ_LUAT_TAG);
			front->setVisible(false);
			front->stopAllActions();
			banutzs.eraseObject(front, true);
			mBanutPool.recyclePoolItem(front);
		}
	}
}

void GameLayer::onTouch()
{
	if(this->gameStatus == GAME_STATUS_OVER)
		return;
	
	SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
	if(this->gameStatus == GAME_STATUS_READY)
	{
		this->delegator->onGameStart();
		this->bird->fly();
		this->gameStatus = GAME_STATUS_START;
		this->createPips();
	}
	else if(this->gameStatus == GAME_STATUS_START)
	{
		if (this->bird->getPositionY() < Director::getInstance()->getVisibleSize().height - this->bird->getContentSize().height/2)
			this->bird->getPhysicsBody()->setVelocity(Vect(0, 70));
	}
}

void GameLayer::rotateBird()
{
	float verticalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
	this->bird->setRotation(min(120, max(-90, verticalSpeed*(-0.4f) + 60)));
}

void GameLayer::update(float delta)
{
	if (this->gameStatus == GAME_STATUS_START)
	{
		this->rotateBird();
		this->checkHit();
	}
}

void GameLayer::createPips()
{
	// Create the pips
	for (int i = 0; i < PIP_COUNT; i++)
	{
		Size screenSize = Director::getInstance()->getWinSize();
		
		Sprite *pipUp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tub.png"));
		pipUp->setScaleY(-1);
		
		Sprite *pipDown = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tub.png"));
		pipDown->setPosition(0, PIP_HEIGHT + PIP_DISTANCE);
		
		// bind to pair
		Node *singlePip = Node::create();
		singlePip->addChild(pipDown, 0, DOWN_PIP);
		singlePip->addChild(pipUp, 0, UP_PIP);
		singlePip->setPosition(screenSize.width + WAIT_DISTANCE + (PIP_INTERVAL * 0.8f + rand() % (int) (PIP_INTERVAL * 0.3f)) * i, this->getRandomHeight());
		auto body = PhysicsBody::create();
		auto shapeBoxDown = PhysicsShapeBox::create(pipDown->getContentSize(),PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, PIP_HEIGHT + PIP_DISTANCE));
		body->addShape(shapeBoxDown);
		body->addShape(PhysicsShapeBox::create(pipUp->getContentSize()));
		body->setContactTestBitmask(0xFFFFFFFF);
		body->setDynamic(false);
		singlePip->setPhysicsBody(body);
		singlePip->setTag(PIP_NEW);
		
		this->addChild(singlePip);
		this->pips.pushBack(singlePip);
	}
}

int GameLayer::getRandomHeight()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	return rand()%(int)(2*PIP_HEIGHT + PIP_DISTANCE - visibleSize.height - 15) + 15;
}

void GameLayer::checkHit()
{
	Rect birdRect = Rect(this->bird->getPositionX() - 5, this->bird->getPositionY() - 5, 10, 10);
	
	for(auto banutz : this->banutzs)
	{
		if (banutz->getTag() == BANUTZ_LUAT_TAG)
			continue;
		
		Rect rect = cocos2d::Rect(
			banutz->getPosition().x - (banutz->getContentSize().width * 0.7f / 2),
			banutz->getPosition().y - (banutz->getContentSize().height * 0.7f / 2),
			banutz->getContentSize().width * 0.7f,
			banutz->getContentSize().height * 0.7f);
		
		if (rect.intersectsRect(birdRect))
		{
			SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
			this->mScore++;
			this->delegator->onGamePlaying(this->mScore);
			banutz->setTag(BANUTZ_LUAT_TAG);
			banutz->setVisible(false);
			banutz->stopAllActions();
			banutzs.eraseObject(banutz, true);
			mBanutPool.recyclePoolItem(banutz);
			break;
		}
	}
}

void GameLayer::gameOver()
{
	if (this->gameStatus == GAME_STATUS_OVER)
		return;
	
	SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
	//get the best score
	int bestScore = UserRecord::getInstance()->readIntegerFromUserDefault("best_score");
	//update the best score
	if(this->mScore > bestScore)
		UserRecord::getInstance()->saveIntegerToUserDefault("best_score",this->mScore);
	
	this->delegator->onGameEnd(this->mScore, bestScore);
	this->unschedule(shiftLand);
	SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
	this->bird->die();
	this->bird->setRotation(120);
	this->birdSpriteFadeOut();
	this->gameStatus = GAME_STATUS_OVER;
}

void GameLayer::birdSpriteFadeOut()
{
	FadeOut* animation = FadeOut::create(1.5f);
	CallFunc* animationDone = CallFunc::create(bind(&GameLayer::birdSpriteRemove,this));
	Sequence* sequence = Sequence::create(animation,animationDone, NULL);
	this->bird->stopAllActions();
	this->bird->runAction(sequence);
}

void GameLayer::birdSpriteRemove()
{
	this->removeChild(this->bird);
}

void GameLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	cocos2d::log("button press %d", keyCode);
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		if (AppDelegate::pluginAnalytics != nullptr)
			AppDelegate::pluginAnalytics->logEvent("click_back_btn");
		
		AppDelegate::closeApp();
	}
}
