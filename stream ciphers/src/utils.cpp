#include "../include/utils.h"


namespace utils{
    bool is_hex_string(const std::string& str){
        volatile bool isValid = true;

        for(char c: str){
            if(!std::isxdigit(c)){
                isValid = false;
            }
        }

        return isValid;

    }

    uint32_t rotl(const uint32_t value, const int shift){
        return value << shift | value >> (32-shift);
    }

    uint32_t little_endian(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3){
        return b0 + (1<<8)*b1 + (1<<16)*b2 + (1<<24)*b3;
    }

    void inverse_little_endian(uint32_t little_endian, uint8_t *b, int index){

        b[index] = little_endian;
        b[index+1] = little_endian >> 8;
        b[index+2] = little_endian >> 16;
        b[index+3] = little_endian >> 24;

    }

    std::vector<uint8_t> hex_to_byte_vector(const std::string &hex){

        if(!is_hex_string(hex)){

            throw std::invalid_argument("Must be hex string");

        }

        if(hex.size() %2 != 0){

            throw std::invalid_argument("Must be even sized string");
        }

        std::vector<uint8_t> result_vec;

        for(size_t i = 0 ; i < hex.size(); i+=2){

            std::string hex_byte = hex.substr(i,2);
            uint8_t byte = static_cast<uint8_t>(std::stoi(hex_byte, nullptr, 16));
            result_vec.push_back(byte);
        }


        return result_vec;
    }

    std::string byte_vector_to_hex(std::vector<uint8_t> v){

        std::stringstream hexss;



        for( size_t i = 0;  i < v.size(); ++i){

            hexss <<std::setw(2)<<std::setfill('0')<< std::hex << static_cast<int>(v[i]);

        }


        return hexss.str();

    }

    std::string str_to_hex(const std::string &s){

        std::stringstream hexss;

        hexss << std::hex << std::setfill('0');

        for (char c: s){
            hexss << std::setw(2) << static_cast<int>(static_cast<unsigned char>(c));
        }

        return hexss.str();
    }

    std::string hex_to_str(const std::string &hex){

        std::string s;

        for( size_t i = 0 ; i < hex.size(); i+=2){
            std::string hex_byte = hex.substr(i,2);
            char c = static_cast<char>(std::stoi(hex_byte, nullptr , 16));
            s+=c;
        }

        return s;
    }
}