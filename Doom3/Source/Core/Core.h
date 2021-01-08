#pragma once

#ifdef _DEBUG
#define DEBUG_VERSION
#else
#define BUILD_VERSION
#endif

#ifdef DEBUG_VERSION

#ifdef _WIN32 || _WIN64
#define CURRENTPATH "C:/Doom3FromScratch/Doom3/"

#elif __APPLE__
#define CURRENTPATH "/Users/sungjinkang/openglstudy/glfwStudys/"


#endif

#else

#endif

#define  GET_RALATIVE_PATH(path) CURRENTPATH path
#include "Assert.h"