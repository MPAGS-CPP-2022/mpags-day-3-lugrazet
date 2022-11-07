//Testing that TransformChar works

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CaesarCipher.hpp"

/*
Tests: should be mostly easy to understand but here's some information.
Test 1: Checks that reading in a negative key in a string 
    leaves the key at 0 as expected. [Don't need to check entering in -5 immediately, 
    because the input is either an unsigned int the string which this checks]

Test 2-3 checks the caesar is occuring as we expect theoretically.
Test 4 checks encrypt(decrypt) leavse the string untouched. 

*/
TEST_CASE("Reject non-numerical key", "[CaesarCipher]")
{
    const std::vector<char> alphabet_ = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    CaesarCipher cipher{std::string{"-5"}};
    for (std::size_t j{0}; j < alphabet_.size(); j++) {
        std::string s{alphabet_[j]};
        REQUIRE(cipher.applyCipher(s, CipherMode::Encrypt) == s);
        REQUIRE(cipher.applyCipher(s, CipherMode::Decrypt) == s);
    }
}

TEST_CASE("Encrpyting as expected", "[CaesarCipher]")
{
    const std::vector<char> alphabet_ = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    for (std::size_t i{0}; i < 26; i++) {
        CaesarCipher cipher{i};
        for (std::size_t j{0}; j < alphabet_.size(); j++) {
            std::string s{alphabet_[j]};
            std::string str2{alphabet_[(j + i) % alphabet_.size()]};
            REQUIRE(cipher.applyCipher(s, CipherMode::Encrypt) == str2);
        }
    }
}

TEST_CASE("Decrypting as expected", "[CaesarCipher]")
{
    const std::vector<char> alphabet_ = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    for (std::size_t i{0}; i < alphabet_.size(); i++) {
        CaesarCipher cipher{i};
        for (std::size_t j{0}; j < alphabet_.size(); j++) {
            std::string s{alphabet_[j]};
            std::string str2{
                alphabet_[(j + alphabet_.size() - i) % alphabet_.size()]};
            REQUIRE(cipher.applyCipher(s, CipherMode::Decrypt) == str2);
        }
    }
}

// - (Should be trivial if the other two are working fine)? oops
TEST_CASE("Decryption(Encryption) == Original", "[CaesarCipher]")
{
    std::string test{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    for (std::size_t i{0}; i < 26; i++) {
        CaesarCipher cipher{i};
        REQUIRE(
            cipher.applyCipher(cipher.applyCipher(test, CipherMode::Encrypt),
                               CipherMode::Decrypt) == test);
    }
}
