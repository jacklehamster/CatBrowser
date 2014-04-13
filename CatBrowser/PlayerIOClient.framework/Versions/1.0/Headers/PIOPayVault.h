#import "PIOVaultItem.h"
#import "PIOError.h"

/**
 *  <p>The Player.IO PayVault.</p>
 *  
 *  <p>Instances of this class represent a specific user's Vault, and contains methods and properties both for inspecting and manipulating the contents.</p>
 *  <p>All properties and methods that inspect the Vault requires that it is up-to-date first. This can be achieved explicitly by calling the -refresh: method
 *  or implicitly by calling any method which modifies the Vault. </p>
 *  
 *  <p>Here is how to read the Coins balance:</p>
 *  <pre>
 *  PIOPayVault* vault = client.payVault;
 *  [vault refresh]
 *  int coins = vault.coins;
 *  </pre>
 *  
 *  <p>This is how you check if an item exists:</p>
 *  <pre>
 *  [client.payVault refresh]
 *  if([client.payVault hasItem:@"simplecar"]) {
 * 		//...
 *  }
 *  </pre>
 *  
 *  <p>Credit and Debit can be used like this:</p>
 *  <pre>
 *  [client.payVault creditCoins:100 reason:@"New player bonus" successBlock:^(void) {
 *    int newcoins = client.payVvault.Coins;
 *  }];
 *  
 *  [client.payVault debitCoins:10 reason:@"Starting fee" successBlock:^(void) {
 *    int newcoins = client.payVvault.Coins;
 *  }];
 *  </pre>
 *  
 *  <p>Buying items with Coins is really easy. This example requires that you have created an item in the PayVaultItems table in BigDB with the key "speedboost", and a property "PriceCoins" containing the price.</p>
 *  <pre>
 *  NSArray buyItems = [NSArray arrayWithObject:[PIOBuyItemInfo itemWithKey:@"speedboost"]];
 *  [client.payVault buyItems:buyItems storeItems:YES successBlock:^(void){
 *    NSUInteger boostCount = [client.payVault countOfItem:@"speedboost"];
 *  }];
 *  </pre>
 *  
 *  <p>And here's how to consume an item:</p>
 *  <pre>
 *  [client.payVault refresh];
 *  PIOVaultItem* boost = [vault firstItem:@"speedboost"];
 *  if (boost != bil) {
 *	  [client.payVault consumeItem:boost successBlock:^(void){
 *      // Boost the player's car
 *    }];
 *  }
 *  </pre>
 *  
 *  <p>When it's time for a user to add more Coins, you can do it like this:</p>
 *  <pre>
 *  NSMutableDictionary* args = [NSMutableDictionary dictionary];
 *  [info setObject:@"..." forKey:@"offerid"];
 *  [client.payVault getBuyCoinsInfoWithProvider:@"socialgold" purchaseArguments:args successBlock:^(NSDictionary* result) {
 *    NSString* url = [result objectForKey:@"socialgoldurl"];
 *    // todo: show url to player
 *  }];
 *  </pre>
 *  
 *  <p>And this is how to let the user buy an item directly. This requires that you have created an item in the PayVaultItems table in BigDB with the key "supercar", and a property "PriceUSD" containing the price.</p>
 *  <pre>
 *  NSMutableDictionary* args = [NSMutableDictionary dictionary];
 *  [info setObject:@"USD" forKey:@"currency"];
 *  [info setObject:@"Red Supercar" forKey:@"item_name"];
 *  NSArray buyItems = [NSArray arrayWithObject:[PIOBuyItemInfo itemWithKey:@"speedboost"]];
 *  [client.payVault getBuyDirectInfoWithProvider:@"paypal" purchaseArguments:info items:buyItems successBlock:^(NSDictionary* result) {
 *    NSString* url = [result objectForKey:@"paypalurl"];
 *    // todo: show url to player
 *  }];
 *  </pre>
 *  
 *  <p>Finally, there are methods for retrieving the payment history of a user:</p>
 *  <pre>
 *  [client.payVault readHistoryWithPage:1 pageSize:10 successBlock:^(NSArray *historyEntries) {
 *		// ...
 *  });
 *  </pre>
 */
