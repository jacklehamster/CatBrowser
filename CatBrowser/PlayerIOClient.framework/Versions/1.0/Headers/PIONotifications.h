//
//  PIONotifications.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/7/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

@class PIOError;

/**
 The Player.IO Notifications service.
 */
@interface PIONotifications : NSObject

/**
 The list of notification endpoints registered for the current client.
 */
@property (readonly) NSArray* myEndpoints;

/**
 Refreshes myEndpoints synchronously
 */
//- (void)refresh;

/**
 Refreshes myEndpoints asynchronously
 @param successBlock Callback block that will be called when the refresh is complete.
 */
- (void)refreshWithSuccessBlock:(void(^)())successBlock;

/**
 Refreshes myEndpoints asynchronously
 @param successBlock Callback block that will be called when the refresh is complete.
 @param errorBlock Callback block that will be called instead of successCallback if an error occurs.
 */
- (void)refreshWithSuccessBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;

/**
 Register a device or endpoint with Player.IO synchronously.
 @param endpointType Endpoint type, such as, IOS, Android, email, etc.
 @param identifier The identifier of the endpoint, such as the device token on iOS or an email address for email.
 @param configuration Configuration relating to the endpoint. Can be nil.
 @param enabled Should the endpoint be enabled.
 */
//- (void)registerEndpointWithEndpointType:(NSString*)endpointType identifier:(NSString*)identifier configuration:(NSMutableDictionary*)configuration enabled:(BOOL)enabled;

/**
 Register a device or endpoint with Player.IO synchronously.
 @param endpointType Endpoint type, such as, IOS, Android, email, etc.
 @param identifier The identifier of the endpoint, such as the device token on iOS or an email address for email.
 @param configuration Configuration relating to the endpoint. Can be nil.
 @param enabled Should the endpoint be enabled.
 @param successBlock Callback block that is invoked when operation succeeds
 */
- (void)registerEndpointWithEndpointType:(NSString*)endpointType identifier:(NSString*)identifier configuration:(NSMutableDictionary*)configuration enabled:(BOOL)enabled successBlock:(void(^)())successBlock;

/**
 Register a device or endpoint with Player.IO synchronously.
 @param endpointType Endpoint type, such as, IOS, Android, email, etc.
 @param identifier The identifier of the endpoint, such as the device token on iOS or an email address for email.
 @param configuration Configuration relating to the endpoint. Can be nil.
 @param enabled Should the endpoint be enabled.
 @param successBlock Callback block that is invoked when operation succeeds
 @param errorBlock Callback block that is invoked when operation fails
 */
- (void)registerEndpointWithEndpointType:(NSString*)endpointType identifier:(NSString*)identifier configuration:(NSMutableDictionary*)configuration enabled:(BOOL)enabled successBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;


/**
 Send one or more notifications
 @param notifications Array of notifications to send
 */
//- (void)sendNotifications:(NSMutableArray*)notifications;

/**
 Send one or more notifications
 @param notifications Array of notifications to send
 @param successBlock Callback block that is invoked when operation succeeds
 */
- (void)sendNotifications:(NSMutableArray*)notifications successBlock:(void(^)())successBlock;

/**
 Send one or more notifications
 @param notifications Array of notifications to send
 @param successBlock Callback block that is invoked when operation succeeds
 @param errorBlock Callback that is invoked when operation fails
 */
- (void)sendNotifications:(NSMutableArray*)notifications successBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;

/**
 Enables or disabled the given endpoints.
 @param endpoints The endpoints to enable or disable.
 @param enabled If true, all the given endpoints will be enabled. If false, they'll be disabled.
 */
//- (void)toggleEndpoints:(NSMutableArray*)endpoints enabled:(BOOL)enabled;

/**
 Enables or disabled the given endpoints.
 @param endpoints The endpoints to enable or disable.
 @param enabled If true, all the given endpoints will be enabled. If false, they'll be disabled.
 @param successBlock Callback block that is invoked when operation succeeds
 */
- (void)toggleEndpoints:(NSMutableArray*)endpoints enabled:(BOOL)enabled successBlock:(void(^)())successBlock;

/**
 Enables or disabled the given endpoints.
 @param endpoints The endpoints to enable or disable.
 @param enabled If true, all the given endpoints will be enabled. If false, they'll be disabled.
 @param successBlock Callback block that is invoked when operation succeeds
 @param errorBlock Callback block that is invoked when operation fails
 */
- (void)toggleEndpoints:(NSMutableArray*)endpoints enabled:(BOOL)enabled successBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;


/**
 Deletes the given endpoints
 @param endpoints The endpoints to delete.
 */
//- (void)deleteEndpoints:(NSMutableArray*)endpoints;

/**
 Deletes the given endpoints
 @param endpoints The endpoints to delete.
 @param successBlock Callback block that is invoked when operation succeeds.
 */
- (void)deleteEndpoints:(NSMutableArray*)endpoints successBlock:(void(^)())successBlock;

/**
 * Deletes the given endpoints
 * @param endpoints The endpoints to delete.
 * @param successBlock Callback block that is invoked when operation succeeds.
 * @param errorBlock Callback block that is invoked when operation fails.
 */
- (void)deleteEndpoints:(NSMutableArray*)endpoints successBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;

@end
