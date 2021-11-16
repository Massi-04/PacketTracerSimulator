#pragma once

#include <string>
#include "Math/Math.h"

typedef unsigned int uint;
typedef unsigned char uchar;

#ifdef ENGINE_DEBUG
#include <iostream>
#define LOG(x) std::cout << x
#else
#define LOG(x)
#endif // ENGINE_DEBUG