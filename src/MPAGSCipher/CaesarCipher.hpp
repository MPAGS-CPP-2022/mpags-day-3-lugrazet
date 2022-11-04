#ifndef MPAGSCIPHER_CAESARCIPHER_HPP
#define MPAGSCIPHER_CAESARCIPHER_HPP

#include <string>
#include <vector>
#include <iostream>
#include "CipherMode.hpp"

class CaesarCipher {
  public:
    //Members
    std::string applyCipher(const std::string in_str, const CipherMode mode);
    

    //Constructors
    explicit CaesarCipher(const std::size_t key);
    explicit CaesarCipher(const std::string key_string);

  private:
    //Members
    std::size_t key_;
    const std::vector<char> alphabet_ = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
};
#endif    // MPAGSCIPHER_CAESARCIPHER_HPP