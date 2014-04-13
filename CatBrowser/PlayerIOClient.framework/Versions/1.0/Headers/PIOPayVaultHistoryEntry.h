/**
 * An entry in the user's PayVault history.
 */
@interface PIOPayVaultHistoryEntry : NSObject{
    @private
    NSString* _type;
    int _amount;
    NSDate* _timestamp;
    NSArray* _itemKeys;
    NSString* _reason;
    NSString* _providerTransactionId;
    NSString* _providerPrice;
}

/** The type of this entry, for example 'buy','credit','debit'... */
- (NSString*) type;
/** The coin amount of this entry. */
- (int) amount;
/** When this entry was created. */
- (NSDate*)timestamp;
/** The item keys related to this entry (entries with type 'buy'). */
- (NSArray*) itemKeys;
/** The developer supplied reason for entries of type 'credit' and 'debit'. */
- (NSString*) reason;
/** The transaction id from the PayVault provider corresponding to this entry. */
- (NSString*) providerTransactionId;
/** The price in real currency of this entry formatted as a human readable currency string, e.g. $10.00 USD */
- (NSString*) providerPrice;
@end
