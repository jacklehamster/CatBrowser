//
//  BookmarkCollectionViewCell.m
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/5/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import "BookmarkCollectionViewCell.h"

@implementation BookmarkCollectionViewCell



- (IBAction)clickCell {
    [_delegate clickedCell:_index];
}
@end
