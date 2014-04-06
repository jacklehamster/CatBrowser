//
//  ViewController.m
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/2/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import "CatBrowserViewController.h"
#import "CatURLProtocol.h"
#import "BookmarkCollectionViewController.h"
#import "BookmarkCollectionViewControllerDelegate.h"

@interface CatBrowserViewController () <UIWebViewDelegate, UIScrollViewDelegate, UITextFieldDelegate, BookmarkCollectionViewControllerDelegate>
{
    NSTimer* bookmarkRefresh;
    NSURL* lastURL;
}
- (void)updateButtons;


@end


@implementation CatBrowserViewController

static NSString* HOME = @"https://www.google.com";

- (void)viewDidLoad
{
    [super viewDidLoad];
    [CatURLProtocol register];
    [[self webView] setDelegate:self];
    [[[self webView] scrollView] setDelegate:self];
    // Do any additional setup after loading the view, typically from a nib.
    [self loadRequestFromString:HOME];
    
    /* Create the page title label */
    UINavigationBar *navBar = self.navigationController.navigationBar;
    CGRect labelFrame = CGRectMake(kMargin+60, kSpacer,
                                   navBar.bounds.size.width - 2*kMargin-120, kLabelHeight);
    UILabel *label = [[UILabel alloc] initWithFrame:labelFrame];
    label.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    label.backgroundColor = [UIColor clearColor];
    label.font = [UIFont systemFontOfSize:12];
    label.textAlignment = NSTextAlignmentCenter;
    [navBar addSubview:label];
    self.pageTitle = label;
    
    /* Create the address bar */
    CGRect addressFrame = CGRectMake(kMargin+60, kSpacer*2.0 + kLabelHeight,
                                     navBar.bounds.size.width - 2*kMargin - 120, kAddressHeight);
    UITextField *address = [[UITextField alloc] initWithFrame:addressFrame];
    address.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    address.borderStyle = UITextBorderStyleRoundedRect;
    address.font = [UIFont systemFontOfSize:17];
    address.keyboardType = UIKeyboardTypeURL;
    address.autocorrectionType = UITextAutocorrectionTypeNo;
    address.delegate = self;

    [address addTarget:self
                action:@selector(loadRequestFromAddressField:)
      forControlEvents:UIControlEventEditingDidEndOnExit];
    [navBar addSubview:address];
    self.addressField = address;
}

- (void)loadRequestFromAddressField:(id)addressField
{
    NSString *urlString = [addressField text];
    [self loadRequestFromString:urlString];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSString*)encodeURIComponent:(NSString*)string
{
    return ((NSString*)CFBridgingRelease(CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault,
                                                                                 (CFStringRef)string,
                                                                                 NULL,
                                                                                 (CFStringRef)@"!*'();:@&=+$,/?%#[]",
                                                                                 kCFStringEncodingUTF8)));
}

- (void)loadRequestFromString:(NSString*)urlString
{
    NSURL *url = [NSURL URLWithString:urlString];
    NSString* scheme = url.scheme;
    if(!scheme) {
        url = [NSURL URLWithString:[@"https://www.google.com/#q=" stringByAppendingString:[self encodeURIComponent:urlString]]];
    }
    NSURLRequest *urlRequest = [NSURLRequest requestWithURL:url];
    [self.webView loadRequest:urlRequest];
    if([self samePath:url otherURL:lastURL] && !_webView.loading) {
        [self.webView reload];
    }
    lastURL = url;
}

- (BOOL) samePath:(NSURL*)url otherURL:(NSURL*)otherURL
{
    NSString* path1 = [[url absoluteString] substringToIndex:[[url absoluteString] length]-[[url fragment] length]-1];
    NSString* path2 = [[otherURL absoluteString] substringToIndex:[[otherURL absoluteString] length]-[[otherURL fragment] length]-1];
    return [path1 isEqualToString:path2];
}

- (IBAction)bookMark:(UIBarButtonItem *)sender {
}

- (IBAction)goHome:(id)sender {
    [CatURLProtocol setCat:YES];
    [self updateCatButton];
    [self loadRequestFromString:HOME];
}

- (void)updateButtons
{
    self.forward.enabled = self.webView.canGoForward;
    self.rewind.enabled = self.webView.canGoBack;
    self.stop.enabled = self.webView.loading;
}

