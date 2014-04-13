#import "PIOMessage.h"
#import "PIOError.h"

@class MessageSerializer;

/**
*  A connetion to a multiplayer room.
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
@interface PIOConnection : NSObject{
    @private
    void (^_resultBlock)(PIOError* error);
    NSMutableArray*         _heldMessages;
    NSMutableDictionary*    _messageCallbacks;
    NSMutableArray*         _disconnectCallbacks;
    MessageSerializer*      _serializer;
    BOOL                    _connected;
    NSInputStream*          _input;
    NSOutputStream*         _output;
    NSMutableData*          _messageBuffer;
    NSUInteger              _messageBufferIndex;
    NSUInteger              _messageBufferBytesWaiting;
    void*                   _readBuffer;
    NSUInteger              _readBufferLength;
}

/** Is the connection currently connected to a remote host? */
- (BOOL) isConnected;
/**
 * Add a message listener to this connection. The callback will be called on every message received by the connection.
 * @param callback The listener to add.
 */
- (void) addMessageCallback:(void (^)(PIOMessage* message))callback;
/**
 * Add a message listener for a specific message type to this connection.
 * @param callback The listener to add.
 * @param type the specific type to limit the listener to
 */
- (void) addMessageCallback:(void (^)(PIOMessage* message))callback forType:(NSString*)type;
/**
 * Add a disconnect listener to this connection.
 * @param callback The listener to add.
 */
- (void) addDisconnectCallback:(void (^)(void))callback;
/**
* Send a message to the room.
* @param message The message to send
*/
- (void) sendMessage:(PIOMessage*)message;
/** Disconnect from the game room */
- (void) disconnect;
@end
