/*
 * StdFileSystem.h
 *
 *  Created on: 11 September 2018
 *      Author: mikee47
 *
 * Standard File System
 *
 * IFS wrapper for POSIX file system
 *
 */

#pragma once

#include <IFS/FileSystem.h>
#include <sys/stat.h>

namespace IFS
{
/** @brief Implementation of standard mingw filing system using IFS
 */
class StdFileSystem : public IFileSystem
{
public:
	StdFileSystem()
	{
	}

	~StdFileSystem() override
	{
	}

	// IFileSystem methods
	int getinfo(Info& info) override;
	String getErrorString(int err) override;
	int opendir(const char* path, DirHandle& dir) override;
	int readdir(DirHandle dir, FileStat& stat) override;
	int closedir(DirHandle dir) override;
	int stat(const char* path, FileStat* stat) override;
	int fstat(File::Handle file, FileStat* stat) override;
	int setacl(File::Handle file, const File::ACL& acl) override
	{
		return Error::ReadOnly;
	}
	int setattr(File::Handle file, File::Attributes attr) override
	{
		return Error::ReadOnly;
	}
	int settime(File::Handle file, time_t mtime) override
	{
		return Error::ReadOnly;
	}
	File::Handle open(const char* path, File::OpenFlags flags) override;
	File::Handle fopen(const FileStat& stat, File::OpenFlags flags) override;
	int close(File::Handle file) override;
	int read(File::Handle file, void* data, size_t size) override;
	int write(File::Handle file, const void* data, size_t size) override
	{
		return Error::ReadOnly;
	}
	int lseek(File::Handle file, int offset, File::SeekOrigin origin) override;
	int eof(File::Handle file) override;
	int32_t tell(File::Handle file) override;
	int truncate(File::Handle file, size_t new_size) override;
	int flush(File::Handle file) override
	{
		return Error::ReadOnly;
	}
	int rename(const char* oldpath, const char* newpath) override
	{
		return Error::ReadOnly;
	}
	int remove(const char* path) override
	{
		return Error::ReadOnly;
	}
	int fremove(File::Handle file) override
	{
		return Error::ReadOnly;
	}
	int format() override
	{
		return Error::ReadOnly;
	}
	int check() override
	{
		return Error::NotImplemented;
	}
	int isfile(File::Handle file) override
	{
		return file >= 0;
	}

private:
	void fillStat(const struct stat& s, FileStat& stat);
};

} // namespace IFS
