#ifndef  __CCX_PROTOCOL_GAMES_H__
#define  __CCX_PROTOCOL_GAMES_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

class ProtocolGameServices : public PluginProtocol
{
public:
	ProtocolGameServices();
	virtual ~ProtocolGameServices();
	
	void startSession();
	void stopSession();
	void initiateSignIn();
	void signOut();
	bool isSignedIn();
	void showLeaderboard();
	void showAchievements();
	void publishScore(int score);
	void unlockAchievement(int id);
	
protected:
	
};

}} // namespace cocos2d { namespace plugin {

#endif   /* ----- #ifndef __CCX_PROTOCOL_GAMES_H__ ----- */
