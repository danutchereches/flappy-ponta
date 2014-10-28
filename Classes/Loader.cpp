#include "Loader.h"

cocos2d::SpriteFrameCache* Loader::mFrameCache = nullptr;

void Loader::loadEverything()
{
	loadEverything(NULL);
}

void Loader::loadEverything(const std::function<void()>& func)
{
	loadSounds();
	loadTextures();
	loadAnimations();
	loadObjects();
	
	if (func)
		func();
}


void Loader::loadSounds()
{
//	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("");
	
//	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mfx/");
}

void Loader::loadTextures()
{
	mFrameCache = cocos2d::SpriteFrameCache::getInstance();
	mFrameCache->retain();
//	mFrameCache->addSpriteFramesWithFile("spritesheet.plist");
}

void Loader::loadAnimations()
{
	
}

void Loader::loadObjects()
{
	
}

cocos2d::SpriteFrameCache* Loader::getFrameCache()
{
	return Loader::mFrameCache;
}
