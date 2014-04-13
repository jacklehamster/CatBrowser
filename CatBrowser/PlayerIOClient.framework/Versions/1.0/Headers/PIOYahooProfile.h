//
//  PIOYahooProfile.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/13/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

/**
 A Yahoo Profile
 */
@interface PIOYahooProfile : NSObject

/**
 * The userId of the user
 */
@property (readonly) NSString* userId;

/**
 * The displayname of the user
 */
@property (readonly) NSString* displayName;

/**
 * The url to the avatar of the user
 */
@property (readonly) NSString* avatarUrl;

/**
 * When was this user last seen
 */
@property (readonly) NSDate* lastOnline;

/**
 * The country code of the user
 */
@property (readonly) NSString* countryCode;

@end
