#ifndef parsetime_h
#define parsetime_h

#include "isotime.h"
#include <string_view>

ISOTime parsetime(std::string_view str);

#endif

