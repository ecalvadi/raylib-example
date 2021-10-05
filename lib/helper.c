//
//  helper.c
//  ray-lib-example
//
//  Created by Kevin Ladan on 4/4/20.
//  Copyright © 2020 Kevin Ladan. All rights reserved.
//

#include "helper.h"
#include <CoreFoundation/CoreFoundation.h>

char * CFStringCopyUTF8String(CFStringRef aString)
{
    if (aString == NULL)
    {
        return NULL;
    }
  
    CFIndex length = CFStringGetLength(aString);
    CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
    
    char *buffer = (char *)malloc(maxSize);
    
    if (CFStringGetCString(aString, buffer, maxSize, kCFStringEncodingUTF8))
    {
        return buffer;
    }
    
    return buffer;
}

char * file_path(CFStringRef file)
{
    CFArrayRef fileComponents = CFStringCreateArrayBySeparatingStrings(NULL, file, CFSTR("."));
    
    if (CFArrayGetCount(fileComponents) > 2)
    {
        printf("unrecognize file\n");
        return NULL;
    }
    
    CFStringRef fileName = (CFStringRef) CFArrayGetValueAtIndex(fileComponents, 0);
    CFStringRef fileExtension = (CFStringRef) CFArrayGetValueAtIndex(fileComponents, 1);
    
    //  get a reference to the main bundle
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    if( mainBundle == NULL )
    {
        printf("unable to get main bundle\n");
        return NULL;
    }
    
    //  get the CFURL reference to the file we're interested in
    CFURLRef dataFileURL = CFBundleCopyResourceURL(mainBundle, fileName, fileExtension, NULL);
    if( dataFileURL == NULL )
    {
        printf("unable to locate data file\n");
        return NULL;
    }
    
    //  since fopen works with paths, we need to convert CFURL reference to path
    CFStringRef path;
    if( !CFURLCopyResourcePropertyForKey(dataFileURL, kCFURLPathKey, &path, NULL))
    {
        printf("unable to get file path\n");
        return NULL;
    }
    
    return CFStringCopyUTF8String(path);
}
