#import <Foundation/Foundation.h>
#import "PIOClient.h"
#import "PIOError.h"
#import "PIORegistrationError.h"
#import "PIOErrorCodes.h"
#import "PIOGameFS.h"
#import "PIOMessage.h"
#import "PIOMultiplayer.h"
#import "PIOServerEndpoint.h"
#import "PIORoomInfo.h"
#import "PIODatabaseObject.h"
#import "PIODatabaseArray.h"
#import "PIOBigDB.h"
#import "PIOPayVault.h"
#import "PIOPayVaultHistoryEntry.h"
#import "PIOBuyItemInfo.h"
#import "PIOVaultItem.h"
#import "PIOAchievement.h"
#import "PIOGameRequest.h"
#import "PIONotificationEndpoint.h"
#import "PIONotification.h"

/**
 * <p>Entry class for the initial connection to Player.IO.</p>
 * <p>Here is an example of using the class to authenticate to Player.IO:</p>
 * <pre>
 * //Connect to Player.IO
 * PIOClient* client = [PlayerIO 
 *   authenticateWithGameId:@"[Enter your game id here]"
 *   connectionId:@"public" 
 *   authenticationArguments:[NSMutableDictionary dictionaryWithObjectsAndKeys:@"someUserId", @"userId", nil]
 *   playerInsightSegments:nil
 * ];
 * </pre>
 */
@interface PlayerIO : NSObject

/**
 * Get access to GameFS for a specific game, without connecting to the game.
 * @param gameId the gameid of the game to connect to
 * @return An instance of PIOGameFS.
 */
+ (PIOGameFS*)gameFSWithGameId:(NSString*)gameId;

/**
 * Calculate an auth hash for use in the connect method.
 * @param userId The userid to use when generating the hash
 * @param sharedSecret The shared secret to use when generating the hash. This must be the same value as the one given to a connection in the admin panel.
 * @return The generated auth hash.
 */
+ (NSString *)calcAuthWithUserId:(NSString *)userId sharedSecret:(NSString *)sharedSecret;

/**
 * Connects to Player.IO using as the given user
 * @param gameId The game id of the game you wish to connect to. This value can be found in the admin panel
 * @param connectionId The id of the connection, as given in the settings section of the admin panel. 'public' should be used as the default
 * @param authenticationArguments A dictionary of arguments for the given connection.
 * @param playerInsightSegments Custom segments for the user in PlayerInsight.
 */
/*+(PIOClient*)authenticateWithGameId:(NSString *)gameId
                       connectionId:(NSString *)connectionId
            authenticationArguments:(NSMutableDictionary *)authenticationArguments
              playerInsightSegments:(NSMutableArray *)playerInsightSegments;*/

/**
 * Connects to Player.IO using as the given user
 * @param gameId The game id of the game you wish to connect to. This value can be found in the admin panel
 * @param connectionId The id of the connection, as given in the settings section of the admin panel. 'public' should be used as the default
 * @param authenticationArguments A dictionary of arguments for the given connection.
 * @param playerInsightSegments Custom segments for the user in PlayerInsight.
 * @param successBlock Callback block with the client object when connected
 */
+(void)authenticateWithGameId:(NSString *)gameId
                 connectionId:(NSString *)connectionId
      authenticationArguments:(NSMutableDictionary *)authenticationArguments
        playerInsightSegments:(NSMutableArray *)playerInsightSegments
                 successBlock:(void (^)(PIOClient*))successBlock;

/**
 * Connects to Player.IO using as the given user
 * @param gameId The game id of the game you wish to connect to. This value can be found in the admin panel
 * @param connectionId The id of the connection, as given in the settings section of the admin panel. 'public' should be used as the default
 * @param authenticationArguments A dictionary of arguments for the given connection.
 * @param playerInsightSegments Custom segments for the user in PlayerInsight.
 * @param successBlock Callback block with the client object when connected
 * @param errorBlock Callback block that will be called instead of successCallback if an error occurs during the connect.
 */
+(void)authenticateWithGameId:(NSString *)gameId
                 connectionId:(NSString *)connectionId
      authenticationArguments:(NSMutableDictionary *)authenticationArguments
        playerInsightSegments:(NSMutableArray *)playerInsightSegments
                 successBlock:(void (^)(PIOClient*))successBlock
                   errorBlock:(void (^)(PIOError* error))errorBlock;

/**
 * Shut down the client and remove all stored credentials.
 */
+ (void)logout;


/**
 * Place the code below at the beginning of your "application:didFinishLaunchingWithOptions:" method to handle PlayLinks
 *if ([launchOptions objectForKey:UIApplicationLaunchOptionsURLKey]){
 * [PlayerIO handlePlayLinkWithURL:[launchOptions objectForKey:UIApplicationLaunchOptionsURLKey]];
 *}
 * @param url The URL passed in as part of the application:didFinishLaunchingWithOptions: invocation
 */
+ (BOOL)handlePlayLinkWithURL:(NSURL*)url;

@end
