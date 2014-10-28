#include "Helpers.h"

void Vibrator::vibrate(int time)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "vibrate", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, time);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
#endif
}
void Vibrator::cancelVibrate()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "cancelVibrate", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void URL::open(char* url)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openUrl", "(Ljava/lang/String;)V"))
	{
		jstring arg1 = t.env->NewStringUTF(url);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, arg1);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(arg1);
	}
#endif
}

void Dialog::getImage()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "imageDialog", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void Dialog::getCamera()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "cameraDialog", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void Dialog::getMusic()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "soundDialog", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}
