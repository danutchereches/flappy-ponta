#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"
#include "BackgroundLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

class LoadingScene : public Scene {
public:
	LoadingScene();
	~LoadingScene();
	
	CREATE_FUNC(LoadingScene);
	void onEnter() override;
private:
	void load(float dt);
};
