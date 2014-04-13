@class PIOError;
@class PIODatabaseArray;
@class PIODatabaseObject;

/**
 *  <p>The BigDB service.</p>
 *  <p>This class is used to create, load, and delete database objects. All database objects are stored in tables and have a unique key.
 *  You can set up tables in your admin panel, and you can also set up indexes there for when you want to load objects by properties
 *  or ranges of properties. Please note that all methods are asynchronous and any handling of results have to be done in a callback.
 *  If you don't care about the results of a method call, typically for create or delete functions, you can just pass in a null callback.</p>
 *  <p>Here's how to store and update an object:</p>
 *  <pre>
 *  //Make new object and set some properties
 *  PIODatabaseObject* obj = [PIODatabaseObject object];
 *  [obj setString:@"Adam" forProperty:@"username"];
 *  [obj setString:@"London" forProperty:@"location"];
 *  [obj setInt:20 forProperty:@"age"];
 *
 *  //Create object in table Users with ConnectUserId as key
 *  [client.bigDB createObjectWithKey:connectUserId inTable:@"Users" object:obj successBlock:^(PIODatabaseObject object){
 *    [object setString:@"Paris" forProperty:@"location"];
 *    [object saveWithSuccessBlock:nil];
 *  }];
 *  </pre>
 *  <p>This is how you load an object:</p>
 *  <pre>
 *  [client.bigDB loadObjectWithKey:connectUserId fromTable:@"Users" successBlock:^(PIODatabaseObject result){
 *    if (result != nil) {
 *      //Change a property and save back.
 *      [object setString:@"Paris" forProperty:@"location"];
 *      [object saveWithSuccessBlock:nil];
 *    }
 *  }];
 *  </pre>
 *  <p>In case you always want to modify an object, you can use the LoadOrCreate method to ensure you get an object back:</p>
 *  <pre>
 *  [client.bigDB loadOrCreateObjectWithKey:connectUserId inTable:@"Users" successBlock:^(PIODatabaseObject result){
 *    if ( ![result containsProperty:@"username"] ) {
 *      //Empty object, initialize it
 *      [obj setString:@"Charlie" forProperty:@"username"];
 *      [obj setInt:20 forProperty:@"age"];
 *    }
 *    [object setString:@"Copenhagen" forProperty:@"location"];
 *    [object saveWithSuccessBlock:nil];
 *  }];
 *  </pre>
 *  <p>
 *  BigDB also supports indexes for retrieving objects by a specific property, a range of properties,
 *  or to sort objects by properties. Indexes need to be set up in the admin panel for each table,
 *  each index needs a name, and a list of properties, and for each property you also need to specify a
 *  sort order.
 *  </p>
 *  <p>Imagine that we have objects that look like this:</p>
 *  <pre>
 *  {
 *  	username:"Adam",
 *  	created:2010-05-12 15:28
 *  	location:"London",
 *  	age:20,
 *  }
 *  </pre>
 *  <p>That we have defined an index called "ByUsername" that looks like this:
 *  	<ul>
 *  		<li>{Property:"username", Type:String, Order:Ascending}</li>
 *  	</ul>
 *  </p>
 *  <p>And an index called "ByCreated" that looks like this:
 *  	<ul>
 *  		<li>{Property:"created", Type:Datetime, Order:Descending}</li>
 *  	</ul>
 * </p>
 *  <p>Then we can do lookups like these:</p>
 *  <pre>
 *  //Get the object where username="Adam"
 *  [client.bigDB loadSingleFromTable:@"Users" index:@"ByUsername" indexValue:[NSArray arrayWithObject:@"Adam"] successBlock:^(PIOdatabaseObject* loaded){
 *    //...
 *  }];
 *
 *  //Get all users with usernames between "Adam" and "Charlie".
 *  //This would retrieve users named "Adamsson" and "Barney",
 *  //but not users named "Abel" or "Charlotte".
 *  [client.bigDB loadRangeFromTable:@"Users" index:@"ByUsername" indexPath:nil start:@"Adam" stop:@"Charlie" limit:100 successBlock:^(NSArray* results){
 *    //...
 *  }];
 *
 *  //Get all users up to and including "Adam". This would retrieve
 *  //users named "Aaron" and "Ackerman", but not "Adamsson" or "Barney".
 *  [client.bigDB loadRangeFromTable:@"Users" index:@"ByUsername" indexPath:nil start:nil stop:@"Adam" limit:100 successBlock:^(NSArray* results){
 *    //...
 *  }];
 *
 *  //Get all users from "Xerxes". This would retrieve users named
 *  //"Yngwie" and "Zed", but not "Charlie" or "Xantippa".
 *  [client.bigDB loadRangeFromTable:@"Users" index:@"ByUsername" indexPath:nil start:@"Xerxes" stop:nil limit:100 successBlock:^(NSArray* results){
 *    //...
 *  }];
 *
 *  //Retrieve the ten first objects by the ByCreated index.
 *  //Since that index is sorted in descending order, this will actually
 *  //retrieve the 10 latest created users.
 *  [client.bigDB loadRangeFromTable:@"Users" index:@"ByCreated" indexPath:nil start:nil stop:nil limit:10 successBlock:^(NSArray* results){
 *    //...
 *  }];
 *
 *  //Get the 10 latest users that were created more than 7 days ago.
 *  NSDate* weekago = [NSDate dateWithNaturalLanguageString:@"one week ago"];
 *  [client.bigDB loadRangeFromTable:@"Users" index:@"ByCreated" indexPath:nil start:weekago stop:nil limit:10 successBlock:^(NSArray* results){
 *    //...
 *  }];
 *  </pre>
 *  <p>
 *  BigDB also supports compound indexes, that is indexes with more than one property. Given our example object above, we can create an index called "ByLocationAgeCreated" that looks like this:
 *  	<ul>
 *  		<li>{Property:"location", Type:String, Order:Ascending}</li>
 *  		<li>{Property:"age", Type:Integer, Order:Ascending}</li>
 *  		<li>{Property:"created", Type:Datetime, Order:Descending}</li>
 *  	</ul>
 *  </p>
 *  <p>
 *  With this index, we can then lookup on either location, or location and age, or location and age and created. If we use more than one property in the lookup, we can only specify the range for the last one, the preceding ones have to be fixed and are sent in via the path parameter.
 *  </p>
 *  <pre>
 *  //Load all users where location is "London"
 *  [client.bigDB loadRangeFromTable:@"Users" index:@"ByLocationAgeCreated" indexPath:nil start:@"London" stop:@"London" limit:100 successBlock:^(NSArray* results){
 *    //...
 *  }];
 *
 *  //Load all users from London between 20 and 30 years of age
 *  [client.bigDB loadRangeFromTable:@"Users" index:@"ByLocationAgeCreated" indexPath:[NSArray arrayWithObject:@"London"] start:[NSNumber numberWithInt:20] stop:[NSNumber numberWithInt:30] limit:100 successBlock:^(NSArray* results){
 *    //...
 *  }];
 *
 *  //Load all users from London that are above 50
 *  [client.bigDB loadRangeFromTable:@"Users" index:@"ByLocationAgeCreated" indexPath:[NSArray arrayWithObject:@"London"] start:[NSNumber numberWithInt:50] stop:nil limit:100 successBlock:^(NSArray* results){
 *    //...
 *  }];
 *
 *  //Load all users from Paris that are 30 years old, and were created in April
 *  [client.bigDB loadRangeFromTable:@"Users" index:@"ByLocationAgeCreated" indexPath:[NSArray arrayWithObjects:@"London", [NSNumber numberWithInt:30], nil] start:[NSDate dateWithNaturalLanguageString:@"April 1st, 2010"] stop:[NSDate dateWithNaturalLanguageString:@"April 30th, 2010"] limit:100 successBlock:^(NSArray* results){
 *    //...
 *  }];
 *
 *  //Load the 10 latest 20-year old users from Amsterdam
 *  [client.bigDB loadRangeFromTable:@"Users" index:@"ByLocationAgeCreated" indexPath:[NSArray arrayWithObjects:@"Amsterdam", [NSNumber numberWithInt:20], nil] start:nil stop:nil limit:10 successBlock:^(NSArray* results){
 *    //...
 *  }];
 *  </pre>
 *
 *  <p>Finally, deleting objects is as easy as calling the DeleteKeys method, or DeleteRange if you want to delete by an index.</p>
 *  <pre>
 *  //Delete current Users object.
 *  [client.bigDB deleteKeys:[NSArray arrayWithObject:connectUserId] fromTable:@"Users"];
 *
 *  //Delete all objects with usernames between "Adam" and "Charlie"
 *  [client.bigDB deleteRangeFromTable:@"Users" index:@"ByUsername" indexPath:nil start:@"Adam" stop:@"Charlie"];
 *  </pre>
 */
