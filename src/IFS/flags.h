/*
 * flags.h
 *
 *  Created on: 31 Aug 2018
 *      Author: mikee47
 */

#ifndef __IFS_FLAGS_H
#define __IFS_FLAGS_H

#include "ifstypes.h"

/** @brief convert a set of flags into a comma-separated list
 *  @param flags
 *  @param strings table of PROGMEM string pointers
 *  @param flagCount flags start at 0 and go to flagCount - 1
 *  @param buf
 *  @param bufSize
 *  @retval char* pointer to buf
 */
char* flagsToStr(uint32_t flags, PGM_P const* strings, unsigned flagCount, char* buf, size_t bufSize);

#endif // __IFS_FLAGS_H
