#import "PIODatabaseArray.h"
#import "PIOBigDB.h"

@class DatabaseCore;

/**
 *  <p>This class represents a BigDB Database Object that has a key and a collection of named properties.</p>
 *  <p>There are methods for setting, getting, and removing properties, and changes to the object can be persisted to BigDB with the -save: method.</p>
 *  <p>Database objects are very similar to JSON objects and are most easily visualized as such. For example, we can visualize a car object like this:</p>
 *  <pre>
 *  'car20312' = {
 * 		Name: 'OldSpeedy',
 * 		Stats:{
 * 			Acceleration: 3.2,
 * 			TopSpeed: 50,
 * 			Steering: 5,
 * 			WorkingBreaks:false
 * 		}
 * 		LatestLapTimes: ['20:34','22:03','22:30']
 *  }
 *  </pre>
 *  <p>If we then want to create this object in BigDB, we would have to do this:</p>
 *  <pre>
 *  PIODatabaseObject* car = [PIODatabaseObject object];
 *  [car setString:@"OldSpeedy" forProperty:@"Name"];
 *  
 *  //Create nested stats object
 *  PIODatabaseObject* stats = new PIODatabaseObject();
 *  [stats setFloat:3.2F forProperty:@"Acceleration"];
 *  [stats setInt:50 forProperty:@"TopSpeed"];
 *  [stats setInt:5 forProperty:@"Steering"];
 *  [stats setBool:NO forProperty:@"WorkingBreaks"];
 *  [car setObject:stats forProperty:@"Stats"];
 *  
 *  //Create laptimes array
 *  PIODatabaseArray* laptimes = [PIODatabaseArray array];
 *  [laptimes addString:@"20:34"];
 *  [laptimes addString:@"22:03"];
 *  [laptimes addString:@"22:30"];
 *  [car setArray:laptimes forProperty:@"LatestLapTimes"];
 *  
 *  //Save car to table "Cars" under key "car20312"
 *  [client.bigDB createObjectWithKey:@"car20312" inTable:@"Cars" object:car];
 *  </pre>
 *  <p>To make it easier to work with nested objects, you can reference them directly by separating the property names with a dot. Using this, we can set the stats properties of the car like this instead:</p>
 *  <pre>
 *  PIODatabaseObject* car = [PIODatabaseObject object];
 *  [car setFloat("Stats.Acceleration"];
 *  [car setInt:50 forProperty:"Stats.TopSpeed"];
 *  [car setInt:5 forProperty:"Stats.Steering];
 *  [car setBool:NO forProperty:@"Stats.WorkingBreaks"];
 *  </pre>
 *  
 *  <p>When you want to read properties from a database object, you have to call the corresponding get method indicating the type of the property.</p>
 *  <pre>
 *  [client.bigDB loadObjectWithKey:@"car20312" fromTable:@"Cars" successBlock:^(PIODatabaseObject object){
 *    NSString* name = [car stringForProperty:@"Name"];
 *    float name = [car floatForProperty:@"Stats.Acceleration"];
 *    int name = [car intForProperty:@"Stats.TopSpeed"];
 *  }];
 *  </pre>
 *  
 *  <p>BigDB doesn't enforce anything on your objects. Two objects in the same table do not need to have the same properties set, and do not need to have the same type on the same property. If you try to get a property that is missing, or if you are using a get method of the wrong type, you will get an exception.</p>
 *  <pre>
 *  [client.bigDB loadObjectWithKey:@"car20312" fromTable:@"Cars" successBlock:^(PIODatabaseObject object){
 *    // name is a string, throws exception!
 *    int name = [car intForProperty:@"Name"];
 *    // Color does not exist, throws exception!
 *    NSString* color = [car stringForProperty:@"Color"];
 *  }];
 *  </pre>
 *  
 *  <p>One way of avoiding this is to first check the object if a certain property exists before reading this. You can do this with the Contains method.</p>
 *  <pre>
 *  [client.bigDB loadObjectWithKey:@"car20312" fromTable:@"Cars" successBlock:^(PIODatabaseObject object){
 *    if( ![car containsProperty:@"Name"] ){
 *      [car setString:@"Unknown" forProperty:@"Name"];
 *    }
 *    if( ![car containsProperty:@"Stats.Steering"] ){
 *      //...
 *    }
 *  }];
 *  </pre>
 *  
 *  <p>Another way of avoiding errors is to specify a default value when calling a get method. If the object doesn't contain the property, the method will return your default value instead.</p>
 *  <pre>
 *  [client.bigDB loadObjectWithKey:@"car20312" fromTable:@"Cars" successBlock:^(PIODatabaseObject object){
 *    NSString* color = [car stringForProperty:@"Color" defaultValue:@"Red"];
 *  }];
 *  </pre>
 *  
 *  <p>You can also easily remove properties from your object with the Remove method.</p>
 *  <pre>
 *  [client.bigDB loadObjectWithKey:@"car20312" fromTable:@"Cars" successBlock:^(PIODatabaseObject object){
 *    [car removeProperty:@"Name"];
 *    [car removeProperty:@"Stats.TopSpeed"];
 *  }];
 *  </pre>
 *  
 *  <p>Finally, to persist any changes you've made to an object you can call the Save method. Note that you can only call Save on an object that exist in the database. This means that the first time you save an object you have to call the CreateObject method, but all subsequent times you can call the Save method. There is also a method called existsInDatabase that you can use to check if it has been created or not.</p>
 *  <pre>
 *  [car setString:@"NewSpeedy" forProperty:@"Name"];
 *  [car setFloat:5.0F forProperty:@"Stats.Acceleration"];
 *  if (car.existsInDatabase) {
 *  	[car save]
 *  } else {
 *  	[client.bigDB createObjectWithKey:@"car12345" inTable:@"Cars" objet:car];
 *  }
 *  </pre>
 *  
 *  <p>The Save method is asynchronous just like the CreateObject method in PlayerIO.BigDB, and you can specify a callback if you wish to do something when the object actually has been saved.</p>
 *  <pre>
 *  [car setString:@"NewSpeedy" forProperty:@"Name"];
 *  [car setFloat:5.0F forProperty:@"Stats.Acceleration"];
 *  [car saveWithSuccessBlock:^(void){
 *    //On successful save..
 *  }];
 *  </pre>
 */
