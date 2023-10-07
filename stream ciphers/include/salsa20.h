#ifndef S20_SALSA20_H
#define S20_SALSA20_H
#include <vector>
#include <string>
#include <stdexcept>
#include <stdint.h>
#include <math.h>

#include "../include/utils.h"

class Salsa20{

    private:
        std::vector<uint8_t> k; // key
        std::vector<uint8_t> n; // nonce
        std::string constant = "expand ";

        void quarterround(uint32_t &y0, uint32_t &y1, uint32_t &y2, uint32_t &y3);
        void rowround(uint32_t (&y)[16]);
        void columnround(uint32_t (&x)[16]);
        void doubleround(uint32_t (&x)[16]);

        void salsa20_hash(uint8_t (&xSeq)[64]);
        void salsa20_expansion(uint8_t *x);

        void generate_constants();

        Salsa20() = delete;

    public:

        std::string salsa20_encrypt(const std::string &m);
        std::string salsa20_decrypt(const std::string &c);
        void set_nonce(const std::string &nonce);
        void set_key(const std::string &key);
        Salsa20(const std::string &key, const std::string &nonce);
        ~Salsa20();

};

#endif //S20_SALSA20_H
