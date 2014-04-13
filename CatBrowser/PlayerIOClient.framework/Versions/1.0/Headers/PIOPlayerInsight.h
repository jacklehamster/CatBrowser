//
//  PIOPlayerInsight.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/10/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

@class PIOError;

/**
 PlayerInsight
 */
@interface PIOPlayerInsight : NSObject

/**
 * The numbers of players online in the entire game
 */
@property (readonly) int playersOnline;

/**
 * Assign custom PlayerInsight segments to the current user
 * @param segments Custom segments for the user in PlayerInsight, each string should be in the form 'segmentGroup:value', like 'adcampaign:googleads'.
 */
- (void)setSegmentsWithSegments:(NSMutableArray*)segments;

/**
 * Assign custom PlayerInsight segments to the current user
 * @param segments Custom segments for the user in PlayerInsight, each string should be in the form 'segmentGroup:value', like 'adcampaign:googleads'.
 * @param successBlock Callback block that will be called when the operation succeeds
 */
- (void)setSegmentsWithSegments:(NSMutableArray*)segments successBlock:(void(^)())successBlock;

/**
 * Assign custom PlayerInsight segments to the current user
 * @param segments Custom segments for the user in PlayerInsight, each string should be in the form 'segmentGroup:value', like 'adcampaign:googleads'.
 * @param successBlock Callback block that will be called when the operation succeeds
 * @param errorBlock Callback block that will be called instead of successBlock if an error occurs during the operation.
 */
- (void)setSegmentsWithSegments:(NSMutableArray*)segments successBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;


/**
 * Gets the segment value for the given segment group. For instance, if the player is tagged in the segment 'source:facebook' the method will return 'facebook' when called with 'source' as the argument.
 * @param segmentGroup The segmentGroup to get the current segment value for.
 */
- (NSString*)getSegmentWithSegmentGroup:(NSString*)segmentGroup;

/**
 * Refresh the players online counter and the current segments of the user.
 */
- (void)refresh;

/**
 * Refresh the players online counter and the current segments of the user.
 * @param successBlock Callback block that will be called when the operation succeeds
 */
- (void)refreshWithSuccessBlock:(void(^)())successBlock;

/**
 * Refresh the players online counter and the current segments of the user.
 * @param successBlock Callback block that will be called when the operation succeeds
 * @param errorBlock Callback block that will be called instead of successBlock if an error occurs during the operation.
 */
- (void)refreshWithSuccessBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;


/**
 * Tell PlayerInsight who invited the current user in this session. Used for viral analysis.
 * @param invitingUserid The connectUserId of the user who invited this user.
 * @param invitationChannel An identifier for the channel the invitation was received over, like 'email' or 'fb_invite'.
 */
- (void)trackInvitedByWithInvitingUserId:(NSString*)invitingUserid invitationChannel:(NSString*)invitationChannel;

/**
 * Tell PlayerInsight who invited the current user in this session. Used for viral analysis.
 * @param invitingUserid The connectUserId of the user who invited this user.
 * @param invitationChannel An identifier for the channel the invitation was received over, like 'email' or 'fb_invite'.
 * @param successBlock Callback block that will be called when the operation was completed successfully
 */
- (void)trackInvitedByWithInvitingUserId:(NSString*)invitingUserid invitationChannel:(NSString*)invitationChannel successBlock:(void(^)())successBlock;

/**
 * Tell PlayerInsight who invited the current user in this session. Used for viral analysis.
 * @param invitingUserid The connectUserId of the user who invited this user.
 * @param invitationChannel An identifier for the channel the invitation was received over, like 'email' or 'fb_invite'.
 * @param successBlock Callback block that will be called when the operation was completed successfully
 * @param errorBlock Callback block that will be called instead of successBlock if an error occurs during the operation.
 */
- (void)trackInvitedByWithInvitingUserId:(NSString*)invitingUserid invitationChannel:(NSString*)invitationChannel successBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;

/**
 * Track the given event for the current user in PlayerInsight
 * @param eventType The name of the event to track.
 * @param value The amount to add to the counter value.
 */
- (void)trackEventWithEventType:(NSString*)eventType value:(int)value;

/**
 * Track the given event for the current user in PlayerInsight
 * @param eventType The name of the event to track.
 * @param value The amount to add to the counter value.
 * @param successBlock Callback block that will be called when the operation was completed successfully
 */
- (void)trackEventWithEventType:(NSString*)eventType value:(int)value successBlock:(void(^)())successBlock;

/**
 * Track the given event for the current user in PlayerInsight
 * @param eventType The name of the event to track.
 * @param value The amount to add to the counter value.
 * @param successBlock Callback block that will be called when the operation was completed successfully
 * @param errorBlock Callback block that will be called instead of successBlock if an error occurs during the operation.
 */
- (void)trackEventWithEventType:(NSString*)eventType value:(int)value successBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;

/**
 * Track a completed payment in PlayerInsight from an external non-PayVault payment method.
 * @param currency The currency the payment was made in.
 * @param amount The amount of the payment in the given currency.
 */
- (void)trackExternalPaymentWithCurrency:(NSString*)currency amount:(int)amount;

/**
 * Track a completed payment in PlayerInsight from an external non-PayVault payment method.
 * @param currency The currency the payment was made in.
 * @param amount The amount of the payment in the given currency.
 * @param successBlock Callback block that will be called when the operation was completed successfully
 */
- (void)trackExternalPaymentWithCurrency:(NSString*)currency amount:(int)amount successBlock:(void(^)())successBlock;


/**
 * Track a completed payment in PlayerInsight from an external non-PayVault payment method.
 * @param currency The currency the payment was made in.
 * @param amount The amount of the payment in the given currency.
 * @param successBlock Callback block that will be called when the operation was completed successfully
 * @param errorBlock Callback block that will be called instead of successBlock if an error occurs during the operation.
 */
- (void)trackExternalPaymentWithCurrency:(NSString*)currency amount:(int)amount successBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;


@end
