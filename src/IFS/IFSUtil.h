/*
 * IFSUtil.h
 *
 *  Created on: 10 Sep 2018
 *      Author: Mike
 *
 *  Various bits for file system implementations to use
 */

#ifndef __IFS_UTIL_H_
#define __IFS_UTIL_H_

#include "IFSError.h"

/* Paths equal to "/" or "" are empty and considered equivalent to nullptr.
 * Methods or functions can use this macro to resolve these for simpler parsing.
 */
#define FS_CHECK_PATH(_path)                                                                                           \
	if(_path) {                                                                                                        \
		if(*_path == '/')                                                                                              \
			++_path;                                                                                                   \
		if(*_path == '\0')                                                                                             \
			_path = nullptr;                                                                                           \
	}

#endif // __IFS_UTIL_H_
