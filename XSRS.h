// XSRS.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <stdio.h>

#define toString(x) #x

#if defined(_WIN64) || defined(WIN64) || defined(_WIN64_)
	#define PLATFORM "64-Bit Windows"
#elif defined(WIN32) || defined(_WIN32) || defined(_WIN32_)
	#define PLATFORM "32-Bit Windows"
#elif defined(ANDROID) || defined(_ANDROID_)
	#define PLATFORM "Android Device"
#elif defined(__linux__)
	#define PLATFORM "GNU/Linux"
#elif defined(__APPLE__)
	#warning "Apple platform is untested, may be have bugs!"
	#if defined(TARGET_OS_IPHONE_SIMULATOR)
		#define PLATFORM "iPhone Simulator"
	#elif defined(TARGET_OS_IPHONE)
		#define PLATFORM "iPhone Device"
	#elif defined(TARGET_OS_MAC)
		#define PLATFORM "MacOS"
	#else
		#define PLATFORM "Apple Device"
	#endif
#else
	#warning "Unknown platform, may be have bugs!"
	#define PLATFORM "Unknown"
#endif

#if defined(_MSC_VER)
	#define COMPILER "MSVC"
	#define COMPILER_VERSION _MSC_VER
#elif defined(__GNUC__)
	#define COMPILER "GNU GCC"
	#define COMPILER_VERSION __GNUC__
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
	#define COMPILER "SunCC"
	#define COMPILER_VERSION __SUNPRO_C
#else
	#define	COMPILER "Unknown"
	#define COMPILER_VERSION 0
#endif

// TODO: 在此处引用程序需要的其他标头。

#include "XSRSTable.h"