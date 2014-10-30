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
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");
	
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mfx/imn.mp3");
}

void Loader::loadTextures()
{
	mFrameCache = cocos2d::SpriteFrameCache::getInstance();
	mFrameCache->retain();
	mFrameCache->addSpriteFramesWithFile("spritesheet.plist");
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
