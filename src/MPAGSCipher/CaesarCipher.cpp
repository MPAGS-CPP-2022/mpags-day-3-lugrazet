#include "CaesarCipher.hpp"

#include <iostream>
#include <string>
#include <vector>

CaesarCipher::CaesarCipher(const std::size_t key) : key_{key}
{
}

CaesarCipher::CaesarCipher(const std::string key_string): key_{0}
{
    if (!key_string.empty()) {
        // Before doing the conversion we should check that the string contains a
        // valid positive integer.
        // Here we do that by looping through each character and checking that it
        // is a digit. What is rather hard to check is whether the number is too
        // large to be represented by an unsigned long, so we've omitted that for
        // the time being.
        // (Since the conversion function std::stoul will throw an exception if the
        // string does not represent a valid unsigned long, we could check for and
        // handled that instead but we only cover exceptions very briefly on the
        // final day of this course - they are a very complex area of C++ that
        // could take an entire course on their own!)
        for (const auto& elem : key_string) {
            if (!std::isdigit(elem)) {
                std::cerr
                    << "[error] cipher key must be an unsigned long integer for Caesar cipher,\n"
                    << "        the supplied key (" << key_string
                    << ") could not be successfully converted" << std::endl;
                return;
            }
        }
        key_ = std::stoul(key_string);
    }
    return;
}


std::string CaesarCipher::applyCipher(const std::string in_str, const CipherMode mode)
{
    const std::size_t truncatedKey{key_ % alphabet_.size()};
    char processedChar;
    std::string out_str;
    for (const auto& origChar : in_str) {
        // For each character in the input text, find the corresponding position in
        // the alphabet by using an indexed loop over the alphabet container
        for (size_t i{0}; i < alphabet_.size(); ++i) {
            if (origChar == alphabet_[i]) {
                // Apply the appropriate shift (depending on whether we're encrypting
                // or decrypting) and determine the new character
                // Can then break out of the loop over the alphabet
                switch (mode) {
                    case CipherMode::Encrypt:
                        processedChar =
                            alphabet_[(i + truncatedKey) % alphabet_.size()];
                        break;
                    case CipherMode::Decrypt:
                        processedChar =
                        alphabet_[(i + alphabet_.size() - truncatedKey) % alphabet_.size()];
                        break;
                }
            }
        }
        // Add the new character to the output text
        out_str += processedChar;
    }
    return out_str;
}