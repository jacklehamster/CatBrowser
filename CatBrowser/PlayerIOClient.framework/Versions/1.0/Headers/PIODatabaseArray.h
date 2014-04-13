#import <Foundation/Foundation.h>

@class DatabaseCore;
@class PIODatabaseObject;

/**
 *  <p>Represents an BigDB array of values that can be accessed by index.</p>
 *  <p>DatabaseArray is very similar to the DatabaseObject class since it has methods for getting, setting, checking and removing values. But unlike DatabaseObject, this class also has methods for adding and inserting values, and there is no save method, since these cannot be saved to a BigDB table, they always have to be a property of an object.</p>
 *  <p>If we for example have an object that can be visualized like this:</p>
 *  <pre>
 *  'car54321' = {
 * 		Name: 'OldSpeedy',
 * 		LatestLapTimes: [
 * 			{
 * 				Time:'20:34',
 * 				Position:1
 * 			},
 * 			{
 * 				Time:'22:03',
 * 				Position:4
 * 			},
 * 			{
 * 				Time:'22:30',
 * 				Position:5
 * 			}
 * 		]
 *  }
 *  </pre>
 *  <p>Then we would create it in BigDB like this:</p>
 *  <pre>
 *  //Create new object
 *  PIODatabaseObject* car = [PIODatabaseObject object];
 *  [car setString:@"OldSpeedy" forProperty:@"Name"];
 *  
 *  //Make laptimes
 *  PIODatabaseObject* laptime1 = [PIODatabaseObject object];
 *  [laptime1 setString:@"20:34" forProprety:@"Time"];
 *  [laptime1 setInt:1 forProperty:@"Position"];
 *  PIODatabaseObject* laptime2 = [PIODatabaseObject object];
 *  [laptime2 setString:@"22:03" forProprety:@"Time"];
 *  [laptime2 setInt:4 forProperty:@"Position"];
 *  PIODatabaseObject* laptime3 = [PIODatabaseObject object];
 *  [laptime3 setString:@"22:30" forProprety:@"Time"];
 *  [laptime3 setInt:5 forProperty:@"Position"];
 *  
 *  //Make array and add laptimes
 *  PIODatabaseArray* laptimes = [PIODatabaseArray array];
 *  [laptimes addObject:laptime1];
 *  [laptimes addObject:laptime2];
 *  [laptimes addObject:laptime3];
 *  
 *  //Add array to car object
 *  [car setArray:laptimes forProperty:@"LatestLapTimes"];
 *  
 *  //Save car to table "Cars" under key "car54321"
 *  [client.bigDB createObjectWithKey:@"car54321" inTable:@"Cars" object:car];
 *  </pre>
 *  
 *  <p>However, just like DatabaseObject, DatabaseArray also supports nested property names, and we can refer to values in the array with their index number. Using this, we can make the example object in an easier way, like this:</p>
 *  <pre>
 *  PIODatabaseObject* car = [PIODatabaseObject object];
 *  [car setString:@"OldSpeedy" forProperty:@"Name"];
 *  [car setArray:[PIODatabaseArray array] forProperty:@"LatestLapTimes"];
 *  [car setString:@"20:34" forProperty:@"LatestLapTimes.0.Time"];
 *  [car setInt:1 forProperty:@"LatestLapTimes.0.Position"];
 *  [car setString:@"22:03" forProperty:@"LatestLapTimes.1.Time"];
 *  [car setInt:1 forProperty:@"LatestLapTimes.1.Position"];
 *  [car setString:@"22:30" forProperty:@"LatestLapTimes.2.Time"];
 *  [car setInt:1 forProperty:@"LatestLapTimes.2.Position"];
 *  </pre>
 *  
 *  <p>Getting values works exactly like for DatabaseObject, and we can also use nested properties.</p>
 *  <pre>
 *  [client.bigDB loadObjectWithKey:@"car20312" fromTable:@"Cars" successBlock:^(PIODatabaseObject car){
 *    PIODatabaseArray* laptimes = [car arrayForProperty:@"LatestLaptimes"];
 *    PIODatabaseObject* laptime = [laptimes objectAtIndex:0];
 *    int position = [laptime intForProperty:@"Position"];
 *  
 *    //Get position from second laptime
 *    int position2 = [laptimes intForProperty:@"1.Position"];
 *  		
 *    //Or get position from third laptime directly
 *    int position3 = [car intForProperty:@"LatestLapTimes.2.Position"];
 *  });
 *  </pre>
 *  
 *  <p>In addition to getting and setting values, we can also add values to the end of the array, insert values in the middle of it, or remove values in the middle of it. Note that the arrays are sparse, this means that removing a value doesn't shift the indexes of the following values, and we can set any value beyond the last value of the array.</p>
 *  <pre>
 *  PIODatabaseArray arr = [DatabaseArray array];
 * 
 *  //We make an array like this: ['a', 'c']
 *  [arr addString:@"a"];
 *  [arr addString:@"c"];
 *  
 *  //Now it will look like this: ['a', 'c', 'd']
 *  [arr addString:@"d"];
 *  
 *  //We insert a value where c is to get this: ['a', 'b', 'c', 'd']
 *  [arr insertString:@"b" atIndex:1];
 *  
 *  //If we then remove the third value we get this: ['a', 'b', null, 'd']
 *  [arr removeObjectAtIndex:2];
 *  
 *  //Finally, we set the sixth value and get: ['a', 'b', null, 'd', null, 'f']
 *  [arr setString:@"f" atIndex:5];
 *  </pre>
 */
