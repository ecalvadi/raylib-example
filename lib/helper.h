//
//  helper.h
//  ray-lib-example
//
//  Created by Kevin Ladan on 4/4/20.
//  Copyright © 2020 Kevin Ladan. All rights reserved.
//

#ifndef helper_h
#define helper_h

#include <stdio.h>
#include <CoreFoundation/CFString.h>
/**
 *  Get absolute path of file
 *
 *  @return  Returns a file pointer to the file "data.txt" if the file can be opened.  If the
 *          file cannot be opened, or an error occurs, returns \p NULL.
 */
extern char * file_path(CFStringRef file);

/**
 *  C string from a CFString
 *
 *  @param  aString  The CFString to convert
 *
 *  @return  Returns a C string from the contents of the CFString provided.
 */
extern char * CFStringCopyUTF8String(CFStringRef aString);

#endif /* helper_h */
