#ifndef S20_UTILS_H
#define S20_UTILS_H
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <iomanip>

namespace utils{

    bool isHexString(const std::string &str);
    std::vector<uint8_t> hex_to_byte_vector(const std::string &hex);
    std::string byte_vector_to_hex(const std::vector<uint8_t> v);
    std::string str_to_hex(const std::string &s);
    std::string hex_to_str(const std::string &hex);

    uint32_t rotl(const uint32_t value, const int shift);

    uint32_t little_endian(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3);
    void inverse_little_endian(uint32_t littleEndianValue, uint8_t *b, int index);


}
#endif //S20_UTILS_H