@interface PIODatabaseArray : NSObject{
    @private
    DatabaseCore*   _core;
    NSUInteger      _count;
}

/** Create a new autoreleased PIODatabaseObject */
+ (PIODatabaseArray*) array;

/** Returns the number of entries in this array */
- (NSUInteger) count;
/** Get the indexes used in this array */ 
- (NSArray*) allIndexes;
/** Get all values from the properties of this array. Primitive properties (integers, floats, etc.) are wrapped in NSNumber */ 
- (NSArray*) allValues;
/** Enumerator to move over all keys (indexes used) in the array */
- (NSEnumerator*) keyEnumerator;
/** Enumerator to move over all objects in the array */
- (NSEnumerator*) objectEnumerator;
/** Fast enumeration over the values in the array */
- (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(id *)stackbuf count:(NSUInteger)len;
/** Removes all properties on this array */
- (void) removeAllObjects;
/** Removes the given entry from this array */
- (PIODatabaseArray*) removeObjectAtIndex:(NSUInteger)index;
/** Returns true if the given property exists on this object */
- (BOOL) containsObjectAtIndex:(NSUInteger)index;
/** Get the given property as an NSObject. Primitive properties (integers, floats, etc.) are wrapped in NSNumber */
- (id) valueAtIndex:(NSUInteger)index;
/** Get the given String property */
- (NSString*) stringAtIndex:(NSUInteger)index;
/** Get the given String property, or the default if it doesn't exist. */
- (NSString*) stringAtIndex:(NSUInteger)index defaultValue:(NSString*)defaultValue;
/** Get the given int property */
- (int32_t) intAtIndex:(NSUInteger)index;
/** Get the given int property, or the default if it doesn't exist. */
- (int32_t) intAtIndex:(NSUInteger)index defaultValue:(int32_t)defaultValue;
/** Get the given uint property */
- (uint32_t) uintAtIndex:(NSUInteger)index;
/** Get the given uint property, or the default if it doesn't exist. */
- (uint32_t) uintAtIndex:(NSUInteger)index defaultValue:(uint32_t)defaultValue;
/** Get the given long long property */
- (int64_t) longAtIndex:(NSUInteger)index;
/** Get the given long property, or the default if it doesn't exist. */
- (int64_t) longAtIndex:(NSUInteger)index defaultValue:(int64_t)defaultValue;
/** Get the given boolean property */
- (BOOL) boolAtIndex:(NSUInteger)index;
/** Get the given boolean property, or the default if it doesn't exist. */
- (BOOL) boolAtIndex:(NSUInteger)index defaultValue:(BOOL)defaultValue;
/** Get the given float property */
- (float) floatAtIndex:(NSUInteger)index;
/** Get the given float property, or the default if it doesn't exist. */
- (float) floatAtIndex:(NSUInteger)index defaultValue:(float)defaultValue;
/** Get the given double property */
- (double) doubleAtIndex:(NSUInteger)index;
/** Get the given double property, or the default if it doesn't exist. */
- (double) doubleAtIndex:(NSUInteger)index defaultValue:(double)defaultValue;
/** Get the given byte array property */
- (NSData*) dataAtIndex:(NSUInteger)index;
/** Get the given byte array property, or the default if it doesn't exist. */
- (NSData*) dataAtIndex:(NSUInteger)index defaultValue:(NSData*)defaultValue;
/** Get the given Date property */
- (NSDate*) dateAtIndex:(NSUInteger)index;
/** Get the given Date property, or the default if it doesn't exist. */
- (NSDate*) dateAtIndex:(NSUInteger)index defaultValue:(NSDate*)defaultValue;
/** Get the given DatabaseObject property */
- (PIODatabaseObject*) objectAtIndex:(NSUInteger)index;
/** Get the given DatabaseArray property */
- (PIODatabaseArray*) arrayAtIndex:(NSUInteger)index;

/** Set the array entry to the given string value */
- (PIODatabaseArray*) setString:(NSString*)value atIndex:(NSUInteger)index;
/** Set the array entry to the given int value */
- (PIODatabaseArray*) setInt:(int32_t)value atIndex:(NSUInteger)index;
/** Set the array entry to the given uint value */
- (PIODatabaseArray*) setUInt:(uint32_t)value atIndex:(NSUInteger)index;
/** Set the array entry to the given long value */
- (PIODatabaseArray*) setLong:(int64_t)value atIndex:(NSUInteger)index;
/** Set the array entry too the given boolean value */
- (PIODatabaseArray*) setBool:(BOOL)value atIndex:(NSUInteger)index;
/** Set the array entry to the given float value */
- (PIODatabaseArray*) setFloat:(float)value atIndex:(NSUInteger)index;
/** Set the array entry to the given double value */
- (PIODatabaseArray*) setDouble:(double)value atIndex:(NSUInteger)index;
/** Set the array entry to the given bye array value */
- (PIODatabaseArray*) setData:(NSData*)value atIndex:(NSUInteger)index;
/** Set the array entry to the given Date value */
- (PIODatabaseArray*) setDate:(NSDate*)value atIndex:(NSUInteger)index;
/** Set the array entry to the given DatabaseObject value */
- (PIODatabaseArray*) setObject:(PIODatabaseObject*)value atIndex:(NSUInteger)index;
/** Set the array entry too the given DatabaseArray value */
- (PIODatabaseArray*) setArray:(PIODatabaseArray*)value atIndex:(NSUInteger)index;

/** Add the given string value to the end of the database array */
- (PIODatabaseArray*) addString:(NSString*)value;
/** Add the given int value to the end of the database array */
- (PIODatabaseArray*) addInt:(int32_t)value;
/** Add the given unsigned integer value to the end of the database array */
- (PIODatabaseArray*) addUInt:(uint32_t)value;
/** Add the given long value to the end of the database array */
- (PIODatabaseArray*) addLong:(int64_t)value;
/** Add the given boolean value to the end of the database array */
- (PIODatabaseArray*) addBool:(BOOL)value;
/** Add the given float value to the end of the database array */
- (PIODatabaseArray*) addFloat:(float)value;
/** Add the given double value to the end of the database array */
- (PIODatabaseArray*) addDouble:(double)value;
/** Add the given NSData value to the end of the database array */
- (PIODatabaseArray*) addData:(NSData*)value;
/** Add the given NSDate value to the end of the database array */
- (PIODatabaseArray*) addDate:(NSDate*)value;
/** Add the given database object to the end of the database array */
- (PIODatabaseArray*) addObject:(PIODatabaseObject*)value;
/** Add the given database array value to the end of this database array */
- (PIODatabaseArray*) addArray:(PIODatabaseArray*)value;

/** Insert the given string value at the specified index of the database array */
- (PIODatabaseArray*) insertString:(NSString*)value atIndex:(NSUInteger)index;
/** Insert the given int value at the specified index of the database array */
- (PIODatabaseArray*) insertInt:(int32_t)value atIndex:(NSUInteger)index;
/** Insert the given unsigned integer value at the specified index of the database array */
- (PIODatabaseArray*) insertUInt:(uint32_t)value atIndex:(NSUInteger)index;
/** Insert the given long value at the specified index of the database array */
- (PIODatabaseArray*) insertLong:(int64_t)value atIndex:(NSUInteger)index;
/** Insert the given boolean value at the specified index of the database array */
- (PIODatabaseArray*) insertBool:(BOOL)value atIndex:(NSUInteger)index;
/** Insert the given float value at the specified index of the database array */
- (PIODatabaseArray*) insertFloat:(float)value atIndex:(NSUInteger)index;
/** Insert the given double value at the specified index of the database array */
- (PIODatabaseArray*) insertDouble:(double)value atIndex:(NSUInteger)index;
/** Insert the given NSData value at the specified index of the database array */
- (PIODatabaseArray*) insertData:(NSData*)value atIndex:(NSUInteger)index;
/** Insert the given NSDate value at the specified index of the database array */
- (PIODatabaseArray*) insertDate:(NSDate*)value atIndex:(NSUInteger)index;
/** Insert the given database object at the specified index of the database array */
- (PIODatabaseArray*) insertObject:(PIODatabaseObject*)value atIndex:(NSUInteger)index;
/** Insert the given database array at the specified index of the database array */
- (PIODatabaseArray*) insertArray:(PIODatabaseArray*)value atIndex:(NSUInteger)index;


//--------------

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
- (uint32_t) uintForProperty:(NSString*)propertyExpression defaultValue:(uint32_t)defaultValue;
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
- (PIODatabaseArray*) setString:(NSString*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given int value */
- (PIODatabaseArray*) setInt:(int32_t)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given uint value */
- (PIODatabaseArray*) setUInt:(uint32_t)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given long value */
- (PIODatabaseArray*) setLong:(int64_t)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given boolean value */
- (PIODatabaseArray*) setBool:(BOOL)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given float value */
- (PIODatabaseArray*) setFloat:(float)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given double value */
- (PIODatabaseArray*) setDouble:(double)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given bye array value */
- (PIODatabaseArray*) setData:(NSData*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given Date value */
- (PIODatabaseArray*) setDate:(NSDate*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given DatabaseObject value */
- (PIODatabaseArray*) setObject:(PIODatabaseObject*)value forProperty:(NSString*)propertyExpression; 
/** Set the specified property to the given DatabaseArray value */
- (PIODatabaseArray*) setArray:(PIODatabaseArray*)value forProperty:(NSString*)propertyExpression;
@end
