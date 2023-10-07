#include "../include/salsa20.h"

void Salsa20::quarterround(uint32_t &y0, uint32_t &y1, uint32_t &y2, uint32_t &y3){

    y1 ^= utils::rotl(y0 + y3,7);
    y2 ^= utils::rotl(y1 + y0,9);
    y3 ^= utils::rotl(y2 + y1,13);
    y0 ^= utils::rotl(y3 + y2,18);

}

void Salsa20::rowround(uint32_t (&y)[16]){

    quarterround(y[0],y[1],y[2],y[3]);
    quarterround(y[5],y[6],y[7],y[4]);
    quarterround(y[10],y[11],y[8],y[9]);
    quarterround(y[15],y[12],y[13],y[14]);

}

void Salsa20::columnround(uint32_t (&x)[16]){

    quarterround(x[0],x[4],x[8],x[12]);
    quarterround(x[5],x[9],x[13],x[1]);
    quarterround(x[10],x[14],x[2],x[6]);
    quarterround(x[15],x[3],x[7],x[11]);

}

void Salsa20::doubleround(uint32_t (&x)[16]){

    columnround(x);
    rowround(x);

}

void Salsa20::salsa20_hash(uint8_t (&xSeq)[64]){

    uint32_t x[16];
    uint32_t z[16];


    int idx;
    for(int i = 0; i < 16 ; ++i){
        idx = 4*i;
        z[i] = x[i] = utils::little_endian(xSeq[idx],xSeq[idx+1],xSeq[idx+2],xSeq[idx+3]);
    }

    for(int i = 0 ; i < 10; ++i)
        doubleround(z);

    for(int i = 0; i < 16; ++i)
        utils::inverse_little_endian(z[i] + x[i], xSeq, 4*i);

}

void Salsa20::salsa20_expansion(uint8_t *x){

    for(int i = 0; i < 4; ++i){

        x[i] = constant[i];
        x[i + 20] = constant[i + 4];
        x[i + 40] = constant[i + 8];
        x[i + 60] = constant[i + 12];

    }

    int m = (int) k.size()%32== 0;

    for(int i = 0; i < 16; ++i){

        x[i+4] = k[i];
        x[i+24] = n[i];
        x[i+44] = k[i+16*m];

    }

    salsa20_hash(*reinterpret_cast<uint8_t (*)[64]>(x));

}


void Salsa20::generate_constants(){

    std::string size = std::to_string(k.size());

    constant+= size + "-byte k";


}


std::string Salsa20::salsa20_encrypt(const std::string &m){

    std::vector<uint8_t> c = utils::hex_to_byte_vector(m);

    generate_constants();

    for(int i = 8; i < 15; ++i)
        n[i] = 0;


    uint32_t blocks = ceil((double)c.size()/64);

    uint8_t stream[64*blocks];

    for(uint32_t block = 0; block < blocks; ++block){

        salsa20_expansion(stream+(block*64));

        for(int i = 8; i < 15; ++i){

            if(n[i] < 255){
                ++n[i];
                break;

            }
        }
    }

    for(int i = 0; i < c.size(); ++i){

        c[i] ^= stream[i];

    }

    return utils::byte_vector_to_hex(c);


}

std::string Salsa20::salsa20_decrypt(const std::string &c){

    return salsa20_encrypt(c);

}


void Salsa20::set_nonce(const std::string &nonce){

    if(nonce.size() != 16){

        throw std::invalid_argument("Nonce size must be 8 bytes");

    }

    if(nonce.empty()){

        throw std::invalid_argument("Nonce cannot be empty");

    }

    n = utils::hex_to_byte_vector(nonce);

    std::vector<uint8_t> z(8);
    n.insert(n.end(), z.begin(), z.end());

}

void Salsa20::set_key(const std::string &key){

    if( key.size() != 64 && key.size() != 32){

        throw std::invalid_argument("Key must be 32 or 16 bytes");

    }

    if(key.empty()){

        throw std::invalid_argument("Key cannot be empty");
    }


    k = utils::hex_to_byte_vector(key);

}

Salsa20::Salsa20(const std::string &key, const std::string &nonce){

    set_key(key);
    set_nonce(nonce);

}

Salsa20::~Salsa20(){

    k.clear();
    std::vector<uint8_t>().swap(k);

}