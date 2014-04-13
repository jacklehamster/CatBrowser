//
//  PIOGameRequest.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/6/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 A received game request.
 */
@interface PIOGameRequest : NSObject
/**
 * The request type of the request
 */
@property (readonly) NSString* type;

/**
 * The user id of the user that sent the request
 */
@property (readonly) NSString* sendUserId;

/**
 * When the request was received
 */
@property (readonly) NSDate* created;

/**
 * The game-specific extra data associated with this request
 */
@property (readonly) NSDictionary* data;
@end
