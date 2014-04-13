//
//  PIOAchievements.h
//  PlayerIOClient
//
//  Created by Arash Rassouli on 2/3/14.
//  Copyright (c) 2014 PlayerScale. All rights reserved.
//

@class PIOError;
@class PIOAchievement;

typedef void (^OnComplete)(PIOAchievement*);

/**
 The Player.IO Achievements service
 */
@interface PIOAchievements : NSObject


/**
 The list of all achievements; the values of Progress and ProgressGoal will indicate whether the achievement is started/pending/complete.
 */
@property (readonly, retain) NSArray* myAchievements;

/**
 Callback block called whenever an achievement is completed by a call to progressXXX.
 */
@property (readwrite, copy) OnComplete onComplete;

/**
 This method gets the specified achievement.
 @param achievementId The id of the achievement to get
 @return The achievement, if found, otherwise nil
 */
- (PIOAchievement*)getWithAchievementId:(NSString*)achievementId;

/**
 * Refreshes myAchievements synchronously
 */
//- (void)refresh;

/**
  Refreshes myAchievements asynchronously.
  @param successBlock Callback block that will be called when the refresh is complete.
 */
- (void)refreshWithSuccessBlock:(void(^)())successBlock;

/**
 Refreshes myAchievements asynchronously.
 @param successBlock Callback block that will be called when the refresh is complete.
 @param errorBlock Callback block that will be called instead of successBlock if an error occurs
 */
- (void)refreshWithSuccessBlock:(void(^)())successBlock errorBlock:(void(^)(PIOError*))errorBlock;


/**
 Load achievements for the specified users.
 @param userIds Array of userIds to load achievements for.
 @return A dictionary where the keys are userIds and the values are their achievements
 */
//- (NSDictionary*)loadWithUserIds:(NSMutableArray*)userIds;

/**
 Load achievements for the specified users asynchronously.
 @param userIds Array of userIds to load achievements for.
 @param successBlock Callback block that will be called with a dictionary where the keys are userIds and the values are their achievements.
 */
- (void)loadWithuserIds:(NSMutableArray*)userIds successBlock:(void(^)(NSDictionary*))successBlock;

/**
 Load achievements for the specified users asynchronously.
 @param userIds Array of userIds to load achievements for.
 @param successBlock Callback block that will be called with a dictionary where the keys are userIds and the values are their achievements.
 @param errorBlock Callback block that will be called instead of successBlock if an error occurs.
 */
- (void)loadWithuserIds:(NSMutableArray*)userIds successBlock:(void(^)(NSDictionary*))successBlock errorBlock:(void(^)(PIOError*))errorBlock;

/**
 Sets the progress of the specified achievement synchronously.
 @param achievementId The id of the achivement to add progress to.
 @param progress The new progress value for the achievement.
 @return The updated achievement
 */
//- (PIOAchievement*)progressSetWithAchievementId:(NSString*)achievementId progress:(int)progress;

/**
 Sets the progress of the specified achievement asynchronously.
 @param achievementId The id of the achivement to add progress to.
 @param progress The new progress value for the achievement.
 @param successBlock Callback block that will be called with the updated Achievement.
 */
- (void)progressSetWithAchievementId:(NSString*)achievementId progress:(int)progress successBlock:(void(^)(PIOAchievement*))successBlock;

/**
 Sets the progress of the specified achievement asynchronously.
 @param achievementId The id of the achivement to add progress to.
 @param progress The new progress value for the achievement.
 @param successBlock Callback block that will be called with the updated Achievement.
 @param errorBlock Callback block that will be called instead of successBlock if an error occurs.
 */
- (void)progressSetWithAchievementId:(NSString*)achievementId progress:(int)progress successBlock:(void(^)(PIOAchievement*))successBlock errorBlock:(void(^)(PIOError*))errorBlock;

