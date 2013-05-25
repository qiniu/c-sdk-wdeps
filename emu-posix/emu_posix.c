/*
 ============================================================================
 Name        : emu_posix.c
 Author      : Qiniu.com
 Copyright   : 2012(c) Shanghai Qiniu Information Technologies Co., Ltd.
 Description : 
 ============================================================================
 */

#include "emu_posix.h"
#include <sys/stat.h>

Qiniu_Posix_Handle Qiniu_Posix_Open(const char* file, int oflag, int mode)
{
	Qiniu_Posix_Handle fd = CreateFileA(
		file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
	if (fd != INVALID_HANDLE_VALUE) {
		return fd;
	}
	errno = GetLastError();
	return INVALID_HANDLE_VALUE;
}

ssize_t Qiniu_Posix_Pread(Qiniu_Posix_Handle fd, void* buf, size_t nbytes, off_t offset)
{
	BOOL ret;
	DWORD nreaded = 0;
	OVERLAPPED o = {0};
	o.Offset = (DWORD)offset;
	o.OffsetHigh = (DWORD)(offset >> 32);
	ret = ReadFile(fd, buf, nbytes, &nreaded, &o);
	if (ret) {
		return nreaded;
	}
	errno = GetLastError();
	return -1;
}

static time_t fileTime2time_t(FILETIME ft)
{
	ULONGLONG ll = ft.dwLowDateTime | ((ULONGLONG)ft.dwHighDateTime << 32);
	return (time_t)((ll - 116444736000000000) / 10000000);
}

int Qiniu_Posix_Fstat(Qiniu_Posix_Handle fd, struct stat* buf)
{
	BY_HANDLE_FILE_INFORMATION fi;
	BOOL ret = GetFileInformationByHandle(fd, &fi);
	if (ret) {
		memset(buf, 0, sizeof(*buf));
		buf->st_size = fi.nFileSizeLow | ((off_t)fi.nFileSizeHigh << 32);
		buf->st_atime = fileTime2time_t(fi.ftLastAccessTime);
		buf->st_mtime = fileTime2time_t(fi.ftLastWriteTime);
		buf->st_ctime = fileTime2time_t(fi.ftCreationTime);
		return 0;
	}
	errno = GetLastError();
	return -1;
}

int Qiniu_Posix_Close(Qiniu_Posix_Handle fd)
{
	BOOL ret = CloseHandle(fd);
	if (ret) {
		return 0;
	}
	errno = GetLastError();
	return -1;
}
