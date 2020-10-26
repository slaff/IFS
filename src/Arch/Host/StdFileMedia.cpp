/*
 * StdFileMedia.cpp
 *
 *  Created on: 18 Aug 2018
 *      Author: mikee47
 */

#define _POSIX_C_SOURCE 200112L

#include "include/IFS/StdFileMedia.h"
#include <IFS/Error.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef O_BINARY
#define O_BINARY 0
#endif

#define CHECK_FILE()                                                                                                   \
	if(m_file < 0) {                                                                                                   \
		return Error::NoMedia;                                                                                          \
	}

#define SEEK(_offset)                                                                                                  \
	{                                                                                                                  \
		auto off = _offset;                                                                                            \
		if(lseek(m_file, off, SEEK_SET) != (int)off)                                                                   \
			return Error::BadExtent;                                                                                    \
	}

namespace IFS
{
StdFileMedia::StdFileMedia(const char* filename, uint32_t size, uint32_t blockSize, Media::Attributes attr)
	: Media(size, attr)
{
	m_blockSize = blockSize;

	int file = open(filename, O_BINARY | O_CREAT | (attr[Media::Attribute::ReadOnly] ? O_RDONLY : O_RDWR), 0644);
	if(file < 0) {
		debug_e("Failed to open '%s'", filename);
		return; // Error::NotFound;
	}

	int len = lseek(file, 0, SEEK_END);

	/*
	 * If file is larger than indicated size, use that as our initial media size,
	 * alternatively if we're using the media in read/write then ensure the backing
	 * file is at least as large as the maximum size indicated.
	 */
	if(len > (int)size) {
		size = len;
	} else if((int)size > len && !attr[Media::Attribute::ReadOnly]) {
		if(ftruncate(file, size) < 0) {
			::close(m_file);
			return;
		}
	}

	debug_i("Opened file media '%s', %u bytes", filename, size);

	m_size = size;
	m_file = file;
}

StdFileMedia::~StdFileMedia()
{
	if(m_file >= 0) {
		close(m_file);
	}
}

Media::Info StdFileMedia::getinfo() const
{
	Media::Info info{
		.type = Type::Disk,
		.bus = Bus::System,
		.blockSize = m_blockSize,
	};

	return info;
}

int StdFileMedia::read(uint32_t offset, uint32_t size, void* buffer)
{
	CHECK_FILE();
	FS_CHECK_EXTENT(offset, size);
	SEEK(offset);
	int n = ::read(m_file, buffer, size);
	return (n == (int)size) ? FS_OK : Error::ReadFailure;
}

int StdFileMedia::write(uint32_t offset, uint32_t size, const void* data)
{
	CHECK_FILE();
	FS_CHECK_EXTENT(offset, size);
	FS_CHECK_WRITEABLE();
	SEEK(offset);
	int n = ::write(m_file, data, size);
	return (n == (int)size) ? FS_OK : Error::WriteFailure;
}

int StdFileMedia::erase(uint32_t offset, uint32_t size)
{
	debug_i("StdFileMedia::erase(0x%08X, 0x%08X)", offset, size);

	uint8_t tmp[size];
	memset(tmp, 0xFF, size);
	return write(offset, size, tmp);
}

} // namespace IFS
