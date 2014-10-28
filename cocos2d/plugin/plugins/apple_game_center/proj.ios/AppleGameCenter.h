/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>

#import "InterfaceGameServices.h"
#import "GameCenterManager.h"

#define kLeaderboardID @"com.appledts.EasyTapList"

//Achievement IDs
#define kAchievement1 @"com.appletest.one_tap"
#define kAchievement2 @"com.appledts.twenty_taps"
#define kAchievement3 @"com.appledts.one_hundred_taps"


@interface AppleGameCenter : NSObject <InterfaceGameServices>
{
    
}

@property BOOL debug;
@property (nonatomic, retain) GameCenterManager *gameCenterManager;

@property BOOL isAvailable;

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