- (void)updateTitle:(UIWebView*)aWebView
{
    NSString* pageTitle = [aWebView stringByEvaluatingJavaScriptFromString:@"document.title"];
    self.pageTitle.text = pageTitle;
}

- (void)updateAddress:(UIWebView*)aWebView
{
    NSString* location = [aWebView stringByEvaluatingJavaScriptFromString:@"location.href"];
    self.addressField.text = location;
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
    [self updateTitle:webView];
//    if(![self.addressField isFirstResponder])
//         [self updateAddress:webView];
}
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    [self updateButtons];
}

-(void)scrollViewDidScroll:(UIScrollView *)scrollView
{
//    if([scrollView contentOffset].y<20)
//        [self.navigationController.navigationBar setHidden:NO];
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    NSString* urlString = [[textField text] stringByReplacingCharactersInRange:range withString:string];
    NSURL *url = [NSURL URLWithString:urlString];
    NSString* scheme = url.scheme;
    if(!scheme) {
        if(_webView.loading) {
//            [_webView stopLoading];
        }
        [self loadRequestFromString:urlString];
    }
    return YES;
}
- (IBAction)clickCat:(UIBarButtonItem*)sender {
    [CatURLProtocol setCat:![CatURLProtocol cat]];
    [self updateCatButton];
    [_webView reload];
}

- (void) updateCatButton
{
    [_cat setImage:[CatURLProtocol cat]?[UIImage imageNamed:@"liftarn_Cat_silhouette.png"]:[UIImage imageNamed:@"silhouette.png"]];
}

- (void) updateBookmarkTimer:(NSTimer*)timer
{
    BookmarkCollectionViewController* bookmarkViewController = [timer userInfo];
    [self updateBookmark:bookmarkViewController];
}

- (void) updateBookmark:(BookmarkCollectionViewController*)bookmarkViewController
{
    if([CatURLProtocol cat]) {
        bookmarkViewController.snapShot = [self takeSnapshot:_webView];
    }
    else {
        bookmarkViewController.snapShot = nil;
        [CatURLProtocol setCat:YES];
        [self updateCatButton];
        [_webView reload];
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"bookmark"]) {
        [[self pageTitle] setHidden:YES];
        [[self addressField] setHidden:YES];
        BookmarkCollectionViewController* bookmarkViewController = segue.destinationViewController;
        [bookmarkViewController setLocation:[_webView stringByEvaluatingJavaScriptFromString:@"location.href"]];
        [bookmarkViewController setTitle:[_webView stringByEvaluatingJavaScriptFromString:@"document.title"]];
        [bookmarkViewController setDelegate:self];
        bookmarkRefresh = [NSTimer scheduledTimerWithTimeInterval:.5 target:self selector:@selector(updateBookmarkTimer:) userInfo:bookmarkViewController repeats:YES];
        [self updateBookmark:bookmarkViewController];
    }
}

+ (BOOL) isRetina
{
    if ([[UIScreen mainScreen] respondsToSelector:@selector(displayLinkWithTarget:selector:)] &&
        ([UIScreen mainScreen].scale == 2.0)) {
        return YES;
    } else {
        return NO;
    }
}

- (UIImage *) takeSnapshot:(UIView *)view
{
    int mul = [CatBrowserViewController isRetina] ? 2 : 1;
    CGSize thumbnailSize = [[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad ? CGSizeMake(190, 172) : CGSizeMake(120, 92);
    CGSize size = CGSizeMake(view.frame.size.width,view.frame.size.width/thumbnailSize.width*thumbnailSize.height);
    UIGraphicsBeginImageContextWithOptions(size, view.opaque, thumbnailSize.width*mul/view.frame.size.width);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextTranslateCTM(context,0,fmin(0,[_webView scrollView].contentOffset.y));
    [view.layer renderInContext:context];
    
    UIImage * img = UIGraphicsGetImageFromCurrentImageContext();
    
    UIGraphicsEndImageContext();
    
    return img;
}

- (void) viewWillAppear:(BOOL)animated
{
    if(bookmarkRefresh!=nil) {
        [bookmarkRefresh invalidate];
        bookmarkRefresh = nil;
    }
}

- (void) viewDidAppear:(BOOL)animated
{
    [[self pageTitle] setHidden:NO];
    [[self addressField] setHidden:NO];
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    [textField selectAll:self];
}

- (void) openLink:(NSString*) location
{
    [[self addressField] setText:location];
    [self loadRequestFromString:location];
}


@end
