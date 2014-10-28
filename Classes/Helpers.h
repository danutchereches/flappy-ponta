#ifndef __HELPERS_H__
#define __HELPERS_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <AudioToolbox/AudioServices.h>
#endif

#define CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

class Vibrator
{
public:
	static void vibrate(int time);
	static void cancelVibrate();
};

class URL
{
public:
	static void open(char* url);
};

class Dialog
{
public:
	static void getImage();
	static void getCamera();
	static void getMusic();
};

#endif // __HELPERS_H__
