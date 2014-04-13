@class DatabaseCore;
#import "PIODatabaseObject.h"
#import "PIODatabaseArray.h"
/**
 *  Represents information about an item in a user's Vault.
 *  <p>The methods and properties in a PIOVaultItem are very simliar to those of a PIODatabaseObject, except that it's read-only, and that there are some extra properties regarding the purchase.</p>
 *  <pre>
 *  //Get a 'simplecar' from the Vault
 *  PIOVaultItem* car = [client.payVault firstItem:@"simplecar"];
 *  if (car != nil) {
 *  	NSString* color = [car stringForProperty:@"Color"];
 *  }
 *  </pre>
 */
@interface PIOVaultItem : NSObject{
    @private
    DatabaseCore* _core;
    NSString* _id;
    NSString* _itemKey;
    NSDate* _purchaseDate;
}

/** The unique id of this particular vault item in the users vault. */
- (NSString*) id;
/** key of the underlying item in the PayVaultItems BigDB table */
- (NSString*) itemKey;
/** The unique id of this particular vault item in the users vault. */
- (NSDate*) purchaseDate;

/** Returns the number of properties on this object */
- (NSUInteger) count;
/** Get the names of all properties on this object */ 
- (NSArray*) allProperties;
/** Get all values from the properties of this object. Primitive properties (integers, floats, etc.) are wrapped in NSNumber */ 
- (NSArray*) allValues;
/** Enumerator to move over keys used for properties in the object */
- (NSEnumerator*) keyEnumerator;
/** Enumerator to move over all properties in the object */
- (NSEnumerator*) objectEnumerator;
/** Fast enumeration over the properties in the object */
- (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(id *)stackbuf count:(NSUInteger)len;
/** Returns true if the given property exists on this object */
- (BOOL) containsProperty:(NSString*)propertyExpression;
/** Get the given property as an object. Primitive properties (integers, floats, etc.) are wrapped in NSNumber */
- (id) valueForProperty:(NSString*)propertyExpression;
/** Get the given String property */
- (NSString*) stringForProperty:(NSString*)propertyExpression;
/** Get the given String property, or the default if it doesn't exist. */
- (NSString*) stringForProperty:(NSString*)propertyExpression defaultValue:(NSString*)defaultValue;
/** Get the given int property */
- (int32_t) intForProperty:(NSString*)propertyExpression;
/** Get the given int property, or the default if it doesn't exist. */
- (int32_t) intForProperty:(NSString*)propertyExpression defaultValue:(int32_t)defaultValue;
/** Get the given uint property */
- (uint32_t) uintForProperty:(NSString*)propertyExpression;
/** Get the given uint property, or the default if it doesn't exist. */
- (uint32_t) uintForProperty:(NSString*)propertyExpression defaultValue:(uint)defaultValue;
/** Get the given long property */
- (int64_t) longForProperty:(NSString*)propertyExpression;
/** Get the given long property, or the default if it doesn't exist. */
- (int64_t) longForProperty:(NSString*)propertyExpression defaultValue:(int64_t)defaultValue;
/** Get the given boolean property */
- (BOOL) boolForProperty:(NSString*)propertyExpression;
/** Get the given boolean property, or the default if it doesn't exist. */
- (BOOL) boolForProperty:(NSString*)propertyExpression defaultValue:(BOOL)defaultValue;
/** Get the given float property */
- (float) floatForProperty:(NSString*)propertyExpression;
/** Get the given float property, or the default if it doesn't exist. */
- (float) floatForProperty:(NSString*)propertyExpression defaultValue:(float)defaultValue;
/** Get the given double property */
- (double) doubleForProperty:(NSString*)propertyExpression;
/** Get the given double property, or the default if it doesn't exist. */
- (double) doubleForProperty:(NSString*)propertyExpression defaultValue:(double)defaultValue;
/** Get the given byte array property */
- (NSData*) dataForProperty:(NSString*)propertyExpression;
/** Get the given byte array property, or the default if it doesn't exist. */
- (NSData*) dataForProperty:(NSString*)propertyExpression defaultValue:(NSData*)defaultValue;
/** Get the given Date property */
- (NSDate*) dateForProperty:(NSString*)propertyExpression;
/** Get the given Date property, or the default if it doesn't exist. */
- (NSDate*) dateForProperty:(NSString*)propertyExpression defaultValue:(NSDate*)defaultValue;
/** Get the given DatabaseObject property */
- (PIODatabaseObject*) objectForProperty:(NSString*)propertyExpression;
/** Get the given DatabaseArray property */
- (PIODatabaseArray*) arrayForProperty:(NSString*)propertyExpression;

- (NSString*) toStringWithIndention:(NSString*)indention;
@end
 