@interface PIODatabaseObject : NSObject <NSFastEnumeration> {
    @private
    PIOBigDB*       _owner;
    BOOL            _createIfMissing;
    DatabaseCore*   _core;
    NSString*       _table;
    NSString*       _key;
    NSString*       _version;
    BOOL            _isSaving;
}

/** Create a new autoreleased PIODatabaseObject */
+ (PIODatabaseObject*) object;

/** Returns true if this object has been persisted. */
- (BOOL) existsInDatabase;
/** The name of the BigDB table this object belongs to */
- (NSString*) table;
/** The key of the object. */
- (NSString*) key;

/*
 * Persist the object to the database.
- (void) save;
 */

/*
 * Persist the object to the database, using optimistic locking if specified.
 * @param useOptimisticLocks If true, the save will only be completed if the database object has not changed in BigDB since this instance was loaded.
- (void) saveWithOptimisticLocking:(BOOL)useOptimisticLocks;
 */

/*
 * Persist the object to the database, using optimistic locking and full overwrite if specified.
 * @param useOptimisticLocks If true, the save will only be completed if the database object has not changed in BigDB since this instance was loaded.
 * @param fullOverwrite Will completely overwrite the database object in BigDB with the properties in this instance, instead of just sending the changed properties to the server.
- (void) saveWithOptimisticLocking:(BOOL)useOptimisticLocks fullOverwrite:(BOOL)fullOverwrite;
 */

/**
 * Persist the object to the database asynchronously.
 * @param successBlock A block that will be called if the call succeeds
 */
- (void) saveWithSuccessBlock:(void (^)(void))successBlock;
/**
 * Persist the object to the database asynchronously.
 * @param successBlock A block that will be called if the call succeeds
 * @param errorBlock A block that will be called if the call fails, with an error object describing what went wrong.
 */
- (void) saveWithSuccessBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;
/**
 * Persist the object to the database asynchronously, using optimistic locking if specified.
 * @param useOptimisticLocks If true, the save will only be completed if the database object has not changed in BigDB since this instance was loaded.
 * @param successBlock A block that will be called if the call succeeds
 */
- (void) saveWithOptimisticLocking:(BOOL)useOptimisticLocks successBlock:(void (^)(void))successBlock;
/**
 * Persist the object to the database asynchronously, using optimistic locking if specified.
 * @param useOptimisticLocks If true, the save will only be completed if the database object has not changed in BigDB since this instance was loaded.
 * @param successBlock A block that will be called if the call succeeds
 * @param errorBlock A block that will be called if the call fails, with an error object describing what went wrong.
 */
- (void) saveWithOptimisticLocking:(BOOL)useOptimisticLocks successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;
/**
 * Persist the object to the database asynchronously, using optimistic locking and full overwrite if specified.
 * @param useOptimisticLocks If true, the save will only be completed if the database object has not changed in BigDB since this instance was loaded.
 * @param fullOverwrite Will completely overwrite the database object in BigDB with the properties in this instance, instead of just sending the changed properties to the server.
 * @param successBlock A block that will be called if the call succeeds
 */
- (void) saveWithOptimisticLocking:(BOOL)useOptimisticLocks fullOverwrite:(BOOL)fullOverwrite successBlock:(void (^)(void))successBlock;
/**
 * Persist the object to the database asynchronously, using optimistic locking and full overwrite if specified.
 * @param useOptimisticLocks If true, the save will only be completed if the database object has not changed in BigDB since this instance was loaded.
 * @param fullOverwrite Will completely overwrite the database object in BigDB with the properties in this instance, instead of just sending the changed properties to the server.
 * @param successBlock A block that will be called if the call succeeds
 * @param errorBlock A block that will be called if the call fails, with an error object describing what went wrong.
 */
- (void) saveWithOptimisticLocking:(BOOL)useOptimisticLocks fullOverwrite:(BOOL)fullOverwrite successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;


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

/** Removes the given property from this object */
- (PIODatabaseObject*) removeProperty:(NSString*)propertyExpression;
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
- (PIODatabaseObject*) setString:(NSString*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given int value */
- (PIODatabaseObject*) setInt:(int32_t)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given uint value */
- (PIODatabaseObject*) setUInt:(uint32_t)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given long value */
- (PIODatabaseObject*) setLong:(int64_t)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given boolean value */
- (PIODatabaseObject*) setBool:(BOOL)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given float value */
- (PIODatabaseObject*) setFloat:(float)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given double value */
- (PIODatabaseObject*) setDouble:(double)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given bye array value */
- (PIODatabaseObject*) setData:(NSData*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given Date value */
- (PIODatabaseObject*) setDate:(NSDate*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given DatabaseObject value */
- (PIODatabaseObject*) setObject:(PIODatabaseObject*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given DatabaseArray value */
- (PIODatabaseObject*) setArray:(PIODatabaseArray*)value forProperty:(NSString*)propertyExpression; 
@end
