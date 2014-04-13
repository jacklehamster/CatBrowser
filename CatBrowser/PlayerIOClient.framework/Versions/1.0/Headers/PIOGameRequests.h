//
//  PIOGameRequests.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/6/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

@class PIOGameRequestSendDialogResult, PIOError;

/**
 The Player.IO GameRequests service
 */
@interface PIOGameRequests : NSObject

/**
 * The list of oldest received requests that are waiting to be processed and deleted.
 */
@property (readonly) NSArray* waitingRequests;

/**
 Send a GameRequest to the specified recipients synchronously.
 @param requestType The request type of the request to send.
 @param requestData Data that will be available to the recipient of the request with information about the request. Useful for passing any kind of data to the recipeint.
 @param recipients The recipients to send this request to.
 */
//- (void)sendWithRequestType:(NSString*)requestType requestData:(NSDictionary*)requestData recipients:(NSMutableArray*)recipients;

/**
 Send a GameRequest to the specified recipients asynchronously.
 @param requestType The request type of the request to send.
 @param requestData Data that will be available to the recipient of the request with information about the request. Useful for passing any kind of data to the recipeint.
 @param recipients The recipients to send this request to.
 @param successBlock Callback block that will be called when the operation succeeds.
 */
- (void)sendWithRequestType:(NSString*)requestType requestData:(NSDictionary*)requestData recipients:(NSMutableArray*)recipients successBlock:(void(^)())successBlock;

/**
 Send a GameRequest to the specified recipients asynchronously.
 @param requestType The request type of the request to send.
 @param requestData Data that will be available to the recipient of the request with information about the request. Useful for passing any kind of data to the recipeint.
 @param recipients The recipients to send this request to.
 @param successBlock Callback block that will be called when the operation succeeds.
 @param errorBlock Callback that will be called instead of successBlock if an error occurs during the operation.
 */
- (void)sendWithRequestType:(NSString*)requestType requestData:(NSDictionary*)requestData recipients:(NSMutableArray*)recipients successBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;

/**
 Show a dialogue to send GameRequests
 @param requestType The request type of the request to send.
 @param requestData Data that will be available to the recipient of the request with information about the request. Useful for passing any kind of data to the recipeint.
 @param closeBlock Callback block that will be called when the dialog close, with information about the requests sent. NOTE: There is no way to tell if the end-user copied a link and sent it to another player.
 */
- (void)showSendDialogWithRequestType:(NSString*)requestType requestData:(NSDictionary*)requestData closeBlock:(void(^)(PIOGameRequestSendDialogResult*))closeBlock;

/**
 Refresh the list of received requests synchronously.
 */
//- (void)refresh;

/**
 Refresh the list of received requests asynchronously.
 @param successBlock Callback block that will be called when the operation succeeds.
 */
- (void)refreshWithSuccessBlock:(void(^)())successBlock;

/**
 Refresh the list of received requests asynchronously.
 @param successBlock Callback block that will be called when the operation succeeds.
 @param errorBlock Callback block that will be called instead of successBlock if an error occurs during the operation.
 */
- (void)refreshWithSuccessBlock:(void(^)())successBlock errorBlock:(void (^)(PIOError *))errorBlock;

/**
 Delete the given requests synchronously. Will also update the Received property after deletion is complete.
 @param requests The array of GameRequests to delete.
 */
//- (void)deleteWithGameRequests:(NSMutableArray*)requests;

/**
 * Delete the given requests asynchronously. Will also update the Received property after deletion is complete.
 @param requests The array of GameRequests to delete.
 @param successBlock Callback block that will be called when the operation succeeds.
 */
- (void)deleteWithGameRequests:(NSMutableArray*)requests successBlock:(void(^)())successBlock;

/**
 Delete the given requests asynchronously. Will also update the Received property after deletion is complete.
 @param requests The array of PIOGameRequests to delete.
 @param successBlock Callback block that will be called when the operation succeeds.
 @param errorBlock block that will be called instead of successBlock if an error occurs during the operation.
 */
- (void)deleteWithGameRequests:(NSMutableArray*)requests successBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError *))errorBlock;

@end
