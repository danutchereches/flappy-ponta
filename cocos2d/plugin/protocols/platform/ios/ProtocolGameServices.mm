#include "ProtocolGameServices.h"
#include "InterfaceGameServices.h"
#include "PluginUtilsIOS.h"

namespace cocos2d { namespace plugin {

ProtocolGameServices::ProtocolGameServices()
{
	
}

ProtocolGameServices::~ProtocolGameServices()
{
	PluginUtilsIOS::erasePluginOCData(this);
}

void ProtocolGameServices::startSession()
{
	PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
	assert(pData != NULL);
	
	id ocObj = pData->obj;
	if ([ocObj conformsToProtocol:@protocol(InterfaceGameServices)]) {
		NSObject<InterfaceGameServices>* curObj = ocObj;
		[curObj startSession];
	}
}

void ProtocolGameServices::stopSession()
{
	PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
	assert(pData != NULL);
	
	id ocObj = pData->obj;
	if ([ocObj conformsToProtocol:@protocol(InterfaceGameServices)]) {
		NSObject<InterfaceGameServices>* curObj = ocObj;
		[curObj stopSession];
	}
}

void ProtocolGameServices::initiateSignIn()
{
	PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
	assert(pData != NULL);
	
	id ocObj = pData->obj;
	if ([ocObj conformsToProtocol:@protocol(InterfaceGameServices)]) {
		NSObject<InterfaceGameServices>* curObj = ocObj;
		[curObj initiateSignIn];
	}
}

void ProtocolGameServices::signOut()
{
	PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
	assert(pData != NULL);
	
	id ocObj = pData->obj;
	if ([ocObj conformsToProtocol:@protocol(InterfaceGameServices)]) {
		NSObject<InterfaceGameServices>* curObj = ocObj;
		[curObj signOut];
	}
}

void ProtocolGameServices::publishScore(int score)
{
	PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
	assert(pData != NULL);
	
	id ocObj = pData->obj;
	if ([ocObj conformsToProtocol:@protocol(InterfaceGameServices)]) {
		NSObject<InterfaceGameServices>* curObj = ocObj;
		[curObj publishScore:score];
	}
}

void ProtocolGameServices::showLeaderboard()
{
	PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
	assert(pData != NULL);
	
	id ocObj = pData->obj;
	if ([ocObj conformsToProtocol:@protocol(InterfaceGameServices)]) {
		NSObject<InterfaceGameServices>* curObj = ocObj;
		[curObj showLeaderboard];
	}
}

void ProtocolGameServices::unlockAchievement(int achievementId)
{
	PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
	assert(pData != NULL);
	
	id ocObj = pData->obj;
	if ([ocObj conformsToProtocol:@protocol(InterfaceGameServices)]) {
		NSObject<InterfaceGameServices>* curObj = ocObj;
		[curObj unlockAchievement:achievementId];
	}
}

void ProtocolGameServices::showAchievements()
{
	PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
	assert(pData != NULL);
	
	id ocObj = pData->obj;
	if ([ocObj conformsToProtocol:@protocol(InterfaceGameServices)]) {
		NSObject<InterfaceGameServices>* curObj = ocObj;
		[curObj showAchievements];
	}
}

bool ProtocolGameServices::isSignedIn()
{
	PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
	assert(pData != NULL);
	
	id ocObj = pData->obj;
	if ([ocObj conformsToProtocol:@protocol(InterfaceGameServices)]) {
		NSObject<InterfaceGameServices>* curObj = ocObj;
		return [curObj isSignedIn];
	}
	
	return false;
}

}} // namespace cocos2d { namespace plugin {
