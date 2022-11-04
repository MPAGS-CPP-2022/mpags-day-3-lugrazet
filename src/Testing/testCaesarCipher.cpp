//Testing that TransformChar works

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CaesarCipher.hpp"

/*
PROBLEM WITH THIS: 
I want to check that it leaves the key at initial value when it's given a false string 
(idk how to check it's exiting and cerr-ing but that would also work) 
i.e. at 0. But the key information is kept private
Might want to check that CaesarCipher.applyCaesar does what expected on a known string but that feels like a silly workaround.


A similar check i'd like to do would be cipher('x').key_ == cipher(x).key_ for key being any single digit character.
i.e. check that std::stoul is working and we aren't running into weird problems.
Idk a world where that would change but we assume it's working so its nicer to 
just have it always checked it takes like no time at all to run. 
Would probably do this for switch case '0', ..., '9' ?. So can steal the structure from '0' -> 'ONE' in TransformChar.  


TEST_CASE("Reject non-numerical key", "[numerics]"){
    const std::string ab{"A"};
    REQUIRE( CaesarCipher(ab). == 0 );
}
*/

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
