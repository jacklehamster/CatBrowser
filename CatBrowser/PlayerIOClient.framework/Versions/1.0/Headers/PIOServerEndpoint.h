/**
 * <p>The address and port where a game server can be reached</p>
 */
@interface PIOServerEndpoint : NSObject{
    @private
    NSString* _address;
    NSUInteger _port;
}


/**
 * The address and port where a game server can be reached
 */
- (NSUInteger) port;
/** 
 * The port of the server. 
 */
- (NSString*) address;

/**
 * Initialize the new ServerEndpoint
 * @param address The address/hostname of the server.
 * @param port The port of the server.
 */
- (id) initWithAddress:(NSString*)address port:(NSUInteger)port;

/**
 * Create a new autoreleased ServerEndpoint
 * @param address The address/hostname of the server.
 * @param port The port of the server.
 */
+ (id) endpointWithAddress:(NSString*)address port:(NSUInteger)port;
@end
