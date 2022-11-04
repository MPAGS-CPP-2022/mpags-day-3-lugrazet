#include <string>
#include <vector>
#include <iostream>

    class CaesarCipher {
    public:
        //Members
        std::size_t key_;
        //Constructors
        explicit CaesarCipher(const std::size_t key);

        explicit CaesarCipher(const std::string key_string);
};