@interface PIOBigDB : NSObject

/*
    Creates a new database object in the given table with the specified key. If no key is specified (null), the object will receive an autogenerated id.
    @param key The key to assign to the database object.
    @param table The name of the table to create the database object in.
    @param object The database object to create in the table.
    @return A new instance of PIODatabaseObject from which -save: can be called for future modifications.
    @throws PlayerIOError

- (PIODatabaseObject*)  createObjectWithKey:(NSString*)key inTable:(NSString*)table object:(PIODatabaseObject*)object;
*/

/**
Creates a new database object in the given table with the specified key. If no key is specified (null), the object will receive an autogenerated id.
@param key The key to assign to the database object.
@param table The name of the table to create the database object in.
@param object The database object to create in the table.
@param successBlock A callback block that will be called with the created database object from which -save: can be called for future modifications.
*/
- (void) createObjectWithKey:(NSString*)key inTable:(NSString*)table object:(PIODatabaseObject*)object successBlock:(void (^)(PIODatabaseObject* created))successBlock;
/**
Creates a new database object in the given table with the specified key. If no key is specified (null), the object will receive an autogenerated id.
@param key The key to assign to the database object.
@param table The name of the table to create the database object in.
@param object The database object to create in the table.
@param successBlock A callback block that will be called with the created database object from which -save: can be called for future modifications.
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) createObjectWithKey:(NSString*)key inTable:(NSString*)table object:(PIODatabaseObject*)object successBlock:(void (^)(PIODatabaseObject* created))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*
Loads the database object corresponding to the player from the PlayerObjects table.
@return The database object corresponding to the player in the PlayerObjects table.
@throws PlayerIOError

- (PIODatabaseObject*) loadMyPlayerObject;
 */

