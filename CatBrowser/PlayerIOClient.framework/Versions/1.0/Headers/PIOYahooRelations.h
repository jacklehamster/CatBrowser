//
//  YahooRelations.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/6/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

/**
 The YahooRelations Service.
 */
@interface PIOYahooRelations : NSObject

/**
 * List of all friends
 */
@property (readonly) NSArray* friends;

/**
 * Check if a specific user is a friend
 * @param userId The userId of the user to check.
 */
- (BOOL)isFriendWithUserId:(NSString*)userId;

/**
 *  Check if a specific user is blocked
 * @param userId The userId of the user to check.
 */
- (BOOL)isBlockedWithUserId:(NSString*)userId;

/**
 * Shows a dialog where the user can choose to send a friend request to the specified user.
 * @param userId The userId of the user that will receive the friendship request, if sent
 * @param closedBlock Callback block that will be called when the dialog is closed
 */
- (void)showRequestFriendshipDialogWithUserId:(NSString*)userId closedBlock:(void(^)())closedBlock;

/**
 * Shows a dialog where the user can choose to block a specific user.
 * @param userId The userId of the user to block
 * @param closedBlock Callback block that will be called when the dialog is closed
 */
- (void)showRequestBlockUserDialogWithUserId:(NSString*)userId closedBlock:(void(^)())closedBlock;

/**
 * Shows the a dialog where the user can manage their friends list.
 * @param closedBlock Callback block that will be called when the dialog closes
 */
- (void)showFriendsManagerWithClosedBlock:(void(^)())closedBlock;


/**
 * Shows the a dialog where the user can manage their blocked users list.
 * @param closedBlock Callback that will be called when the dialog closes
 */
- (void)showBlockedUserManagerWithClosedBlock:(void(^)())closedBlock;
@end
