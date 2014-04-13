//
//  PIONotificationEndpoint.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/7/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

/**
 Notifications Endpoint
 */
@interface PIONotificationEndpoint : NSObject

/**
 * The type of the endpoint
 */
@property (readonly) NSString* type;

/**
 * The endpoint identifier (e.g, push device id or e-mail address...)
 */
@property (readonly) NSString* identifier;

/**
 * The configuration of the endpoint
 */
@property (readonly) NSDictionary* configuration;

/**
 * Is this endpoint currently enabled?
 */
@property (readonly) BOOL enabled;

@end
