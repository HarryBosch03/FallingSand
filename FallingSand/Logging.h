#pragma once

#include <iostream>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define Log(text) std::cout << "[" << __FILENAME__ << " | ln " << __LINE__ << "]  " << text << std::endl