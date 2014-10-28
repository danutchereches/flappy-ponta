#ifndef __LOADER_H__
#define __LOADER_H__

#include "cocos2d.h"
#include "Objects.h"

class Loader
{
public:
	static void loadEverything();
	static void loadEverything(const std::function<void()>& func);
	static cocos2d::SpriteFrameCache* getFrameCache();

	static cocos2d::SpriteFrameCache* mFrameCache;
	
	static void loadTextures();
	static void loadSounds();
	static void loadAnimations();
	static void loadObjects();
};

#endif // __LOADER_H__
