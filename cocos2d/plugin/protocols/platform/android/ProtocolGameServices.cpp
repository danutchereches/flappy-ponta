#include "ProtocolGameServices.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

namespace cocos2d { namespace plugin {

ProtocolGameServices::ProtocolGameServices()
{
	
}

ProtocolGameServices::~ProtocolGameServices()
{
	
}

void ProtocolGameServices::startSession()
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t, pData->jclassName.c_str(), "startSession", "()V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ProtocolGameServices::stopSession()
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t, pData->jclassName.c_str(), "stopSession", "()V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ProtocolGameServices::initiateSignIn()
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t, pData->jclassName.c_str(), "initiateSignIn", "()V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ProtocolGameServices::signOut()
{
	PluginUtils::callJavaFunctionWithName(this, "signOut");
}

void ProtocolGameServices::publishScore(int score)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t, pData->jclassName.c_str(), "publishScore", "(I)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, score);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ProtocolGameServices::showLeaderboard()
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t, pData->jclassName.c_str(), "showLeaderboard", "()V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ProtocolGameServices::unlockAchievement(int id)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t, pData->jclassName.c_str(), "unlockAchievement", "(I)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, id);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ProtocolGameServices::showAchievements()
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t, pData->jclassName.c_str(), "showAchievements", "()V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

bool ProtocolGameServices::isSignedIn()
{
	return PluginUtils::callJavaBoolFuncWithName(this, "isSignedIn");
}

}} // namespace cocos2d { namespace plugin {
