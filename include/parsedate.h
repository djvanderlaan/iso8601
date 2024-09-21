#ifndef parsedate_h
#define parsedate_h

#include "isodate.h"
#include <string_view>

ISODate parsedate(std::string_view str);

#endif
