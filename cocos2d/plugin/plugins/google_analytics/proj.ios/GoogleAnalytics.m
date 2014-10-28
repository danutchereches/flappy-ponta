#import "GoogleAnalytics.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation GoogleAnalytics

@synthesize debug = __debug;

- (void) startSession: (NSString*) appKey
{
    
}

- (void) stopSession
{
    OUTPUT_LOG(@"GoogleAnalytics stopSession in GoogleAnalytics not available on iOS");
}

- (void) setSessionContinueMillis: (long) millis
{
    OUTPUT_LOG(@"GoogleAnalytics setSessionContinueMillis invoked(%ld)", millis);
    int seconds = (int)(millis / 1000);
    
}

- (void) setCaptureUncaughtException: (BOOL) isEnabled
{
    OUTPUT_LOG(@"GoogleAnalytics setCaptureUncaughtException in GoogleAnalytics not available on iOS");
}

- (void) setDebugMode: (BOOL) isDebugMode
{
    OUTPUT_LOG(@"GoogleAnalytics setDebugMode invoked(%d)", isDebugMode);
    self.debug = isDebugMode;
    
}

- (void) logError: (NSString*) errorId withMsg:(NSString*) message
{
    OUTPUT_LOG(@"GoogleAnalytics logError invoked(%@, %@)", errorId, message);	
    
}

- (void) logEvent: (NSString*) eventId
{
    OUTPUT_LOG(@"GoogleAnalytics logEvent invoked(%@)", eventId);
    
}

- (void) logEvent: (NSString*) eventId withParam:(NSMutableDictionary*) paramMap
{
    OUTPUT_LOG(@"GoogleAnalytics logEventWithParams invoked (%@, %@)", eventId, [paramMap debugDescription]);
    
}

- (void) logTimedEventBegin: (NSString*) eventId
{
    OUTPUT_LOG(@"GoogleAnalytics logTimedEventBegin invoked (%@)", eventId);
    
}

- (void) logTimedEventEnd: (NSString*) eventId
{
    OUTPUT_LOG(@"GoogleAnalytics logTimedEventEnd invoked (%@)", eventId);
    
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
