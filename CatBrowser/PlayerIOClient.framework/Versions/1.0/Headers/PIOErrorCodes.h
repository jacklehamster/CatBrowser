typedef NSString* PIOErrorCode;

/** 
 * The error codes used by PIOError objects 
 */
@interface PIOErrorCodes : NSObject
+(PIOErrorCode) byValue:(int)value;
/** The method requested is not supported */
+(PIOErrorCode) UnsupportedMethod;
/** A general error occurred */
+(PIOErrorCode) GeneralError;
/** An unexpected error occurred inside the Player.IO webservice. Please try again. */
+(PIOErrorCode) InternalError;
/** Access is denied */
+(PIOErrorCode) AccessDenied;
/** The message is malformatted */
+(PIOErrorCode) InvalidMessageFormat;
/** A value is missing */
+(PIOErrorCode) MissingValue;
/** A game is required to do this action */
+(PIOErrorCode) GameRequired;
/** An error occurred while contacting an external service */
+(PIOErrorCode) ExternalError;
/** The given argument value is outside the range of allowed values. */
+(PIOErrorCode) ArgumentOutOfRange;
/** The game has been disabled, most likely because of missing payment. */
+(PIOErrorCode) GameDisabled;
/** The game requested is not known by the server */
+(PIOErrorCode) UnknownGame;
/** The connection requested is not known by the server */
+(PIOErrorCode) UnknownConnection;
/** The auth given is invalid or malformatted */
+(PIOErrorCode) InvalidAuth;
/** There is no server in any of the selected server clusters for the game that are eligible to start a new room in (they're all at full capacity or there are no servers in any of the clusters). Either change the selected clusters for your game in the admin panel, try again later or start some more servers for one of your clusters. */
+(PIOErrorCode) NoServersAvailable;
/** The room data for the room was over the allowed size limit */
+(PIOErrorCode) RoomDataTooLarge;
/** You are unable to create room because there is already a room with the specified id */
+(PIOErrorCode) RoomAlreadyExists;
/** The game you're connected to does not have a room type with the specified name */
+(PIOErrorCode) UnknownRoomType;
/** There is no room running with that id */
+(PIOErrorCode) UnknownRoom;
/** You can't join the room when the RoomID is null or the empty string */
+(PIOErrorCode) MissingRoomId;
/** The room already has the maxmium amount of users in it. */
+(PIOErrorCode) RoomIsFull;
/** The key you specified is not set as searchable. You can change the searchable keys in the admin panel for the server type */
+(PIOErrorCode) NotASearchColumn;
/** The QuickConnect method (simple, facebook, kongregate...) is not enabled for the game. You can enable the various methods in the admin panel for the game */
+(PIOErrorCode) QuickConnectMethodNotEnabled;
/** The user is unknown */
+(PIOErrorCode) UnknownUser;
/** The password supplied is incorrect */
+(PIOErrorCode) InvalidPassword;
/** The supplied data is incorrect */
+(PIOErrorCode) InvalidRegistrationData;
/** The key given for the BigDB object is not a valid BigDB key. BigDB keys must be between 1 and 50 word characters (no spaces). */
+(PIOErrorCode) InvalidBigDBKey;
/** The object exceeds the maximum allowed size for BigDB objects. */
+(PIOErrorCode) BigDBObjectTooLarge;
/** Could not locate the database object. */
+(PIOErrorCode) BigDBObjectDoesNotExist;
/** The specified table does not exist. */
+(PIOErrorCode) UnknownTable;
/** The specified index does not exist. */
+(PIOErrorCode) UnknownIndex;
/** The value given for the index, does not match the expected type. */
+(PIOErrorCode) InvalidIndexValue;
/** The operation was aborted because the user attempting the operation was not the original creator of the object accessed. */
+(PIOErrorCode) NotObjectCreator;
/** The key is in use by another database object */
+(PIOErrorCode) KeyAlreadyUsed;
/** BigDB object could not be saved using optimistic locks as it's out of date. */
+(PIOErrorCode) StaleVersion;
/** Cannot create circular references inside database objects */
+(PIOErrorCode) CircularReference;
/** The server could not complete the heartbeat */
+(PIOErrorCode) HeartbeatFailed;
/** The game code is invalid */
+(PIOErrorCode) InvalidGameCode;
/** Cannot access coins or items before vault has been loaded. Please refresh the vault first. */
+(PIOErrorCode) VaultNotLoaded;
/** There is no PayVault provider with the specified id */
+(PIOErrorCode) UnknownPayVaultProvider;
/** The specified PayVault provider does not support direct purchase */
+(PIOErrorCode) DirectPurchaseNotSupportedByProvider;
/** The specified PayVault provider does not support buying coins */
+(PIOErrorCode) BuyingCoinsNotSupportedByProvider;
/** The user does not have enough coins in the PayVault to complete the purchase or debit. */
+(PIOErrorCode) NotEnoughCoins;
/** The item does not exist in the vault. */
+(PIOErrorCode) ItemNotInVault;
/** The chosen provider rejected one or more of the purchase arguments */
+(PIOErrorCode) InvalidPurchaseArguments;
/** The chosen provider is not configured correctly in the admin panel */
+(PIOErrorCode) InvalidPayVaultProviderSetup;
/** Unable to locate the custom PartnerPay action with the given key */
+(PIOErrorCode) UnknownPartnerPayAction;
/** The given type was invalid */
+(PIOErrorCode) InvalidType;
/** The index was out of bounds from the range of acceptable values */
+(PIOErrorCode) IndexOutOfBounds;
/** The given identifier does not match the expected format */
+(PIOErrorCode) InvalidIdentifier;
/** The given argument did not have the expected value */
+(PIOErrorCode) InvalidArgument;
/** This client has been logged out */
+(PIOErrorCode) LoggedOut;
/** The given segment was invalid. */
+(PIOErrorCode) InvalidSegment;
/** Cannot access requests before Refresh() has been called. */
+(PIOErrorCode) GameRequestsNotLoaded;
/** Cannot access achievements before Refresh() has been called. */
+(PIOErrorCode) AchievementsNotLoaded;
/** Cannot find the achievement with the specified id. */
+(PIOErrorCode) UnknownAchievement;
/** Cannot access notification endpoints before Refresh() has been called. */
+(PIOErrorCode) NotificationsNotLoaded;
/** The given notifications endpoint is invalid */
+(PIOErrorCode) InvalidNotificationsEndpoint;
/** The Yahoo features are only avaliable when authenticated to PlayerIO using Yahoo authentication. Authentication methods are managed in the connections setting of your game in the admin panel on PlayerIO. */
+(PIOErrorCode) YahooNotAvailable;
/** Cannot access profile, friends, ignored before Yahoo has been loaded. Please refresh Yahoo first. */
+(PIOErrorCode) YahooNotLoaded;
@end
