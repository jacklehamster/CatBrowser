#import "PIOErrorCodes.h"

/** 
 * An error in Player.IO 
 */
@interface PIOError : NSException{
    PIOErrorCode _errorCode;
}

- (id) initWithErrCode:(PIOErrorCode)errorCode message:(NSString*)string;

/** The error code of the given error. Compare with values on PIOErrorCodes */
- (PIOErrorCode) errorCode;

+ (PIOError*) error:(NSString*)message, ...;
+ (PIOError*) errorWithCode:(PIOErrorCode)errorCode message:(NSString*)message, ...;
@end
