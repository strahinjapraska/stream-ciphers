#include "include/salsa20.h"
#include "include/utils.h"
#include <iostream>

int main(){


    const std::string pt = "Salsa20 implementation";
    const std::string key =  "48d60551bfa4b387e67516600cadc1c595126acd561025acf4258520d01d8010";  // generated with OpenSSL rand
    const std::string nonce =  "4f0bdfc3b87cb2c7";

    Salsa20 s20 = Salsa20(key,nonce);

    std::string c = s20.salsa20_encrypt(utils::str_to_hex(pt));


    std::cout<<c<< std::endl;


    std::cout<< utils::hex_to_str(s20.salsa20_decrypt(c))<<std::endl;

    return 0;
}