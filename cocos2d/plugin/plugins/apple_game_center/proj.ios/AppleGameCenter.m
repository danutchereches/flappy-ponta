#include "AppleGameCenter.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation AppleGameCenter

@synthesize debug = __debug;
@synthesize isAvailable;

@synthesize gameCenterManager;

- (void) showAlertWithTitle: (NSString*) title message: (NSString*) message
{
	UIAlertView* alert= [[UIAlertView alloc] initWithTitle: title message: message 
							delegate: NULL cancelButtonTitle: @"OK" otherButtonTitles: NULL];
	[alert show];
}

- (void) startSession
{
    OUTPUT_LOG(@"start ses");
	
	if([GameCenterManager isGameCenterAvailable])
	{
		self.gameCenterManager= [[GameCenterManager alloc] init];
		[self.gameCenterManager setDelegate: self];
		[self.gameCenterManager authenticateLocalUser];
		
		self.isAvailable = true;
	}
	else
	{
		[self showAlertWithTitle: @"Game Center Support Required!"
						 message: @"The current device does not support Game Center, which this sample requires."];
		
		self.isAvailable = false;
	}
}

- (void) stopSession
{
	OUTPUT_LOG(@"stop ses");
}

- (void) initiateSignIn
{
	OUTPUT_LOG(@"init sign in");
}

- (void) signOut
{
	OUTPUT_LOG(@"sign out");
}

- (BOOL) isSignedIn
{
	OUTPUT_LOG(@"is sign");
	
	return self.isAvailable;
}

- (void) showLeaderboard
{
	OUTPUT_LOG(@"show lead");
}

- (void) showAchievements
{
	OUTPUT_LOG(@"show ach");
}

- (void) publishScore:(int) score
{
	OUTPUT_LOG(@"publish scor");
}

- (void) unlockAchievement:(int) achievementId
{
	OUTPUT_LOG(@"unlock ach");
	
	NSString* identifier= NULL;
	switch (achievementId)
	{
		case 1:
			identifier= kAchievement1;
			break;
		case 2:
			identifier= kAchievement2;
			break;
		case 3:
			identifier= kAchievement3;
			break;
	}
	
	[self.gameCenterManager submitAchievement: identifier percentComplete: 100];
}

- (void) setDebugMode: (BOOL) isDebugMode
{
	OUTPUT_LOG(@"Flurry setDebugMode invoked(%d)", isDebugMode);
	self.debug = isDebugMode;
}

- (NSString*) getSDKVersion
{
	return @"0.0.0";
}

- (NSString*) getPluginVersion
{
	return @"0.0.0";
}

@end
