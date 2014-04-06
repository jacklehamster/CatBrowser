//
//  BookmarkCollectionViewController.h
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/4/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BookmarkCollectionViewControllerDelegate.h"

@interface BookmarkCollectionViewController : UICollectionViewController

@property (nonatomic) UIImage* snapShot;
@property NSString* title;
@property NSString* location;
@property id<BookmarkCollectionViewControllerDelegate>delegate;
@end
