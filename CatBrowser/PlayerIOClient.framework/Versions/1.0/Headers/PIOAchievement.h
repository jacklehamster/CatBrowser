//
//  PIOAchievement.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/3/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

/**
 An Achievement
 */
@interface PIOAchievement : NSObject

/**
 * The id of the achivement
 */
@property (readonly) NSString* identifier;

/**
 * The title of the achievement
 */
@property (readonly) NSString* title;

/**
 * The description
 */
@property (readonly) NSString* description;

/**
 * An url to the image of the achievement
 */
@property (readonly) NSString* imageUrl;

/**
 * Current progress made towards the ProgressGoal of this achievement
 */
@property (readonly,assign) unsigned int progress;

/**
 * The progress value to reach to complete the achievement
 */
@property (readonly,assign) unsigned int progressGoal;

/**
 * Last updated time, in UTC */
@property (readonly) NSDate* lastUpdated;

/**
 * A value in the range [0:1] indicating the progress made towards completion.
 */
@property (readonly,nonatomic, assign) double progressRatio;

/**
 * True when Progress==ProgressGoal
 */
@property (readonly,nonatomic, assign) BOOL completed;
@end
