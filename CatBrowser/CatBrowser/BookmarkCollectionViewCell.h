//
//  BookmarkCollectionViewCell.h
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/5/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BookmarkCollectionViewCellDelegate.h"

@interface BookmarkCollectionViewCell : UICollectionViewCell
@property (strong, nonatomic) IBOutlet UIButton *imageView;
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *loadIndicator;
@property (strong, nonatomic) IBOutlet UILabel *label;
@property (strong, nonatomic) IBOutlet UIImageView *star;
@property (strong, nonatomic) IBOutlet UIImageView *blackStar;
- (IBAction)clickCell;

@property long index;
@property id<BookmarkCollectionViewCellDelegate> delegate;

@end
