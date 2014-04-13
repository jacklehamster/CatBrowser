//
//  BookmarkCollectionViewController.m
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/4/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import "BookmarkCollectionViewController.h"
#import "BookmarkCollectionViewCell.h"
#import "BookmarkCollectionViewCellDelegate.h"
#import "NSString+MD5.h"

@interface BookmarkCollectionViewController ()<BookmarkCollectionViewCellDelegate>
{
    BookmarkCollectionViewCell* firstCell;
    UIImage* _snapShot;
    NSMutableArray* favoritesEntries;
    NSMutableDictionary* imagesCache;
}

@end

@implementation BookmarkCollectionViewController


- (void) viewDidLoad
{
    NSString *bundlePath = [[NSBundle mainBundle] resourcePath];
    NSError *error = nil;
    NSString* directory =[bundlePath stringByAppendingPathComponent:@"bookmarks"];
    if(![[NSFileManager defaultManager] fileExistsAtPath:directory]) {
        [[NSFileManager defaultManager] createDirectoryAtPath:directory withIntermediateDirectories:YES attributes:nil error:NULL];
    }
    imagesCache = [NSMutableDictionary dictionary];
    NSData* data = [NSData dataWithContentsOfFile:[directory stringByAppendingPathComponent:@"bookmark.txt"]];
    NSDictionary* dico = data ? [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error] : @{@"favorites":@[]};

    favoritesEntries = [(NSArray*)[dico objectForKey:@"favorites"] mutableCopy];
    NSDictionary* selfEntry = nil;
    for (int i=0;i<[favoritesEntries count];i++) {
        NSDictionary* entry = [favoritesEntries objectAtIndex:i];
        if([[entry objectForKey:@"location"] isEqualToString:[self location]]) {
            selfEntry = entry;
            [favoritesEntries removeObjectAtIndex:i];
            [favoritesEntries insertObject:selfEntry atIndex:0];
            break;
        }
    }
    
    if(!selfEntry) {
        selfEntry =@{
                     @"title":[self pageTitle],
                     @"location":[self location],
                     @"not-favorite":@YES
                     };
        [favoritesEntries insertObject:selfEntry atIndex:0];
    }
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return [favoritesEntries count];
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath{
    static NSString *identifier = @"Cell";
    
    BookmarkCollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:identifier forIndexPath:indexPath];

    [cell setDelegate:self];
    NSDictionary* entry = [favoritesEntries objectAtIndex:indexPath.row];
    
    if(entry) {
        cell.index = indexPath.row;
        [self refreshCell:cell];
    }
    
    return cell;
}

- (void) refreshCell:(BookmarkCollectionViewCell*)cell
{
    NSDictionary* entry = [favoritesEntries objectAtIndex:cell.index];
    BOOL bookMarked = ![entry objectForKey:@"not-favorite"];
    cell.backgroundColor = bookMarked?[UIColor colorWithWhite:.8 alpha:1]:[UIColor grayColor];
    
    UIButton *imageView = [cell imageView];
    UIActivityIndicatorView* indicator = [cell loadIndicator];
    [[cell star] setHidden:!bookMarked];
    [[cell blackStar] setHidden:bookMarked];
    [[cell label] setText:[entry objectForKey:@"title"]];
    if([[entry objectForKey:@"location"] isEqualToString:[self location]]) {
        firstCell = cell;
        [imageView setTitle:@"" forState:UIControlStateNormal];
        [imageView setBackgroundImage:_snapShot forState:UIControlStateNormal];
        [indicator setHidden:_snapShot!=nil];
    }
    else {
        [imageView setTitle:@"" forState:UIControlStateNormal];
        NSString* thumbnail = [entry objectForKey:@"thumbnail"];
        if(thumbnail==nil) {
            thumbnail = [[[entry objectForKey:@"location"] md5] stringByAppendingPathExtension:@"jpg"];
        }
        UIImage* image = [imagesCache objectForKey:thumbnail];
        if(image)
        {
            [imageView setBackgroundImage:image forState:UIControlStateNormal];
            [indicator setHidden:YES];
        }
        else {
            NSString *bundlePath = [[NSBundle mainBundle] resourcePath];
            NSString* directory =[bundlePath stringByAppendingPathComponent:@"bookmarks"];
            NSString* thumbnailPath = [directory stringByAppendingPathComponent:thumbnail];
            if([[NSFileManager defaultManager] fileExistsAtPath:thumbnailPath]) {
                NSData* data = [NSData dataWithContentsOfFile:thumbnailPath];
                image = [UIImage imageWithData:data];
                if(image) {
                    [imagesCache setObject:image forKey:thumbnail];
                    [imageView setBackgroundImage:image forState:UIControlStateNormal];
                    [indicator setHidden:YES];
                }
            }
        }
    }
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
    // If you need to use the touched cell, you can retrieve it like so
    BookmarkCollectionViewCell *cell = (BookmarkCollectionViewCell*)[collectionView cellForItemAtIndexPath:indexPath];
    NSMutableDictionary* entry = [(NSDictionary*)[favoritesEntries objectAtIndex:cell.index] mutableCopy];
    
    static NSString* notFavoriteKey = @"not-favorite";
    BOOL bookMarked = ![entry objectForKey:notFavoriteKey];
    if(bookMarked) {
        [entry setObject:@YES forKey:notFavoriteKey];
    }
    else {
        [entry removeObjectForKey:notFavoriteKey];
    }
    [favoritesEntries setObject:entry atIndexedSubscript:cell.index];
    [self saveFavorites];
    [self refreshCell:cell];
}

