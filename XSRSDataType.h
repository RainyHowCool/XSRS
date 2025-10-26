#pragma once

#include <stdlib.h>

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
#ifdef _WIN32
	typedef long long i64;
	typedef unsigned long long u64;
#else
	typedef long i64;
	typedef unsigned long u64;
#endif
typedef size_t usize;
typedef size_t ptr;
typedef u8 boolean;
#define True 1
#define False 0