@interface PIOPayVault : NSObject

/** Get the current coin balance in this Vault. This method can only be called on an up-to-date vault. */
- (int) coins;
/** Get the list of items in this Vault. This method can only be called on an up-to-date vault. */
- (NSArray*) items;

/**
* This method checks if the Vault contains at least one item of the given itemKey. This method can only be called on an up-to-date vault.
* @param itemKey The itemKey to check for.
* @return True if the user has at least one item of the given type (itemKey).
* @throws PlayerIOError
*/
- (BOOL) hasItem:(NSString*)itemKey;
/**
* Returns the first item of the given itemKey from this Vault. This method can only be called on an up-to-date vault.
* @param itemKey The itemKey of the item to get.
* @return A VaultItem if one was found, or null if not.
* @throws PlayerIOError
*/
- (PIOVaultItem*) firstItem:(NSString*)itemKey;
/**
* Returns the number of items of a given itemKey is in this Vault. This method can only be called on an up-to-date vault.
* @param itemKey The itemKey of the items to count.
* @return The number of items of the given type that the user has in the vault.
* @throws PlayerIOError
*/
- (NSUInteger) countOfItem:(NSString*)itemKey;

/**
* Refreshes this Vault, making sure the Items and Coins are up-to-date.
* @throws PlayerIOError
*/
/*- (void) refresh;*/
/**
* Refreshes this Vault, making sure the Items and Coins are up-to-date.
* @param successBlock A callback block that will be called when the vault is successfully updated.
*/
- (void) refreshWithSuccessBlock:(void (^)(void))successBlock;
/**
* Refreshes this Vault, making sure the Items and Coins are up-to-date.
* @param successBlock A callback block that will be called when the vault is successfully updated.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) refreshWithSuccessBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
* Loads a page of entries from this Vaults history, in reverse chronological order, i.e. newest first.
* @param page The page of entries to load. The first page has number 0.
* @param pageSize The number of entries per page.
* @throws PlayerIOError
*/
/*- (NSArray*) readHistoryWithPage:(NSUInteger)page pageSize:(NSUInteger)pageSize;*/
/**
* Loads a page of entries from this Vaults history, in reverse chronological order, i.e. newest first.
* @param page The page of entries to load. The first page has number 0.
* @param pageSize The number of entries per page.
* @param successBlock A callback block that will be called with the history entries in the specified page.
*/
- (void) readHistoryWithPage:(NSUInteger)page pageSize:(NSUInteger)pageSize successBlock:(void (^)(NSArray* historyEntries))successBlock;
/**
* Loads a page of entries from this Vaults history, in reverse chronological order, i.e. newest first.
* @param page The page of entries to load. The first page has number 0.
* @param pageSize The number of entries per page.
* @param successBlock A callback block that will be called with the history entries in the specified page.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) readHistoryWithPage:(NSUInteger)page pageSize:(NSUInteger)pageSize successBlock:(void (^)(NSArray* historyEntries))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
* Give coins to this Vault
* @param coinAmount The amount of coins to give.
* @param reason Your reason for giving the coins to this user. This will show up in the vault history, and in the PayVault admin panel for this user.
* @throws PlayerIOError
*/
/*- (void) creditCoins:(NSUInteger)coinAmount reason:(NSString*)reason;*/
/**
* Give coins to this Vault
* @param coinAmount The amount of coins to give.
* @param reason Your reason for giving the coins to this user. This will show up in the vault history, and in the PayVault admin panel for this user.
* @param successBlock A callback block that will be called when the coins have been credited to the vault.
*/
- (void) creditCoins:(NSUInteger)coinAmount reason:(NSString*)reason successBlock:(void (^)(void))successBlock;
/**
* Give coins to this Vault
* @param coinAmount The amount of coins to give.
* @param reason Your reason for giving the coins to this user. This will show up in the vault history, and in the PayVault admin panel for this user.
* @param successBlock A callback block that will be called when the coins have been credited to the vault.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) creditCoins:(NSUInteger)coinAmount reason:(NSString*)reason successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/*- (void) debitCoins:(NSUInteger)coinAmount reason:(NSString*)reason;*/
/**
* Take coins from this Vault
* @param coinAmount The amount of coins to take.
* @param reason Your reason for taking the coins from this user. This will show up in the vault history, and in the PayVault admin panel for this user.
* @param successBlock A callback block that will be called when the coins have been debited from the vault.
*/
- (void) debitCoins:(NSUInteger)coinAmount reason:(NSString*)reason successBlock:(void (^)(void))successBlock;
/**
* Take coins from this Vault
* @param coinAmount The amount of coins to take.
* @param reason Your reason for taking the coins from this user. This will show up in the vault history, and in the PayVault admin panel for this user.
* @param successBlock A callback block that will be called when the coins have been debited from the vault.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) debitCoins:(NSUInteger)coinAmount reason:(NSString*)reason successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
* Consume an item in the Vault. This will cause the item to be removed. The action will not show up in the vault history.
* @param item The VaultItem to use from the users vault - this should be an instances from the items in this Vault.
* @throws PlayerIOError
*/
/*- (void) consumeItem:(PIOVaultItem*)item;*/
/**
* Consume an item in the Vault. This will cause the item to be removed. The action will not show up in the vault history.
* @param item The VaultItem to use from the users vault - this should be an instances from the items in this Vault.
* @param successBlock A callback block that will be called when the item has been removed from the users vault.
*/
- (void) consumeItem:(PIOVaultItem*)item successBlock:(void (^)(void))successBlock;
/**
* Consume an item in the Vault. This will cause the item to be removed. The action will not show up in the vault history.
* @param item The VaultItem to use from the users vault - this should be an instances from the items in this Vault.
* @param successBlock A callback block that will be called when the item has been removed from the users vault.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) consumeItem:(PIOVaultItem*)item successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
* Consume items in this Vault. This will cause them to be removed. The action will not show up in the vault history.
* @param items The VaultItems to use from the users vault - this should be instances of items in this Vault.
* @throws PlayerIOError
*/
/*- (void) consumeItems:(NSArray*)items;*/
/**
* Consume items in this Vault. This will cause them to be removed. The action will not show up in the vault history.
* @param items The VaultItems to use from the users vault - this should be instances of items in this Vault.
* @param successBlock A callback block that will be called when the items has been removed from the users vault.
*/
- (void) consumeItems:(NSArray*)items successBlock:(void (^)(void))successBlock;
/**
* Consume items in this Vault. This will cause them to be removed. The action will not show up in the vault history.
* @param items The VaultItems to use from the users vault - this should be instances of items in this Vault.
* @param successBlock A callback block that will be called when the items has been removed from the users vault.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) consumeItems:(NSArray*)items successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
* Buy items with Coins.
* @param storeItems Whether or not to store the items in the vault after purchase
* @param items A list of items to buy, together with any additional payload.
* @throws PlayerIOError
*/
/*- (void) buyItems:(NSArray*)items storeItems:(BOOL)storeItems;*/
/**
* Buy items with Coins.
* @param storeItems Whether or not to store the items in the vault after purchase
* @param items A list of items to buy, together with any additional payload.
* @param successBlock A callback block that will be called when the item has been successfully bought with coins.
*/
- (void) buyItems:(NSArray*)items storeItems:(BOOL)storeItems successBlock:(void (^)(void))successBlock;
/**
* Buy items with Coins.
* @param storeItems Whether or not to store the items in the vault after purchase
* @param items A list of items to buy, together with any additional payload.
* @param successBlock A callback block that will be called when the item has been successfully bought with coins.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) buyItems:(NSArray*)items storeItems:(BOOL)storeItems successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
* Give the user items without taking any of his coins from the vault.
* @param items A list of items to give, together with any additional payload.
* @throws PlayerIOError
*/
/*- (void) giveItems:(NSArray*)items;*/
/**
* Give the user items without taking any of his coins from the vault.
* @param items A list of items to give, together with any additional payload.
* @param successBlock A callback block that will be called when the item is succesfully given.
*/
- (void) giveItems:(NSArray*)items successBlock:(void (^)(void))successBlock;
/**
* Give the user items without taking any of his coins from the vault.
* @param items A list of items to give, together with any additional payload.
* @param successBlock A callback block that will be called when the item is succesfully given.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void) giveItems:(NSArray*)items successBlock:(void (^)(void))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
* Gets information about how to make a coin purchase with the specified PayVault provider.
* @param provider The name of the PayVault provider to use for the coin purchase.
* @param purchaseArguments Any additional information that will be given to the PayVault provider to configure this purchase.
* @throws PlayerIOError
*/
/*- (NSDictionary*)   getBuyCoinsInfoWithProvider:(NSString*)provider purchaseArguments:(NSDictionary*)purchaseArguments;*/
/**
* Gets information about how to make a coin purchase with the specified PayVault provider.
* @param provider The name of the PayVault provider to use for the coin purchase.
* @param purchaseArguments Any additional information that will be given to the PayVault provider to configure this purchase.
* @param successBlock A callback block that will be called with information about how to complete the coins purchase.
*/
- (void)            getBuyCoinsInfoWithProvider:(NSString*)provider purchaseArguments:(NSDictionary*)purchaseArguments successBlock:(void (^)(NSDictionary*))successBlock;
/**
* Gets information about how to make a coin purchase with the specified PayVault provider.
* @param provider The name of the PayVault provider to use for the coin purchase.
* @param purchaseArguments Any additional information that will be given to the PayVault provider to configure this purchase.
* @param successBlock A callback block that will be called with information about how to complete the coins purchase.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void)            getBuyCoinsInfoWithProvider:(NSString*)provider purchaseArguments:(NSDictionary*)purchaseArguments successBlock:(void (^)(NSDictionary*))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
* Gets information about how to make a direct item purchase with the specified PayVault provider.
* @param provider The name of the PayVault provider to use for the item purchase.
* @param purchaseArguments Any additional information that will be given to the PayVault provider to configure this purchase.
* @param items A list of items to buy, together with any additional payload.
* @throws PlayerIOError
*/
/*- (NSDictionary*)   getBuyDirectInfoWithProvider:(NSString*)provider purchaseArguments:(NSDictionary*)purchaseArguments items:(NSArray*)items;*/
/**
* Gets information about how to make a direct item purchase with the specified PayVault provider.
* @param provider The name of the PayVault provider to use for the item purchase.
* @param purchaseArguments Any additional information that will be given to the PayVault provider to configure this purchase.
* @param items A list of items to buy, together with any additional payload.
* @param successBlock A callback block that will be called with information about how to complete the buy item direct purchase.
*/
- (void)            getBuyDirectInfoWithProvider:(NSString*)provider purchaseArguments:(NSDictionary*)purchaseArguments items:(NSArray*)items successBlock:(void (^)(NSDictionary*))successBlock;
/**
* Gets information about how to make a direct item purchase with the specified PayVault provider.
* @param provider The name of the PayVault provider to use for the item purchase.
* @param purchaseArguments Any additional information that will be given to the PayVault provider to configure this purchase.
* @param items A list of items to buy, together with any additional payload.
* @param successBlock A callback block that will be called with information about how to complete the buy item direct purchase.
* @param errorBlock A callback block that will be called on error, with information about the error.
*/
- (void)            getBuyDirectInfoWithProvider:(NSString*)provider purchaseArguments:(NSDictionary*)purchaseArguments items:(NSArray*)items successBlock:(void (^)(NSDictionary*))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;
@end