/**
Loads the database object corresponding to the player from the PlayerObjects table.
@param successBlock A callback block that will be called with the database object corresponding to the player in the PlayerObjects table.
*/
- (void) loadMyPlayerObjectWithSuccessBlock:(void (^)(PIODatabaseObject* playerObject))successBlock;
/**
Loads the database object corresponding to the player from the PlayerObjects table.
@param successBlock A callback block that will be called with the database object corresponding to the player in the PlayerObjects table.
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) loadMyPlayerObjectWithSuccessBlock:(void (^)(PIODatabaseObject* playerObject))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*
Load the database object with the given key from the given table.
@param key The key of the database object to load.
@param table The table to load the database object from.
@return The database object found, or null if no object exists with the given key.
@throws PlayerIOError
- (PIODatabaseObject*) loadObjectWithKey:(NSString*)key fromTable:(NSString*)table;
*/

/**
Load the database object with the given key from the given table.
@param key The key of the database object to load.
@param table The table to load the database object from.
@param successBlock A callback block that will be called with the database object found
*/
- (void) loadObjectWithKey:(NSString*)key fromTable:(NSString*)table successBlock:(void (^)(PIODatabaseObject* object))successBlock;
/**
Load the database object with the given key from the given table.
@param key The key of the database object to load.
@param table The table to load the database object from.
@param successBlock A callback block that will be called with the database object found
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) loadObjectWithKey:(NSString*)key fromTable:(NSString*)table successBlock:(void (^)(PIODatabaseObject* object))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*
Loads the database objects with the given keys from the given table.
@param keys The keys of the database objects to load.
@param table The table to load the database objects from.
@return An array of database objects in the same order as the keys array, with null values for non-existant database objects.
@throws PlayerIOError
- (NSArray*) loadObjectsWithKeys:(NSArray*)keys fromTable:(NSString*)table;
*/

