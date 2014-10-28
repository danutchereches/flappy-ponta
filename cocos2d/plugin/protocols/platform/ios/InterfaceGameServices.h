#import <Foundation/Foundation.h>

@protocol InterfaceGameServices <NSObject>

- (void) startSession;
- (void) stopSession;
- (void) initiateSignIn;
- (void) signOut;
- (BOOL) isSignedIn;
- (void) showLeaderboard;
- (void) showAchievements;
- (void) publishScore: (int) score;
- (void) unlockAchievement: (int) achievementId;

- (void) setDebugMode: (BOOL) isDebugMode;
- (NSString*) getSDKVersion;
- (NSString*) getPluginVersion;

@end
