//
//  BookmarkCollectionViewControllerDelegate.h
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/5/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import <Foundation/Foundation.h>


@protocol BookmarkCollectionViewControllerDelegate <NSObject>
@required
- (void) openLink:(NSString*) location;
@end