/**
Loads the database objects with the given keys from the given table.
@param keys The keys of the database objects to load.
@param table The table to load the database objects from.
@param successBlock A callback block that will be called with the database objects found
*/
- (void) loadObjectsWithKeys:(NSArray*)keys fromTable:(NSString*)table successBlock:(void (^)(NSArray* objects))successBlock;
/**
Loads the database objects with the given keys from the given table.
@param keys The keys of the database objects to load.
@param table The table to load the database objects from.
@param successBlock A callback block that will be called with the database objects found
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) loadObjectsWithKeys:(NSArray*)keys fromTable:(NSString*)table successBlock:(void (^)(NSArray* objects))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*
Loads or creates the database object with the given key from the given table.
@param key The key of the database object to load or create
@param table The table from which to load or create the database object
@return The database object created or loaded
@throws PlayerIOError
- (PIODatabaseObject*) loadOrCreateObjectWithKey:(NSString*)key fromTable:(NSString*)table;
 */

/**
Loads or creates the database object with the given key from the given table.
@param key The key of the database object to load or create
@param table The table from which to load or create the database object
@param successBlock A callback block that will be called with the database object found or created
*/
- (void) loadOrCreateObjectWithKey:(NSString*)key fromTable:(NSString*)table successBlock:(void (^)(PIODatabaseObject* object))successBlock;
/**
Loads or creates the database object with the given key from the given table.
@param key The key of the database object to load or create
@param table The table from which to load or create the database object
@param successBlock A callback block that will be called with the database object found or created
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) loadOrCreateObjectWithKey:(NSString*)key fromTable:(NSString*)table successBlock:(void (^)(PIODatabaseObject* object))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*
Loads or creates database objects with the given keys from the given table. New objects are created if there are no existing objects for the given keys.
@param keys The keys of the database objects to load or create.
@param table The table from which to load or create the database objects.
@return An array of database objects in the same order as the keys array.
@throws PlayerIOError
- (NSArray*) loadOrCreateObjectsWithKeys:(NSArray*)keys fromTable:(NSString*)table;
*/

/**
Loads or creates database objects with the given keys from the given table. New objects are created if there are no existing objects for the given keys.
@param keys The keys of the database objects to load or create.
@param table The table from which to load or create the database objects.
@param successBlock A callback block that will be called with the database objects found or created in the same order as the keys array
*/
- (void) loadOrCreateObjectsWithKeys:(NSArray*)keys fromTable:(NSString*)table successBlock:(void (^)(NSArray* objects))successBlock;
/**
Loads or creates database objects with the given keys from the given table. New objects are created if there are no existing objects for the given keys.
@param keys The keys of the database objects to load or create.
@param table The table from which to load or create the database objects.
@param successBlock A callback block that will be called with the database objects found or created in the same order as the keys array
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) loadOrCreateObjectsWithKeys:(NSArray*)keys fromTable:(NSString*)table successBlock:(void (^)(NSArray* objects))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*
Delete a set of database objects from a table.
@param keys The keys of the database objects to delete.
@param table The table to delete the database objects from.
@throws PlayerIOError
- (void) deleteKeys:(NSArray*)keys fromTable:(NSString*)table;
 */

/**
Delete a set of database objects from a table.
@param keys The keys of the database objects to delete.
@param table The table to delete the database objects from.
@param successBlock A callback block that will be called when the objects have been successfully deleted
*/
- (void) deleteKeys:(NSArray*)keys fromTable:(NSString*)table successBlock:(void (^)(void))successBlock;
/**
Delete a set of database objects from a table.
@param keys The keys of the database objects to delete.
@param table The table to delete the database objects from.
@param successBlock A callback block that will be called when the objects have been successfully deleted
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) deleteKeys:(NSArray*)keys fromTable:(NSString*)table successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*
Save changes to one or more database objects in one go.
@param objects The objects with changes to save.
@param useOptimisticLocks Should the save only go through, if no other process has modified the object since it was loaded?
@param fullOverwrite Will completely overwrite the database object in BigDB with the properties in this instance, instead of just sending the changed properties to the server.
@throws PlayerIOError
- (void) saveChanges:(NSArray*)objects useOptimisticLocks:(BOOL)useOptimisticLocks fullOverwrite:(BOOL)fullOverwrite;
*/

