
/**
 * The Player.IO ErrorLog service. 
 */
@interface PIOErrorLog : NSObject

/**
* Writes an entry to the error log
* @param error A short string describing the error without details. Example 'Object not set to instance of an object'
*/
- (void) writeError:(NSString*)error;
/**
* Writes an entry to the error log
* @param error A short string describing the error without details. Example 'Object not set to instance of an object'
* @param errorObj An NSError object with more information about the error
*/
- (void) writeError:(NSString*)error errorObj:(NSError*)errorObj;
/**
* Writes an entry to the error log
* @param error A short string describing the error without details. Example 'Object not set to instance of an object'
* @param exception An NSException object with more information about the error
*/
- (void) writeError:(NSString*)error exception:(NSException*)exception;
/**
* Writes an entry to the error log
* @param error A short string describing the error without details. Example 'Object not set to instance of an object'
* @param details The message describing the error in detail. Example 'couldn't find the user 'bob' in the current game'
* @param stacktrace The stacktrace (if available) of the error
*/
- (void) writeError:(NSString*)error details:(NSString*)details stacktrace:(NSString*)stacktrace;
/**
* Writes an entry to the error log
* @param error A short string describing the error without details. Example 'Object not set to instance of an object'
* @param details The message describing the error in detail. Example 'couldn't find the user 'bob' in the current game'
* @param stacktrace The stacktrace (if available) of the error
* @param extraData Any extra data you'd like to associate with the error log entry
*/
- (void) writeError:(NSString*)error details:(NSString*)details stacktrace:(NSString*)stacktrace extraData:(NSDictionary*)extraData;
@end
