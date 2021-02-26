/**
 * Access.cpp
 *
 * Created on: 6 Jun 2018
 *
 * Copyright 2019 mikee47 <mike@sillyhouse.net>
 *
 * This file is part of the IFS Library
 *
 * This library is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, version 3 or later.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this library.
 * If not, see <https://www.gnu.org/licenses/>.
 *
 ****/

#include "include/IFS/Access.h"

namespace IFS
{
String getAclString(const IFS::ACL& acl)
{
	String s;
	s += IFS::getChar(acl.readAccess);
	s += IFS::getChar(acl.writeAccess);
	return s;
}

} // namespace IFS

String toString(const IFS::ACL& acl)
{
	String s;
	s += toString(acl.readAccess);
	s += '/';
	s += toString(acl.writeAccess);
	return s;
}
