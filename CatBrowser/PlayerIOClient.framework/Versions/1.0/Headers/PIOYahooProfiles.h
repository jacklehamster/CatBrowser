//
//  YahooProfiles.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/6/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

@class PIOYahoo;
@class PIOYahooProfile;
@class PIOError;

/**
 The YahooProfile Service.
 */
@interface PIOYahooProfiles : NSObject


/**
 * The profile of the current user
 */
@property (readonly) PIOYahooProfile* myProfile;


/**
 * Show the profile for the specified user
 * @param userId The userId of the user
 * @param closedBlock Callback block that will be called when the profile page is closed
 */
- (void)showProfileWithUserId:(NSString*)userId closedBlock:(void(^)())closedBlock;

/**
 * Load a set of Yahoo profiles synchronously
 * @param userIds The userIds of the profiles to load.
 * @return The loaded profiles
 */
//- (NSArray*)loadProfilesWithUserIds:(NSMutableArray*)userIds;

/**
 * Load a set of Yahoo profiles asynchronously
 * @param userIds The userIds of the profiles to load.
 * @param successBlock Callback block that will be called with the loaded profiles.
 */
- (void)loadProfilesWithUserIds:(NSMutableArray*)userIds successBlock:(void(^)(NSArray*))successBlock;

/**
 * Load a set of Yahoo profiles asynchronously
 * @param userIds The userIds of the profiles to load.
 * @param successBlock Callback block that will be called with the loaded profiles.
 * @param errorBlock Callback block that will be called if the load fails.
 */
- (void)loadProfilesWithUserIds:(NSMutableArray*)userIds successBlock:(void(^)(NSArray*))successBlock errorBlock:(void(^)(PIOError*))errorBlock;

@end
