#import <Foundation/Foundation.h>
#import "PIODatabaseObject.h"
#import "PIODatabaseArray.h"

@class DatabaseCore;

/**
 *  Represents information about the purchase of a PayVault item.
 *  <para>The minimum information necessary to create an instance of this class is an itemKey representing the PayVaultItem that should be purchased.</para>
 *  <para>It is also possible to add a custom payload, and this data will always be present when reading the item from the user's Vault. 
 *  For example: Imagine that we have a racing game and users should be able to buy different cars of different colors, but that color doesn't affect the price
 *  of the car. Instead of creating one PayVaultItem for each combination of type and color, we need only create one item for each type and give them
 *  a different price, and color can then be added in the payload when buying a car.</para>
 *  <para>Setting the payload works exactly like manipulating a DatabaseObject from BigDB.</para>
 *  <pre>
 *  //Buy a red 'simplecar'.
 *  [client.vault buyItems:
 *      [NSArray arrayWithObject:
 *          [[PIOBuyItemInfo itemWithKey:@"simplecar"] setString:@"Red" forProperty:@"Color"]
 *      ]
 *      storeItems:YES
 *  ];
 *  </pre>
 */
@interface PIOBuyItemInfo : NSObject{
    @private
    DatabaseCore* _core;
    NSString* _itemKey;
}

/** Initialize the buy item info with the given key */
- (id) initWithItemKey:(NSString*)itemKey;
/** Create a new autoreleased buy item info with the given key */
+ (PIOBuyItemInfo*) itemWithKey:(NSString*)itemKey;
   
/** The key of the item to buy */
- (NSString*) itemKey;
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
/** Removes all properties on this object */
- (void) clear;
//--------------

/** 
 Removes the given property from this object
 @param propertyExpression The property to be removed
 @return The object instance so that it can be used in chained calls.
 */
- (PIOBuyItemInfo*) removeProperty:(NSString*)propertyExpression;
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

/** Set the specified property to the given string value */
- (PIOBuyItemInfo*) setString:(NSString*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given int value */
- (PIOBuyItemInfo*) setInt:(int32_t)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given uint value */
- (PIOBuyItemInfo*) setUInt:(uint32_t)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given long value */
- (PIOBuyItemInfo*) setLong:(int64_t)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given boolean value */
- (PIOBuyItemInfo*) setBool:(BOOL)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given float value */
- (PIOBuyItemInfo*) setFloat:(float)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given double value */
- (PIOBuyItemInfo*) setDouble:(double)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given bye array value */
- (PIOBuyItemInfo*) setData:(NSData*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given Date value */
- (PIOBuyItemInfo*) setDate:(NSDate*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given DatabaseObject value */
- (PIOBuyItemInfo*) setObject:(PIODatabaseObject*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given DatabaseArray value */
- (PIOBuyItemInfo*) setArray:(PIODatabaseArray*)value forProperty:(NSString*)propertyExpression; 

- (NSString*) toStringWithIndention:(NSString*)indention;
@end
