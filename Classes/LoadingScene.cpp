#include "LoadingScene.h"

LoadingScene::LoadingScene(){}

LoadingScene::~LoadingScene(){}

void LoadingScene::onEnter()
{
	cocos2d::Scene::onEnter();
	
	// add background to current scene
//	Sprite *background = Sprite::create("splash.png");
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	Point origin = Director::getInstance()->getVisibleOrigin();
//	background->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
//	this->addChild(background);
	
//	cocos2d::LayerColor* bg = cocos2d::LayerColor::create(cocos2d::Color4B::WHITE);
//	this->addChild(bg);
//	
//	auto logo = cocos2d::Sprite::create("logo.png");
//	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
//	cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();
//	logo->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
//	this->addChild(logo);
	
	schedule(schedule_selector(LoadingScene::load), 0);
}

void LoadingScene::load(float dt)
{
	Loader::loadEverything();
	
	unschedule(schedule_selector(LoadingScene::load));
	
	auto scene = WelcomeScene::create();
	cocos2d::TransitionScene* transition = cocos2d::TransitionFade::create(1, scene);
	cocos2d::Director::getInstance()->replaceScene(transition);
}