- (void) saveFavorites
{
    NSString *bundlePath = [[NSBundle mainBundle] resourcePath];
    NSString* directory =[bundlePath stringByAppendingPathComponent:@"bookmarks"];
    
    NSMutableArray* favorites =[NSMutableArray array];
    NSDictionary* dico = @{@"favorites":favorites};
    for(int i=0; i<[favoritesEntries count];i++) {
        NSDictionary* entry = [favoritesEntries objectAtIndex:i];
        if([entry objectForKey:@"not-favorite"]) {
            if([entry objectForKey:@"thumbnail"]) {
                NSMutableDictionary* newEntry = [entry mutableCopy];
                NSString* thumbnail = [[[entry objectForKey:@"location"] md5] stringByAppendingPathExtension:@"jpg"];
                NSString* thumbnailPath = [directory stringByAppendingPathComponent:thumbnail];
                if([[NSFileManager defaultManager] fileExistsAtPath:thumbnailPath]) {
                    [[NSFileManager defaultManager] removeItemAtPath:thumbnailPath error:nil];
                }
                [newEntry removeObjectForKey:@"thumbnail"];
                [favoritesEntries setObject:newEntry atIndexedSubscript:i];
            }
        }
        else {
            if(![entry objectForKey:@"thumbnail"]) {
                NSMutableDictionary* newEntry = [entry mutableCopy];
                NSString* thumbnail = [[[newEntry objectForKey:@"location"] md5] stringByAppendingPathExtension:@"jpg"];
                
                UIImage* image = [[entry objectForKey:@"location"] isEqualToString:[self location]]? _snapShot : [imagesCache objectForKey:thumbnail];
                if(image!=nil)
                {
                    NSData* imageData = [NSData dataWithData:UIImageJPEGRepresentation(image, 80)];
                    NSError *writeError = nil;
                    [imageData writeToFile:[directory stringByAppendingPathComponent:thumbnail] options:NSDataWritingAtomic error:&writeError];
                    [newEntry setObject:thumbnail forKey:@"thumbnail"];
                }
                [favoritesEntries setObject:newEntry atIndexedSubscript:i];
                [favorites addObject:newEntry];
            }
            else {
                [favorites addObject:entry];
            }
        }
    }
    NSError* error = nil;
    NSData* data = [NSJSONSerialization dataWithJSONObject:dico options:NSJSONWritingPrettyPrinted error:&error];
    NSString * path =[directory stringByAppendingPathComponent:@"bookmark.txt"];
    [data writeToFile:path atomically:YES];
}

- (void) setSnapShot:(UIImage *)snapShot
{
    _snapShot = snapShot;
    if(firstCell) {
        UIImageView *imageView = (UIImageView *)[firstCell viewWithTag:100];
        imageView.image = _snapShot;
        UIActivityIndicatorView* indicator = (UIActivityIndicatorView*)[firstCell viewWithTag:101];
        [indicator setHidden:_snapShot!=nil];
        NSDictionary* entry = [favoritesEntries objectAtIndex:[firstCell index]];
        NSString* thumbnail = [entry objectForKey:@"thumbnail"];
        if(thumbnail==nil) {
            thumbnail = [[[entry objectForKey:@"location"] md5] stringByAppendingPathExtension:@"jpg"];
        }
        [imagesCache setObject:_snapShot forKey:thumbnail];
        [self refreshCell:firstCell];
    }
}

- (UIImage*) snapShot
{
    return _snapShot;
}

- (void) clickedCell:(long)index
{
    NSDictionary* entry = [favoritesEntries objectAtIndex:index];
    [self.navigationController popViewControllerAnimated:YES];
    [_delegate openLink:[entry objectForKey:@"location"]];
}

@end
