//
// Created by Tomasz Suchodolski on 14.04.19.
//

#include "PackageSizeParser.h"

int32_t PackageSizeParser::parse_int_32(const char (&buf)[4])
{
    uint8_t u0 = buf[0], u1 = buf[1], u2 = buf[2], u3 = buf[3];
    uint32_t uval = u0 | (u1 << 8) | (u2 << 16) | (u3 << 24);
    return uval;
}