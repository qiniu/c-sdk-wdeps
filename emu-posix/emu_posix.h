/*
 ============================================================================
 Name        : emu_posix.h
 Author      : Qiniu.com
 Copyright   : 2012(c) Shanghai Qiniu Information Technologies Co., Ltd.
 Description : 
 ============================================================================
 */
#ifndef QINIU_EMU_POSIX_H
#define QINIU_EMU_POSIX_H

#include <windows.h>
#include <sys/types.h>

/*============================================================================*/
/* type ssize_t */

#ifndef _W64
#define _W64
#endif

typedef _W64 int ssize_t;

/*============================================================================*/
/* type Qiniu_File */

#define Qiniu_Posix_Handle			HANDLE
#define Qiniu_Posix_InvalidHandle	INVALID_HANDLE_VALUE

Qiniu_Posix_Handle Qiniu_Posix_Open(const char* file, int oflag, int mode);
ssize_t Qiniu_Posix_Pread(Qiniu_Posix_Handle fd, void* buf, size_t nbytes, off_t offset);
int Qiniu_Posix_Fstat(Qiniu_Posix_Handle fd, struct stat* buf);
int Qiniu_Posix_Close(Qiniu_Posix_Handle fd);

/*============================================================================*/

#endif /* QINIU_EMU_POSIX_H */

