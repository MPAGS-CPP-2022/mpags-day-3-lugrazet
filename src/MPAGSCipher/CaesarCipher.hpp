#include <string>
#include <vector>
#include <iostream>

class CaesarCipher {
public:
    //Members
    std::string applyCipher(const std::string in_str, const bool encrypt)
    {
        const std::size_t truncatedKey{key_ % alphabet_.size()};
        char processedChar{'x'};
        std::string out_str{'x'};
        for (const auto& origChar : in_str) {
            // For each character in the input text, find the corresponding position in
            // the alphabet by using an indexed loop over the alphabet container
            for (size_t i{0}; i < alphabet_.size(); ++i) {
                if (origChar == alphabet_[i]) {
                    // Apply the appropriate shift (depending on whether we're encrypting
                    // or decrypting) and determine the new character
                    // Can then break out of the loop over the alphabet
                    if (encrypt) {
                        processedChar = alphabet_[(i + truncatedKey) % alphabet_.size()];
                    } else {
                        processedChar = alphabet_[(i + alphabet_.size() - truncatedKey) %
                                                alphabet_.size()];
                    }
                    break;
                }
            }
            // Add the new character to the output text
            return out_str += processedChar;
        }
        return out_str;
    };
    
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