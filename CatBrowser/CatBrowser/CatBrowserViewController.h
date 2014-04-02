//
//  ViewController.h
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/2/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CatBrowserViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIWebView *webView;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *rewind;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *stop;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *refresh;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *forward;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *cat;


- (void)loadRequestFromString:(NSString*)urlString;


@end
