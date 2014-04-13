//
//  PIONotification.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/7/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

/**
 A Notification.
 */
@interface PIONotification : NSObject

/**
 * The intended recipient (userId) of this notification
 */
@property (readonly) NSString* recipientUserId;

/**
 * The type of notification endpoint that will receive this notification
 */
@property (readonly) NSString* endpointType;

/**
 * The notification data
 */
@property (readonly) NSDictionary* data;

/**
 * Create a new notification intended for the specified recipient if he/she has registered a notification endpoint of the given type.
 * @param recipientUserId The intended recipient userId of this notification.
 * @param endpointType The endpoint type that this notification is intended for.
 */
- (id)initWithRecipientUserId:(NSString*)recipientUserId endpointType:(NSString*)endpointType;

/**
 * Add a specific argument to the Data of this notification
 * @param key The key to add
 * @param value The value to add
 * @return This instance after modifications made by set
 */
- (PIONotification*)setWithKey:(NSString*)key value:(NSString*)value;

@end
