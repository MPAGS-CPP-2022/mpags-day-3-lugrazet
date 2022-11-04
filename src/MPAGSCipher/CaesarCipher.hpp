#include <string>
#include <vector>


class CaesarCipher {
public:
//Constructor
CaesarCipher(const std::string& key);
//variables
std::string key{0}; ///< Key for the Caesar Shift
};