/**
Save changes to one or more database objects in one go.
@param objects The objects with changes to save.
@param useOptimisticLocks Should the save only go through, if no other process has modified the object since it was loaded?
@param fullOverwrite Will completely overwrite the database object in BigDB with the properties in this instance, instead of just sending the changed properties to the server.
@param successBlock A callback block that will be called when the changes have been successfully saved
*/
- (void) saveChanges:(NSArray*)objects useOptimisticLocks:(BOOL)useOptimisticLocks fullOverwrite:(BOOL)fullOverwrite successBlock:(void (^)(void))successBlock;
/**
Save changes to one or more database objects in one go.
@param objects The objects with changes to save.
@param useOptimisticLocks Should the save only go through, if no other process has modified the object since it was loaded?
@param fullOverwrite Will completely overwrite the database object in BigDB with the properties in this instance, instead of just sending the changed properties to the server.
@param successBlock A callback block that will be called when the changes have been successfully saved
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) saveChanges:(NSArray*)objects useOptimisticLocks:(BOOL)useOptimisticLocks fullOverwrite:(BOOL)fullOverwrite successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*
Load a database object from a table using the specified index.
@param table The table to load the database object from.
@param index The name of the index to query for the database object.
@param indexValue An array of objects of the same types as the index properties, specifying which object to load.
@return The database object found, or null if no object was found.
@throws PlayerIOError
- (PIODatabaseObject*) loadSingleFromTable:(NSString*)table index:(NSString*)index indexValue:(NSArray*)indexValue;
*/

/**
Load a database object from a table using the specified index.
@param table The table to load the database object from.
@param index The name of the index to query for the database object.
@param indexValue An array of objects of the same types as the index properties, specifying which object to load.
@param successBlock A callback block that will be called with the found database object (or nil of no object was found).
*/
- (void) loadSingleFromTable:(NSString*)table index:(NSString*)index indexValue:(NSArray*)indexValue successBlock:(void (^)(PIODatabaseObject* object))successBlock;
/**
Load a database object from a table using the specified index.
@param table The table to load the database object from.
@param index The name of the index to query for the database object.
@param indexValue An array of objects of the same types as the index properties, specifying which object to load.
@param successBlock A callback block that will be called with the found database object (or nil of no object was found).
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) loadSingleFromTable:(NSString*)table index:(NSString*)index indexValue:(NSArray*)indexValue successBlock:(void (^)(PIODatabaseObject* object))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*
Load a range of database objects from a table using the specified index.
@param table The table to load the database objects from.
@param index The name of the index to query for the database objects.
@param indexPath Where in the index to start the range search: An array of objects of the same types as the index properties, specifying where in the index to start loading database objects from. For instance, in the index [Mode,Map,Score] you might use new object[]{"expert","skyland"} as the indexPath and use the start and stop arguments to determine the range of scores you wish to return. IndexPath can be set to null if there is only one property in the index.
@param start Where to start the range search. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then start defines the minimum score to include in the results.
@param stop Where to stop the range search. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then stop defines the maximum score to include in the results.
@param limit The max amount of objects to return.
@return The database objects found.
@throws PlayerIOError
- (NSArray*) loadRangeFromTable:(NSString*)table index:(NSString*)index indexPath:(NSArray*)indexPath start:(id)start stop:(id)stop limit:(int)limit;
*/

