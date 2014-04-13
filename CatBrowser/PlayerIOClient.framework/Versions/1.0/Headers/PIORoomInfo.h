/**
 * Information about a room returned from listRooms
 */
@interface PIORoomInfo : NSObject{
    @private
    NSString* _id;
    NSString* _roomType;
    NSUInteger _onlineUsers;
    NSDictionary* _roomData;
}

/** The id of the room */
- (NSString*) id;

/** The type of the room (coresponding to the [RoomType(...)] attribute assignd to the room) */
- (NSString*) roomType;

/** How many users are currently in the room */
- (NSUInteger) onlineUsers;

/** How many users are currently in the room */
- (NSDictionary*) roomData;
@end
