//
//  BookmarkCollectionViewCellDelegate.h
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/5/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol BookmarkCollectionViewCellDelegate <NSObject>
@required
- (void) clickedCell:(long)index;
@end