/**
Load a range of database objects from a table using the specified index.
@param table The table to load the database objects from.
@param index The name of the index to query for the database objects.
@param indexPath Where in the index to start the range search: An array of objects of the same types as the index properties, specifying where in the index to start loading database objects from. For instance, in the index [Mode,Map,Score] you might use new object[]{"expert","skyland"} as the indexPath and use the start and stop arguments to determine the range of scores you wish to return. IndexPath can be set to null if there is only one property in the index.
@param start Where to start the range search. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then start defines the minimum score to include in the results.
@param stop Where to stop the range search. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then stop defines the maximum score to include in the results.
@param limit The max amount of objects to return.
@param successBlock A callback block that will be called with an array of found database objects
*/
- (void) loadRangeFromTable:(NSString*)table index:(NSString*)index indexPath:(NSArray*)indexPath start:(id)start stop:(id)stop limit:(int)limit successBlock:(void (^)(NSArray* objects))successBlock;
/**
Load a range of database objects from a table using the specified index.
@param table The table to load the database objects from.
@param index The name of the index to query for the database objects.
@param indexPath Where in the index to start the range search: An array of objects of the same types as the index properties, specifying where in the index to start loading database objects from. For instance, in the index [Mode,Map,Score] you might use new object[]{"expert","skyland"} as the indexPath and use the start and stop arguments to determine the range of scores you wish to return. IndexPath can be set to null if there is only one property in the index.
@param start Where to start the range search. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then start defines the minimum score to include in the results.
@param stop Where to stop the range search. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then stop defines the maximum score to include in the results.
@param limit The max amount of objects to return.
@param successBlock A callback block that will be called with an array of found database objects
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) loadRangeFromTable:(NSString*)table index:(NSString*)index indexPath:(NSArray*)indexPath start:(id)start stop:(id)stop limit:(int)limit successBlock:(void (^)(NSArray* objects))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*
Delete a range of database objects from a table using an index.
@param table The table to delete the database object from.
@param index The name of the index to query for the database objects to delete.
@param indexPath Where in the index to start the range delete: An array of objects of the same types as the index properties, specifying where in the index to start loading database objects from. For instance, in the index [Mode,Map,Score] you might use new object[]{"expert","skyland"} as the indexPath and use the start and stop arguments to determine the range of scores you wish to delete. IndexPath can be set to null instead of an empty array.
@param start Where to start the range delete. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then start defines the minimum score to delete.
@param stop Where to stop the range delete. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then stop defines the maximum score to delete.
@throws PlayerIOError
- (void) deleteRangeFromTable:(NSString*)table index:(NSString*)index indexPath:(NSArray*)indexPath start:(id)start stop:(id)stop;
*/

/**
Delete a range of database objects from a table using an index.
@param table The table to delete the database object from.
@param index The name of the index to query for the database objects to delete.
@param indexPath Where in the index to start the range delete: An array of objects of the same types as the index properties, specifying where in the index to start loading database objects from. For instance, in the index [Mode,Map,Score] you might use new object[]{"expert","skyland"} as the indexPath and use the start and stop arguments to determine the range of scores you wish to delete. IndexPath can be set to null instead of an empty array.
@param start Where to start the range delete. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then start defines the minimum score to delete.
@param stop Where to stop the range delete. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then stop defines the maximum score to delete.
@param successBlock A callback block that will be called when the objects have been successfully deleted.
*/
- (void) deleteRangeFromTable:(NSString*)table index:(NSString*)index indexPath:(NSArray*)indexPath start:(id)start stop:(id)stop successBlock:(void (^)(void))successBlock;
/**
Delete a range of database objects from a table using an index.
@param table The table to delete the database object from.
@param index The name of the index to query for the database objects to delete.
@param indexPath Where in the index to start the range delete: An array of objects of the same types as the index properties, specifying where in the index to start loading database objects from. For instance, in the index [Mode,Map,Score] you might use new object[]{"expert","skyland"} as the indexPath and use the start and stop arguments to determine the range of scores you wish to delete. IndexPath can be set to null instead of an empty array.
@param start Where to start the range delete. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then start defines the minimum score to delete.
@param stop Where to stop the range delete. For instance, if the index is [Mode,Map,Score] and indexPath is ["expert","skyland"], then stop defines the maximum score to delete.
@param successBlock A callback block that will be called when the objects have been successfully deleted.
@param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) deleteRangeFromTable:(NSString*)table index:(NSString*)index indexPath:(NSArray*)indexPath start:(id)start stop:(id)stop successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;
@end
