#include "WelcomeLayer.h"

bool WelcomeLayer::init()
{
	if (!LayerColor::initWithColor(cocos2d::Color4B(133, 185, 209, 255)))
		return false;
	
	//get the origin point of the X-Y axis, and the visiable size of the screen
	Size screenSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	//create the background image according to the current time;
	LayerColor* background = LayerColor::create(Color4B(193, 193, 193, 255));
	background->setContentSize(Size(screenSize.width, screenSize.height*0.5f));
	background->setAnchorPoint(cocos2d::Vec2(0, 0));
	background->setPosition(Vec2::ZERO);
	auto bgS = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.jpg"));
	bgS->setPosition(cocos2d::Vec2(screenSize.width/2, background->getContentSize().height));
	bgS->setAnchorPoint(cocos2d::Vec2(0.5f, 1));
	background->addChild(bgS);
	this->addChild(background);
	
	//add the word game-title to the current scene
	Sprite *title  = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("title.png"));
	title->setPosition(Point(origin.x + visibleSize.width/2 , (visibleSize.height * 5) / 7));
	this->addChild(title);
	
	//add the start-menu to the current scene
	Sprite *startButton = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("button_play.png"));
	Sprite *activeStartButton = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("button_play.png"));
	activeStartButton->setPositionY(1);
	auto menuItem  = MenuItemSprite::create(startButton,activeStartButton,NULL,CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this));
	menuItem->setPosition(Point(visibleSize.width/2 ,visibleSize.height*2/5));
	
	auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(origin.x ,origin.y));
	this->addChild(menu,1);
	
	//create a bird and set the position in the center of the screen
	this->bird = BirdSprite::getInstance();
	this->bird->createBird();
	this->bird->setTag(BIRD_SPRITE_TAG);
	this->bird->setPosition(Point(origin.x + visibleSize.width / 2,origin.y + visibleSize.height*3/5 - 10));
	this->bird->idle();
	this->addChild(this->bird);
	
	// Add the land
	this->land1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("land.jpg"));
	this->land1->setAnchorPoint(Point::ZERO);
	this->land1->setPosition(Point::ZERO);
	this->addChild(this->land1);
	
	this->land2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("land.jpg"));
	this->land2->setAnchorPoint(Point::ZERO);
	this->land2->setPosition(this->land1->getContentSize().width - 2.0f, 0);
	this->addChild(this->land2);
	
	this->schedule(schedule_selector(WelcomeLayer::scrollLand), 0.01f);
	
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(WelcomeLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}

void WelcomeLayer::scrollLand(float dt)
{
	this->land1->setPositionX(this->land1->getPositionX() - 0.5f);
	this->land2->setPositionX(this->land1->getPositionX() + this->land1->getContentSize().width - 0.5f);
	
	if(this->land2->getPositionX() == 0)
		this->land1->setPositionX(0);
}

void WelcomeLayer::menuStartCallback(Ref *sender)
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	this->removeChildByTag(BIRD_SPRITE_TAG);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void WelcomeLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	cocos2d::log("button press %d", keyCode);
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		if (AppDelegate::pluginAnalytics != nullptr)
			AppDelegate::pluginAnalytics->logEvent("click_back_btn");
		
		AppDelegate::closeApp();
	}
}
