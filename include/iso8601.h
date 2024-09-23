#ifndef iso8601_h
#define iso8601_h

#include "isodate.h"
#include "isotime.h"
#include <string_view>

ISODate parsedate(std::string_view str);
ISOTime parsetime(std::string_view str);

#endif
