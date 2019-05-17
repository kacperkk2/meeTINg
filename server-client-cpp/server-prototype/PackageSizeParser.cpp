#include "PackageSizeParser.h"

int32_t PackageSizeParser::parse_int_32(const char (&buf)[4])
{
    uint8_t u0 = buf[3], u1 = buf[2], u2 = buf[1], u3 = buf[0];
    uint32_t uval = u0 | (u1 << 8) | (u2 << 16) | (u3 << 24);
    return uval;
}

void PackageSizeParser::serialize_int_32(char (&buf)[4], int32_t val)
{
    uint32_t uval = val;
    buf[3] = uval;
    buf[2] = uval >> 8;
    buf[1] = uval >> 16;
    buf[0] = uval >> 24;
}
