#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
	if (!LayerColor::initWithColor(cocos2d::Color4B(133, 185, 209, 255)))
		return false;
	
	Size screenSize = Director::getInstance()->getWinSize();
	
	LayerColor* background = LayerColor::create(Color4B(193, 193, 193, 255));
	background->ignoreAnchorPointForPosition(false);
	background->setContentSize(Size(screenSize.width, screenSize.height*0.5f));
	background->setAnchorPoint(cocos2d::Vec2(0, 0));
	background->setPosition(Vec2::ZERO);
	this->addChild(background);
	
	auto bgS = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.jpg"));
	bgS->setPosition(cocos2d::Vec2(screenSize.width/2, background->getContentSize().height));
	bgS->setAnchorPoint(cocos2d::Vec2(0.5f, 1));
	background->addChild(bgS);
	
	return true;
}

float BackgroundLayer::getLandHeight()
{
	return Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("land.jpg"))->getContentSize().height;
}
