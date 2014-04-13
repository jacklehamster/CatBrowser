typedef enum {
    IntegerMessageEntryType = 0,
    UnsignedIntegerMessageEntryType = 1,
    LongMessageEntryType = 2,
    UnsignedLongMessageEntryType = 3,
    DoubleMessageEntryType = 4,
    FloatMessageEntryType = 5,
    StringMessageEntryType = 6,
    DataMessageEntryType = 7,
    BooleanMessageEntryType = 8
} PIOMessageEntryType;

/**
 *  <p>Represents a message sent between client and server.</p>
 *  <p>A message consists of a string type, and a payload of zero or more typed parameters.</p>
 *  <p>For example here we create a simple message that we send to the server indicating that this player is ready:</p>
 *  <pre>
 *  // message of type ready with no payload
 *  PIOMessage* m = [Message messageWithType:@"ready"];
 *  
 *  // send the message to the server
 *  [connection sendMessage:m];
 *  </pre>
 *  <p>You can also build up messages as you go, if you don't know the exact payload until runtime.</p>
 *  <p>In this example, imagine the player has multiple pieces and we send in the list of moves this player wants to do in a single turn.</p>
 *  <pre>
 *  // create a new message of type moves
 *  PIOMessage* m = [Message messageWithType:@"moves"];
 *  
 *  // add all the currently connected userids to the message
 *  for(Move* move in moves){
 *    [m addString:move.pieceId];
 *    [m addInt:move.x];
 *    [m addInt:move.y];
 *  }
 *  
 *  // send the message to the server
 *  [connection sendMessage:m];
 *  </pre>
 */
@interface PIOMessage : NSObject{
    @private
    NSString* _type;
    NSMutableArray* _objects;
    NSMutableArray* _types;
}

/** Initialize the message with the given type. */
- (id) initWithType:(NSString*)type;
/** The type of the message. */
- (NSString*) type;
/** Get the number of objects in this Message. */
- (NSUInteger) count;
/** Create a new autoreleased message with the given type */
+ (PIOMessage*) messageWithType:(NSString*)type;
/** Gets the type of object at the given index */
- (PIOMessageEntryType) typeAtIndex:(NSUInteger)index;
/** Gets the object at the given index */
- (id) objectAtIndex:(NSUInteger)index;
/** Add a string value to the end of the message */
- (void) addString:(NSString*)string;
/** Add an integer value to the end of the message */
- (void) addInt:(int32_t)string;
/** Add an integer value to the end of the message */
- (void) addInteger:(int32_t)string;
/** Add an unsigned integer value to the end of the message */
- (void) addUInt:(uint32_t)string;
/** Add an unsigned integer value to the end of the message */
- (void) addUnsignedInteger:(uint32_t)string;
/** Add a long (64bit) value to the end of the message */
- (void) addLong:(int64_t)string;
/** Add an unsigned long (64bit) value to the end of the message */
- (void) addUnsignedLong:(uint64_t)string;
/** Add an NSData object to the end of the message */
- (void) addData:(NSData*)string;
/** Add a floating point (32bit) value to the end of the message */
- (void) addFloat:(float)string;
/** Add a floating point (64bit) value to the end of the message */
- (void) addDouble:(double)string;
/** Add a boolean value to the end of the message */
- (void) addBoolean:(BOOL)string;
/** Add a boolean value to the end of the message */
- (void) addBool:(BOOL)string;
/** Get the NSString value at the given index */
- (NSString*) stringAtIndex:(NSUInteger)index;
/** Get the integer value at the given index */
- (int32_t) intAtIndex:(NSUInteger)index;
/** Get the integer value at the given index */
- (int32_t) integerAtIndex:(NSUInteger)index;
/** Get the unsigned integer value at the given index */
- (uint32_t) unsignedIntegerAtIndex:(NSUInteger)index;
/** Get the long value (64bit) at the given index */
- (int64_t) longAtIndex:(NSUInteger)index;
/** Get the unsigned long (64bit) value at the given index */
- (uint64_t) unsignedLongAtIndex:(NSUInteger)index;
/** Get the NSData value at the given index */
- (NSData*) dataAtIndex:(NSUInteger)index;
/** Get the float value at the given index */
- (float) floatAtIndex:(NSUInteger)index;
/** Get the double value at the given index */
- (double) doubleAtIndex:(NSUInteger)index;
/** Get the boolean value at the given index */
- (BOOL) booleanAtIndex:(NSUInteger)index;
/** Get the boolean value at the given index */
- (BOOL) boolAtIndex:(NSUInteger)index;
@end
