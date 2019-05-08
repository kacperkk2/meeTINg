#ifndef SERVER_PROTOTYPE_PACKAGESIZEPARSER_H
#define SERVER_PROTOTYPE_PACKAGESIZEPARSER_H


#include <cstdint>

class PackageSizeParser {

private:
    // Disallow creating an instance of this object
    PackageSizeParser() = default;

public:
    static int32_t parse_int_32(const char (&buf)[4]);
    void static serialize_int_32(char (&buf)[4], int32_t val);

};


#endif //SERVER_PROTOTYPE_PACKAGESIZEPARSER_H
