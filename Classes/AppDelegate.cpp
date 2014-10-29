#include <algorithm>

#include "AppDelegate.h"

USING_NS_CC;

const int AppDelegate::BASE_WIDTH = 120;
const int AppDelegate::BASE_HEIGHT = 160;
const float AppDelegate::SCALE_L_RES = 3.0;   //scale 0.250000
const float AppDelegate::SCALE_M_RES = 4.0;   //scale 0.333333
const float AppDelegate::SCALE_H_RES = 6.0;   //scale 0.500000
const float AppDelegate::SCALE_XH_RES = 8.0;  //scale 0.666666
const float AppDelegate::SCALE_XXH_RES = 12.0;//scale 1.000000

cocos2d::plugin::ProtocolAnalytics* AppDelegate::pluginAnalytics = nullptr;
cocos2d::plugin::ProtocolGameServices* AppDelegate::pluginGameServices = nullptr;

AppDelegate::AppDelegate()
{
	
}

AppDelegate::~AppDelegate()
{
	
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview)
	{
		glview = GLView::createWithRect("Flappy Ponta", cocos2d::Rect(0, 0, 480, 640), 1);
		director->setOpenGLView(glview);
	}
	
	glview->setDesignResolutionSize(AppDelegate::BASE_WIDTH, AppDelegate::BASE_HEIGHT, ResolutionPolicy::NO_BORDER);
	cocos2d::Size frameSize = glview->getFrameSize();
	
	cocos2d::log("frame size %f, %f", frameSize.width, frameSize.height);
	
	std::vector<std::string> searchPath;
	if (frameSize.height >= 1920) {
		this->resolutionScale = AppDelegate::SCALE_XXH_RES;
		searchPath.push_back("gfx/xxh_res");
	} else if (frameSize.height >= 1280) {
		this->resolutionScale = AppDelegate::SCALE_XH_RES;
		searchPath.push_back("gfx/xh_res");
	} else if (frameSize.height >= 960) {
		this->resolutionScale = AppDelegate::SCALE_H_RES;
		searchPath.push_back("gfx/h_res");
	} else if (frameSize.height >= 640) {
		this->resolutionScale = AppDelegate::SCALE_M_RES;
		searchPath.push_back("gfx/m_res");
	} else {
		this->resolutionScale = AppDelegate::SCALE_L_RES;
		searchPath.push_back("gfx/l_res");
	}
	searchPath.push_back("gfx/all_res");
	searchPath.push_back("sfx");
	
	FileUtils::getInstance()->setSearchPaths(searchPath);
	
	cocos2d::log("resolution scale %f, %f", resolutionScale, (AppDelegate::BASE_WIDTH * this->resolutionScale) / AppDelegate::BASE_WIDTH);
	
	director->setContentScaleFactor(this->resolutionScale);
	
	// turn on display FPS
	director->setDisplayStats(true);
	
	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);
	
	pluginAnalytics = dynamic_cast<cocos2d::plugin::ProtocolAnalytics*>
			(cocos2d::plugin::PluginManager::getInstance()->loadPlugin("GoogleAnalytics"));
	pluginAnalytics->setDebugMode(true);
	pluginAnalytics->startSession("UA-55456421-4");
	pluginAnalytics->setCaptureUncaughtException(true);
	pluginAnalytics->setSessionContinueMillis(300);
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	const char *pluginName = "AppleGameCenter";
#else
	const char *pluginName = "GpsGames";
#endif
	pluginGameServices = dynamic_cast<cocos2d::plugin::ProtocolGameServices*>
			(cocos2d::plugin::PluginManager::getInstance()->loadPlugin(pluginName));
	pluginGameServices->setDebugMode(true);
	pluginGameServices->startSession();
	
	auto scene = LoadingScene::create();
	director->runWithScene(scene);
	
	return true;
}

void AppDelegate::unloadPlugins()
{
	if (pluginAnalytics != nullptr)
	{
		pluginAnalytics->stopSession();
		cocos2d::plugin::PluginManager::getInstance()->unloadPlugin(pluginAnalytics->getPluginName());
		pluginAnalytics = nullptr;
	}
	
	if (pluginGameServices != nullptr)
	{
		pluginGameServices->stopSession();
		cocos2d::plugin::PluginManager::getInstance()->unloadPlugin(pluginGameServices->getPluginName());
		pluginGameServices = nullptr;
	}
}

void AppDelegate::closeApp()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	
	AppDelegate::unloadPlugins();
	Director::getInstance()->end();
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	
	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	
	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <android/log.h>
#include <string>
#include "platform/android/jni/JniHelper.h"
#include "CCFileUtilsAndroid.h"
#include "android/asset_manager_jni.h"
#include "deprecated/CCString.h"

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeCloseApp(JNIEnv*  env, jobject thiz) {
		AppDelegate::closeApp();
	}
}
#endif
