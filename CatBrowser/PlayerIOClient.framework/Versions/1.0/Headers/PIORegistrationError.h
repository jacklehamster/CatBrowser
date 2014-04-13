#import "PIOError.h"
/**
 * <p>Error class for PlayerIO QuickConnect registration errors.</p>
 * <p>If there are any errors when using the SimpleRegister method of QuickConnect, 
 * you will get back an error object of this type that holds more detail about the 
 * cause of the error. You can use this information to provide better help for your 
 * users when they are filling out your registration form.</p>
 */
@interface PIORegistrationError : PIOError{
    NSString* _usernameError;
    NSString* _passwordError;
    NSString* _emailError;
    NSString* _captchaError;
}

/** The error for the username field, if any. */
- (NSString*) usernameError;

/** The error for the password field, if any. */
- (NSString*) passwordError;

/** The error for the email field, if any.  */
- (NSString*) emailError;

/** The error for the captcha field, if any. */
- (NSString*) captchaError;
@end
