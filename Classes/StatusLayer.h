#pragma once

#include "cocos2d.h"
#include "Objects.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

class StatusLayer : public Layer, public StatusDelegate
{
public:
	StatusLayer(void);

	~StatusLayer(void);

	virtual bool init();

	CREATE_FUNC(StatusLayer);

	void onGameStart();

	void onGamePlaying(int score);

	void onGameEnd(int curScore, int bestScore);

private:
	void showReadyStatus();

	void showStartStatus();

	void showOverStatus(int curScore, int bestScore);

	void loadWhiteSprite();

	void blinkFullScreen();

	void fadeInGameOver();

	void jumpToScorePanel();

	void fadeInRestartBtn();

	void menuRestartCallback();

	void menuRateCallback();

	void menuShareCallback();

	Label* scoreSprite;

	Sprite* getreadySprite;

	Sprite* tutorialSprite;

	Sprite* whiteSprite;
	
	int currentScore;
	
	int bestScore;
	
	int tmpScore;

	bool isNewRecord;

	Point originPoint;

	Size visibleSize;
	
	Size screeenSize;
};
