//
//  PIOYahoo.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/6/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

#import "PIOYahooProfiles.h"

@class PIOYahooRelations, PIOYahooPayments, PIOError;

/**
 The Yahoo Service.
 */
@interface PIOYahoo : NSObject

/**
 * Access to Yahoo profiles
 */
@property (readonly) PIOYahooProfiles* profiles;

/**
 * Access to Yahoo payments
 */
@property (readonly) PIOYahooPayments* payments;

/**
 * Access to Yahoo relations
 */
@property (readonly) PIOYahooRelations* relations;

/**
 * Refresh Profiles and Relations.
 */
- (void)refresh;

/**
 * Refresh Profiles and Relations.
 * @param successBlock Callback block that will be called when the refresh is complete.
 */
- (void)refreshWithSuccessBlock:(void(^)())successBlock;

/**
 * Refresh Profiles and Relations.
 * @param successBlock Callback block that will be called when the refresh is complete.
 * @param errorBlock Callback block that will be called if the refresh fails.
 */
- (void)refreshWithSuccessBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;
                                                           
@end
