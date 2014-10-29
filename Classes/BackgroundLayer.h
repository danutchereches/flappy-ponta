#pragma once
#include "cocos2d.h"
#include "time.h"
using namespace cocos2d;
using namespace std;

class BackgroundLayer:public LayerColor
{
public:
	virtual bool init() override;
	
	CREATE_FUNC(BackgroundLayer);
	
	static float getLandHeight();
};
