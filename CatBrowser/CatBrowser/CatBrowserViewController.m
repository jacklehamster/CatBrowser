//
//  ViewController.m
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/2/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import "CatBrowserViewController.h"

@interface CatBrowserViewController () <UIWebViewDelegate>
- (void)updateButtons;

@end


@implementation CatBrowserViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [[self webView] setDelegate:self];
    // Do any additional setup after loading the view, typically from a nib.
    [self loadRequestFromString:@"http://www.google.com"];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)loadRequestFromString:(NSString*)urlString
{
    NSURL *url = [NSURL URLWithString:urlString];
    NSURLRequest *urlRequest = [NSURLRequest requestWithURL:url];
    [self.webView loadRequest:urlRequest];
}

- (void)updateButtons
{
    self.forward.enabled = self.webView.canGoForward;
    self.rewind.enabled = self.webView.canGoBack;
    self.stop.enabled = self.webView.loading;
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    [self updateButtons];
}
- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    [self updateButtons];
}
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    [self updateButtons];
}
@end
