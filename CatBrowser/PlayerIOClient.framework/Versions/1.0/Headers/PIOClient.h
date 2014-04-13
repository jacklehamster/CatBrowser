@class PIOYahoo;
@class PIOPayVault;
@class PIOMultiplayer;
@class PIOErrorLog;
@class PIOGameFS;
@class PIOBigDB;
@class PIOAchievements;
@class PIOGameRequests;
@class PIONotifications;
@class PIOPlayerInsight;

/**
*  <p>Access class to the various services.</p>
*  <p>Here are some examples on how to work with the client:</p>
*  <pre>
*  //Connect to Player.IO
*  PIOClient* client = [PlayerIO 
*    connectWithGameId:@"[Enter your game id here]" 
*    connectionId:@"public" 
*    userId:@"user-id" 
*    auth:nil 
*    partnerId:nil
*  ];
*  
*  //Join a multiplayer room
*  PIOConnection* connection = [[client.multiplayer 
*    createJoinRoomWithRoomId:@"MyTestRoom"
*    roomType:@"bounce"
*    visible:YES 
*    roomData:testRoomData 
*    joinData:nil
*  ] retain];
*  
*  //Load an object from BigDB
*  [client.bigDB loadObjectWithKey:client.connectUserId fromTable:@"PlayerObjects" successCallback:^(PIODatabaseObject* object){
*    //...
*  }];
*
*  //Write something to the error log
*  [client.errorLog writeError:@"Something bad happened..."];
*  </pre>
*/
@interface PIOClient : NSObject


/** Get the connectuserid of this client. */
- (NSString*) connectUserId;
/** Get the showBranding of this client. */
- (BOOL)showBranding;
/** Get whether the user is a socialNetworkUser or not. */
- (BOOL)isSocialNetworkUser;
/** Access the GameFS service */
- (PIOGameFS*) gameFS;
/** Access the Errorlog service */
- (PIOErrorLog*) errorLog;
/** Access the Multiplayer service */
- (PIOMultiplayer*) multiplayer;
/** Access the PayVault service */
- (PIOPayVault*) payVault;
/** Access the BigDB service */
- (PIOBigDB*) bigDB;
/** Access the Achievement service */
- (PIOAchievements*) achievements;
/** Access the GameRequest service */
- (PIOGameRequests*) gameRequests;
/** Access the Notifications service */
- (PIONotifications*) notifications;
/** Access the PlayerInsight service */
- (PIOPlayerInsight*) playerInsight;
/** Access the yahoo service */
- (PIOYahoo*) yahoo;

@end
