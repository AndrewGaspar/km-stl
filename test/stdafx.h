// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Headers for CppUnitTest
#include "CppUnitTest.h"

// TODO: reference additional headers your program requires here

// we need the MSVC STL to work alongside our implementation of the STL in order
// for the test framework to work. Therefore, refer to it as kstd instead of std
#define _KSTD kstd