/**
 Add or subtract from the current progress of an achievement synchronously.
 @param achievementId The id of the achivement to add progress to.
 @param progressDelta The delta value that will be added to the current progress of the achievement.
 @return The updated achievement
 */
//- (PIOAchievement*)progressAddWithAchievementId:(NSString*)achievementId progressDelta:(int)progressDelta;

/**
 Add or subtract from the current progress of an achievement asynchronously.
 @param achievementId The id of the achievement to add progress to.
 @param progressDelta The delta value that will be added to the current progress of the achievement.
 @param successBlock Callback block that will be called with the updated Achievement.
 */
- (void)progressAddWithAchievementId:(NSString*)achievementId progressDelta:(int)progressDelta successBlock:(void(^)(PIOAchievement*))successBlock;

/**
 Add or subtract from the current progress of an achievement asynchronously.
 @param achievementId The id of the achievement to add progress to.
 @param progressDelta The delta value that will be added to the current progress of the achievement.
 @param successBlock Callback block that will be called with the updated Achievement.
 @param errorBlock Callback block that will be called instead of successBlock if an error occurs.
 */
- (void)progressAddWithAchievementId:(NSString*)achievementId progressDelta:(int)progressDelta successBlock:(void(^)(PIOAchievement*))successBlock errorBlock:(void(^)(PIOError*))errorBlock;

/**
 Sets the current progress value to the bigger value of progress or the current value synchronously, i.e; newProgress = Max(currentProgress,progress)
 @param achievementId The id of the achivement to work on.
 @param progress The possible new progress value that should be compared to the current progress value.
 @return Returns the modified Achievement object
 */
//- (PIOAchievement*)progressMaxWithAchievementId:(NSString*)achievementId progress:(int)progress;

/**
 Sets the current progress value to the bigger value of progress or the current value asynchronously, i.e; newProgress = Max(currentProgress,progress)
 @param achievementId The id of the achivement to work on.
 @param progress The possible new progress value that should be compared to the current progress value.
 @param successBlock Callback block that will be called with the updated Achievement.
 */
- (void)progressMaxWithAchievementId:(NSString*)achievementId progress:(int)progress successBlock:(void(^)(PIOAchievement*))successBlock;

/**
 Sets the current progress value to the bigger value of progress or the current value asynchronously, i.e; newProgress = Max(currentProgress,progress)
 @param achievementId The id of the achivement to work on.
 @param progress The possible new progress value that should be compared to the current progress value.
 @param successBlock Callback block that will be called with the updated Achievement.
 @param errorBlock Callback block that will be called instead of successBlock if an error occurs.
 */
- (void)progressMaxWithAchievementId:(NSString*)achievementId progress:(int)progress successBlock:(void(^)(PIOAchievement*))successBlock errorBlock:(void(^)(PIOError*))errorBlock;


/**
 Complete the specified achievement, by setting the progress to the maximum (ProgressGoal) of the achievement synchronously.
 @param achievementId The id of the achivement to complete.
 @return The updated achievement.
 */
//- (PIOAchievement*)progressCompleteWithAchievementId:(NSString*)achievementId;

/**
 Complete the specified achievement, by setting the progress to the maximum (ProgressGoal) of the achievement asynchronously.
 @param achievementId The id of the achivement to complete.
 @param successBlock Callback block that will be called with the updated Achievement.
 */
- (void)progressCompleteWithAchievementId:(NSString*)achievementId successBlock:(void(^)(PIOAchievement*))successBlock;

/**
 Complete the specified achievement, by setting the progress to the maximum (ProgressGoal) of the achievement asynchronously.
 @param achievementId The id of the achivement to complete.
 @param successBlock Callback block that will be called with the updated Achievement.
 @param errorBlock Callback block that will be called instead of successBlock if an error occurs.
 */
- (void)progressCompleteWithAchievementId:(NSString*)achievementId successBlock:(void(^)(PIOAchievement*))successBlock errorBlock:(void(^)(PIOError*))errorBlock;

@end
