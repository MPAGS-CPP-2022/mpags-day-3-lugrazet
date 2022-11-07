#include "ProcessCommandLine.hpp"
#include "CaesarCipher.hpp"
#include "TransformChar.hpp"
#include "CipherMode.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};
    for (std::size_t i{0}; i < cmdLineArgs.size(); i++) {
        std::cout << cmdLineArgs[i] << "\n" << std::endl;
    }
    ProgramSettings cmdLineSettings{
        false, // help
        false, // version
        "",  //inputFile
        "", //outputFile
        "", //cipherKey
        CipherMode::Encrypt //encrypt
    };

    // Process command line arguments
    const bool cmdLineStatus{
        processCommandLine(cmdLineArgs, cmdLineSettings)};

    // Any failure in the argument processing means we can't continue
    // Use a non-zero return value to indicate failure
    if (cmdLineStatus == false) {
        return 1;
    }

    // Handle help, if requested
    if (cmdLineSettings.help) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>] [-k <key>] [--encrypt/--decrypt]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  -k KEY           Specify the cipher KEY\n"
            << "                   A null key, i.e. no encryption, is used if not supplied\n\n"
            << "  --encrypt        Will use the cipher to encrypt the input text (default behaviour)\n\n"
            << "  --decrypt        Will use the cipher to decrypt the input text\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (cmdLineSettings.version) {
        std::cout << "0.3.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    if (!cmdLineSettings.inputFile.empty()) {
        // Open the file and check that we can read from it
        std::ifstream inputStream{cmdLineSettings.inputFile};
        if (!inputStream.good()) {
            std::cerr << "[error] failed to create istream on file '"
                      << cmdLineSettings.inputFile << "'" << std::endl;
            return 1;
        }

        // Loop over each character from the file
        while (inputStream >> inputChar) {
            inputText += transformChar(inputChar);
        }

    } else {
        // Loop over each character from user input
        // (until Return then CTRL-D (EOF) pressed)
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }
    
    // initialise CaesarCipher
    CaesarCipher cipher(cmdLineSettings.cipherKey);
    // Caesar shift the inputText
    std::string outputText{cipher.applyCipher(inputText, cmdLineSettings.mode)};

    // Output the encrypted/decrypted text to stdout/file
    if (!cmdLineSettings.outputFile.empty()) {
        // Open the file and check that we can write to it
        std::ofstream outputStream{cmdLineSettings.outputFile};
        if (!outputStream.good()) {
            std::cerr << "[error] failed to create ostream on file '"
                      << cmdLineSettings.outputFile << "'" << std::endl;
            return 1;
        }

        // Print the encrypted/decrypted text to the file
        outputStream << outputText << std::endl;

    } else {
        // Print the encrypted/decrypted text to the screen
        std::cout << outputText << std::endl;
    }

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}
