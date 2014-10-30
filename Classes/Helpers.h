#ifndef __HELPERS_H__
#define __HELPERS_H__

#include "cocos2d.h"

namespace helpers {

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

}; // namespace helpers {
#endif // __HELPERS_H__
