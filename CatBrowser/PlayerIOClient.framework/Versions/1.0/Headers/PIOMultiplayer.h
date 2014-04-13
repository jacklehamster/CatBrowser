#import "PIOServerEndpoint.h"
#import "PIOConnection.h"
#import "PIOError.h"

/**
*  The Multiplayer Service
*  <p>Here's how to create/join a room and send and receive messages:</p>
*  <pre>
*  // join a room 
*  PIOConnection* connection = [[client.multiplayer 
*    createJoinRoomWithRoomId:@"MyTestRoom"
*    roomType:@"bounce"
*    visible:YES 
*    roomData:testRoomData 
*    joinData:nil
*  ] retain];
*  
*  // listen to all messages on the connection
*  [connection addMessageCallback:^(PIOMessage *message){
*    NSLog(@"Got Message: %@", message);
*  }];
*
*  // listen to 'hello' messages on the connection
*  [connection addMessageCallback:^(PIOMessage *message) {
*    NSLog(@"Got Hello: %@", message);
*  } forType:@"hello" ];
*   
*  // add a callback for when the connection is disconnected
*  [connection addDisconnectCallback:^(void){
*    NSLog(@"Disconnect Callback");
*  }];
*    
*  // send a message to the connection
*  PIOMessage* message = [PIOMessage messageWithType:@"hello"];
*  [message addString:@"world"];
*  [connection sendMessage:message];
* </pre>
*/
@interface PIOMultiplayer : NSObject

/** If set to non-nil value, rooms will be created on the development server at the address defined by the server endpoint, instead of using the live Player.IO servers. */
- (PIOServerEndpoint*)developmentServer;
/** If set to non-nil value, rooms will be created on the development server at the address defined by the server endpoint, instead of using the live Player.IO servers. */
- (void)setDevelopmentServer:(PIOServerEndpoint*)developmentServer;

