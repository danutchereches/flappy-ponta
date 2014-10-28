#include "PluginFactory.h"

namespace cocos2d { namespace plugin {

PluginFactory::PluginFactory()
{

}

PluginFactory::~PluginFactory()
{

}

PluginFactory* PluginFactory::getInstance()
{
	return 0;
}

void PluginFactory::purgeFactory()
{
	
}

PluginProtocol* PluginFactory::createPlugin(const char* name)
{
	return 0;
}

}} //namespace cocos2d { namespace plugin {
