#include "PluginProtocol.h"


namespace cocos2d { namespace plugin {

PluginProtocol::~PluginProtocol()
{
	
}

std::string PluginProtocol::getPluginVersion()
{
	return 0;
}

std::string PluginProtocol::getSDKVersion()
{
	return 0;
}

void PluginProtocol::setDebugMode(bool isDebugMode)
{
	
}

void PluginProtocol::callFunc(const char* funcName)
{
	
}

void PluginProtocol::callFuncWithParam(const char* funcName, PluginParam* param, ...)
{
	
}

void PluginProtocol::callFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
	
}

std::string PluginProtocol::callStringFuncWithParam(const char* funcName, PluginParam* param, ...)
{
	return 0;
}

std::string PluginProtocol::callStringFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
	return 0;
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, PluginParam* param, ...)
{
	return 0;
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
	return 0;
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, PluginParam* param, ...)
{
	return false;
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
	return false;
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, PluginParam* param, ...)
{
	return 0;
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
	return 0;
}

}} //namespace cocos2d { namespace plugin {
