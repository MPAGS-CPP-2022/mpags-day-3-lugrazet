#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

#include <string>
#include <vector>

struct ProgramSettings {
    bool help; // 1 for help requested, 0 otherwise
    bool version; // 1 for version output requested, 0 otherwise
    std::string inputFile; 
    std::string outputFile;
    std::string cipherKey;
    bool encrypt; // 0 for decryption requested, 1 for encryption. (Set as encrypt by default for some reason?)
};

bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
                        ProgramSettings& cmdLinePS);

#endif    // MPAGSCIPHER_PROCESSCOMMANDLINE_HPP