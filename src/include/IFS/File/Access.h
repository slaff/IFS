/*
 * Access.h
 *
 *  Created on: 6 Jun 2018
 *      Author: mikee47
 */

#pragma once

#include "../UserRole.h"

namespace IFS
{
namespace File
{
/*
 * Role-based Access Control List.
 *
 * We only require two entries to explicitly define read/write access.
 */
struct ACL {
	/* Minimum access permissions */
	UserRole readAccess : 8;
	UserRole writeAccess : 8;
};

} // namespace File

/**
 * @brief Return a brief textual representation for an ACL
 * Suitable for inclusion in a file listing
 * @param acl
 * @retval String
 */
String toString(const File::ACL& acl);

} // namespace IFS
