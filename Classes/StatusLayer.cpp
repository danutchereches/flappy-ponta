#include "StatusLayer.h"


StatusLayer::StatusLayer(){};

StatusLayer::~StatusLayer(){};


bool StatusLayer::init()
{
	if(!Layer::init())
		return false;
	
	// init numbers
	this->bestScore = 0;
	this->currentScore = 0;
	this->isNewRecord = false;
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->originPoint = Director::getInstance()->getVisibleOrigin();
	this->screeenSize = Director::getInstance()->getWinSize();
	this->showReadyStatus();
	this->loadWhiteSprite();
	return true;
}

void StatusLayer::showReadyStatus()
{
	scoreSprite = cocos2d::Label::createWithTTF("0", "fonts/robo.ttf", 10);
	scoreSprite->setColor(Color3B(176, 19, 19));
	scoreSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2,this->originPoint.y + this->visibleSize.height *5/6));
	this->addChild(scoreSprite);
	
	getreadySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("text_ready.png"));
	getreadySprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y + this->visibleSize.height * 0.66f));
	this->addChild(getreadySprite);
	
	tutorialSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tutorial.png"));
	tutorialSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y + this->visibleSize.height * 0.4f));
	this->addChild(tutorialSprite);
}

void StatusLayer::showStartStatus()
{
	this->getreadySprite->runAction(FadeOut::create(0.4f));
	this->tutorialSprite->runAction(FadeOut::create(0.4f));
}

void StatusLayer::showOverStatus(int curScore, int bestScore)
{
	this->currentScore = curScore;
	this->bestScore = bestScore;
	if(curScore > bestScore){
		this->bestScore = curScore;
		this->isNewRecord = true;
	}else{
		this->isNewRecord = false;
	}
	this->removeChild(scoreSprite);
	this->blinkFullScreen();
	
	if (AppDelegate::pluginAnalytics != nullptr)
		AppDelegate::pluginAnalytics->callFuncWithParam("logPageView", new cocos2d::plugin::PluginParam("game_over_scene"), nullptr);
}

void StatusLayer::onGameStart()
{
	this->showStartStatus();
}

void StatusLayer::onGamePlaying(int score)
{
	this->scoreSprite->setString(__String::createWithFormat("%d", -score)->_string);
}

void StatusLayer::onGameEnd(int curScore, int bestScore)
{
	this->showOverStatus(curScore,bestScore);
}

void StatusLayer::loadWhiteSprite()
{
	//this white sprite is used for blinking the screen for a short while
	whiteSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("white.png"));
	whiteSprite->setScale(150);
	whiteSprite->setOpacity(0);
	this->addChild(whiteSprite,10000);
}

void StatusLayer::blinkFullScreen()
{
	//display a flash blink
	auto fadeOut = FadeOut::create(0.1f);
	auto fadeIn = FadeIn::create(0.1f);
	auto blinkAction = Sequence::create(fadeIn,fadeOut,NULL);
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInGameOver, this));
	auto sequence = Sequence::createWithTwoActions(blinkAction, actionDone);
	whiteSprite->stopAllActions();
	whiteSprite->runAction(sequence);
}

void StatusLayer::fadeInGameOver()
{
	// create the game over panel
	Sprite* gameoverSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("text_game_over.png"));
	gameoverSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y + this->visibleSize.height * 0.8f));
	this->addChild(gameoverSprite);
	auto gameoverFadeIn = FadeIn::create(0.5f);
	
	// Start next action
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::jumpToScorePanel, this));
	auto sequence = Sequence::createWithTwoActions(gameoverFadeIn, actionDone);
	gameoverSprite->stopAllActions();
	gameoverSprite->runAction(sequence);
}

void StatusLayer::jumpToScorePanel()
{
	// create the score panel
	Sprite* scorepanelSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("score_panel.png"));
	scorepanelSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y - scorepanelSprite->getContentSize().height));
	this->addChild(scorepanelSprite);
	
	//display the  score on the score panel
	auto scoreSprite = cocos2d::Label::createWithTTF(__String::createWithFormat("%d", -this->currentScore)->_string, "fonts/robo.ttf", 8);
	scoreSprite->setColor(Color3B(176, 19, 19));
	scoreSprite->setPosition(scorepanelSprite->getContentSize().width/2, scorepanelSprite->getContentSize().height * 0.56f);
	scorepanelSprite->addChild(scoreSprite);
	
	//display the  best score on the score panel
	auto bestScoreSprite = cocos2d::Label::createWithTTF(__String::createWithFormat("%d", -this->bestScore)->_string, "fonts/robo.ttf", 8);
	bestScoreSprite->setColor(Color3B(176, 19, 19));
	bestScoreSprite->setPosition(scorepanelSprite->getContentSize().width/2, scorepanelSprite->getContentSize().height * 0.16f);
	scorepanelSprite->addChild(bestScoreSprite);
	
	// Start next action
	auto scorePanelMoveTo = MoveTo::create(0.8f ,Point(this->originPoint.x + this->visibleSize.width / 2,this->originPoint.y + this->visibleSize.height * 0.55f));
	// add variable motion for the action
	EaseExponentialOut* sineIn = EaseExponentialOut::create(scorePanelMoveTo);
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInRestartBtn, this));
	auto sequence = Sequence::createWithTwoActions(sineIn, actionDone);
	scorepanelSprite->stopAllActions();
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	scorepanelSprite->runAction(sequence);
}

void StatusLayer::fadeInRestartBtn()
{
	//create the restart menu;
	auto restart = MyMenuItem::create(Sprite::createWithSpriteFrameName("button_play.png"), CC_CALLBACK_0(StatusLayer::menuRestartCallback, this));
	restart->setPosition(Point(this->originPoint.x + this->visibleSize.width * 0.2f, this->originPoint.y + this->visibleSize.height * 0.26f));
	
	auto rate = MyMenuItem::create(Sprite::createWithSpriteFrameName("button_rate.png"), CC_CALLBACK_0(StatusLayer::menuRateCallback,this));
	rate->setPosition(Point(this->originPoint.x + this->visibleSize.width * 0.5f, this->originPoint.y + this->visibleSize.height * 0.26f));
	
	auto share = MyMenuItem::create(Sprite::createWithSpriteFrameName("button_share.png"), CC_CALLBACK_0(StatusLayer::menuShareCallback,this));
	share->setPosition(Point(this->originPoint.x + this->visibleSize.width * 0.8f, this->originPoint.y + this->visibleSize.height * 0.26f));
	
	auto menu = Menu::create(restart, rate, share, NULL);
	menu->setAnchorPoint(Vec2::ZERO);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void StatusLayer::menuRestartCallback()
{
	if (AppDelegate::pluginAnalytics != nullptr)
		AppDelegate::pluginAnalytics->logEvent("click_restart");
	
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void StatusLayer::menuRateCallback()
{
	if (AppDelegate::pluginAnalytics != nullptr)
		AppDelegate::pluginAnalytics->logEvent("click_rate");
	
	helpers::URL::open((char*) "https://play.google.com/store/apps/details?id=com.hatersallover.victo.rush");
}

void StatusLayer::menuShareCallback()
{
	if (AppDelegate::pluginAnalytics != nullptr)
		AppDelegate::pluginAnalytics->logEvent("click_share");
	
	helpers::URL::open((char*) "https://www.facebook.com/sharer.php?u=http://goo.gl/c1M4YW");
}