/**
* Create a multiplayer room on the Player.IO infrastructure.
* @param roomId The id you wish to assign to your new room - You can use this to connect to the specific room later as long as it still exists.
* @param roomType The name of the room type you wish to run the room as. This value should match one of the [RoomType(...)] attributes of your uploaded code. A room type of 'bounce' is always available.
* @param visible Should the room be visible when listing rooms with GetRooms or not?
* @param roomData The data to initialize the room with, this can be read with ListRooms and changed from the serverside.
* @return The id of the room that was created.
* @throws PlayerIOError 
*/
/*- (NSString*) createRoomWithRoomId:(NSString*)roomId roomType:(NSString*)roomType visible:(BOOL)visible roomData:(NSDictionary*)roomData;*/
/**
* Create a multiplayer room on the Player.IO infrastructure.
* @param roomId The id you wish to assign to your new room - You can use this to connect to the specific room later as long as it still exists.
* @param roomType The name of the room type you wish to run the room as. This value should match one of the [RoomType(...)] attributes of your uploaded code. A room type of 'bounce' is always available.
* @param visible Should the room be visible when listing rooms with GetRooms or not?
* @param roomData The data to initialize the room with, this can be read with ListRooms and changed from the serverside.
* @param successBlock A callback block that will be called with the final room id of the created room.
*/
- (void) createRoomWithRoomId:(NSString*)roomId roomType:(NSString*)roomType visible:(BOOL)visible roomData:(NSDictionary*)roomData successBlock:(void (^)(NSString* roomId))successBlock;
/**
* Create a multiplayer room on the Player.IO infrastructure.
* @param roomId The id you wish to assign to your new room - You can use this to connect to the specific room later as long as it still exists.
* @param roomType The name of the room type you wish to run the room as. This value should match one of the [RoomType(...)] attributes of your uploaded code. A room type of 'bounce' is always available.
* @param visible Should the room be visible when listing rooms with GetRooms or not?
* @param roomData The data to initialize the room with, this can be read with ListRooms and changed from the serverside.
* @param successBlock A callback block that will be called with the final room id of the created room.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) createRoomWithRoomId:(NSString*)roomId roomType:(NSString*)roomType visible:(BOOL)visible roomData:(NSDictionary*)roomData successBlock:(void (^)(NSString* roomId))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
* Join a running multiplayer room.
* @param roomId The id of the room you wish to connect to.
* @param joinData Data to send to the room with additional information about the join.
* @return A connection into the room.
* @throws PlayerIOError
*/
/*- (PIOConnection*) joinRoomWithRoomId:(NSString*)roomId joinData:(NSDictionary*)joinData;*/
/**
* Join a running multiplayer room.
* @param roomId The id of the room you wish to connect to.
* @param joinData Data to send to the room with additional information about the join.
* @param successBlock A callback block that will be called with the established connection when the room has been joined
*/
- (void) joinRoomWithRoomId:(NSString*)roomId joinData:(NSDictionary*)joinData successBlock:(void (^)(PIOConnection* connection))successBlock;
/**
* Join a running multiplayer room.
* @param roomId The id of the room you wish to connect to.
* @param joinData Data to send to the room with additional information about the join.
* @param successBlock A callback block that will be called with the established connection when the room has been joined
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) joinRoomWithRoomId:(NSString*)roomId joinData:(NSDictionary*)joinData successBlock:(void (^)(PIOConnection* connection))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
* Creates a multiplayer room (if it does not exist already) and joins it.
* @param roomId The id of the room you wish to create/join.
* @param roomType The name of the room type you wish to run the room as. This value should match one of the [RoomType(...)] attributes of your uploaded code. A room type of 'bounce' is always available.
* @param visible If the room doesn't exist: Should the room be visible when listing rooms with GetRooms upon creation?
* @param roomData If the room doesn't exist: The data to initialize the room with upon creation.
* @param joinData Data to send to the room with additional information about the join.
* @return A connection into the room that was created and joined.
* @throws PlayerIOError
*/
/*- (PIOConnection*) createJoinRoomWithRoomId:(NSString*)roomId roomType:(NSString*)roomType visible:(BOOL)visible roomData:(NSDictionary*)roomData joinData:(NSDictionary*)joinData;*/
/**
* Creates a multiplayer room (if it does not exist already) and joins it.
* @param roomId The id of the room you wish to create/join.
* @param roomType The name of the room type you wish to run the room as. This value should match one of the [RoomType(...)] attributes of your uploaded code. A room type of 'bounce' is always available.
* @param visible If the room doesn't exist: Should the room be visible when listing rooms with GetRooms upon creation?
* @param roomData If the room doesn't exist: The data to initialize the room with upon creation.
* @param joinData Data to send to the room with additional information about the join.
* @param successBlock A callback block that will be called with the established connection when the room has been joined
*/
- (void) createJoinRoomWithRoomId:(NSString*)roomId roomType:(NSString*)roomType visible:(BOOL)visible roomData:(NSDictionary*)roomData joinData:(NSDictionary*)joinData successBlock:(void (^)(PIOConnection* connection))successBlock;
/**
* Creates a multiplayer room (if it does not exist already) and joins it.
* @param roomId The id of the room you wish to create/join.
* @param roomType The name of the room type you wish to run the room as. This value should match one of the [RoomType(...)] attributes of your uploaded code. A room type of 'bounce' is always available.
* @param visible If the room doesn't exist: Should the room be visible when listing rooms with GetRooms upon creation?
* @param roomData If the room doesn't exist: The data to initialize the room with upon creation.
* @param joinData Data to send to the room with additional information about the join.
* @param successBlock A callback block that will be called with the established connection when the room has been joined
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) createJoinRoomWithRoomId:(NSString*)roomId roomType:(NSString*)roomType visible:(BOOL)visible roomData:(NSDictionary*)roomData joinData:(NSDictionary*)joinData successBlock:(void (^)(PIOConnection* connection))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;;

/**
* List the currently running multiplayer rooms.
* @param roomType The type of room you wish to list.
* @param searchCriteria Only rooms with the same values in their roomdata will be returned.
* @param resultLimit The maximum amount of rooms you want to receive. Use 0 for 'as many as possible'.
* @param resultOffset The offset into the list you wish to start listing at.
* @return A list of rooms matching the search criteria
* @throws PlayerIOError
*/
/*- (NSArray*) listRoomsWithRoomType:(NSString*)roomType searchCriteria:(NSDictionary*)searchCriteria resultLimit:(NSUInteger)resultLimit resultOffset:(NSUInteger)resultOffset;*/
/**
* List the currently running multiplayer rooms.
* @param roomType The type of room you wish to list.
* @param searchCriteria Only rooms with the same values in their roomdata will be returned.
* @param resultLimit The maximum amount of rooms you want to receive. Use 0 for 'as many as possible'.
* @param resultOffset The offset into the list you wish to start listing at.
* @param successBlock A callback block that will be called with the list of rooms found
* @throws PlayerIOError
*/
- (void) listRoomsWithRoomType:(NSString*)roomType searchCriteria:(NSDictionary*)searchCriteria resultLimit:(NSUInteger)resultLimit resultOffset:(NSUInteger)resultOffset successBlock:(void (^)(NSArray* rooms))successBlock;
/**
* List the currently running multiplayer rooms.
* @param roomType The type of room you wish to list.
* @param searchCriteria Only rooms with the same values in their roomdata will be returned.
* @param resultLimit The maximum amount of rooms you want to receive. Use 0 for 'as many as possible'.
* @param resultOffset The offset into the list you wish to start listing at.
* @param successBlock A callback block that will be called with the list of rooms found
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) listRoomsWithRoomType:(NSString*)roomType searchCriteria:(NSDictionary*)searchCriteria resultLimit:(NSUInteger)resultLimit resultOffset:(NSUInteger)resultOffset successBlock:(void (^)(NSArray* rooms))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;
@end
