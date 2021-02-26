/**
 * FsBase.h
 * Common base for file system classes
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

#pragma once

#include "FileSystem.h"

namespace IFS
{
class FsBase
{
public:
	FsBase(IFileSystem* filesys) : fileSystem(filesys)
	{
	}

	/** @brief determine if an error occurred during operation
	 *  @retval int filesystem error code
	 */
	int getLastError()
	{
		return lastError;
	}

	String getErrorString(int err) const
	{
		return fileSystem == nullptr ? Error::toString(err) : fileSystem->getErrorString(err);
	}

	String getLastErrorString() const
	{
		return getErrorString(lastError);
	}

	FileSystem* getFileSystem() const
	{
		lastError = (fileSystem == nullptr) ? Error::NoFileSystem : FS_OK;
		return static_cast<FileSystem*>(fileSystem);
	}

protected:
	/** @brief Check file operation result and note error code
	 *  @param res result of fileXXX() operation to check
	 *  @retval bool true if operation was successful, false if error occurred
	 */
	bool check(int res)
	{
		if(res >= 0) {
			return true;
		}

		lastError = res;
		return false;
	}

protected:
	mutable int lastError{FS_OK};

private:
	IFileSystem* fileSystem;
};

} // namespace IFS
