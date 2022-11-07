#include "ProcessCommandLine.hpp"

#include <iostream>
#include <string>
#include <vector>

/*
Takes two inputs, a referenced string of arguments and referended Settings structure.
The settings structure has already been initialised with the default settings, and 
this program then checks each element of the argument string, evaluates it, 
then changes data members in the settings appropriately.

Returns a boolean "processStatus", True if nothing goes wrong. False if otherwise
    Otherwise: no input file name given after -i
               no output file name given after -o
               inappropriate caesar key given after -k
               unknown argument given in.

The command line arguments affect the settings as follows:

[-h/--help] [--version] [-i <file>] [-o <file>] [-k <key>] [--encrypt/--decrypt]
-h|--help        bool ProgramSettings.help = true 
--version        bool ProgramSettings.version = true
-i FILE          string ProgramSettings.inputFile = argument after this one
-o FILE          string ProgramSettings.outputFile = argument after this one
-k KEY           string ProgramSettings.cipherKey = argument after this one
--encrypt        CipherMode ProgramSettings.mode = CipherMode::Encrypt 
--decrypt        CipherMode ProgramSettings.mode = CipherMode::Decrypt 
*/

bool processCommandLine(const std::vector<std::string>& cmdLineArgs, 
                        ProgramSettings& cmdLineSettings)
{
    // Status flag to indicate whether or not the parsing was successful
    bool processStatus{true};

    // Process the arguments - ignore zeroth element, as we know this to be
    // the program name and don't need to worry about it
    const std::size_t nCmdLineArgs{cmdLineArgs.size()};
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
            // Set the indicator and terminate the loop
            cmdLineSettings.help = true;
            break;
        } else if (cmdLineArgs[i] == "--version") {
            // Set the indicator and terminate the loop
            cmdLineSettings.version = true;
            break;
        } else if (cmdLineArgs[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // Set the flag to indicate the error and terminate the loop
                processStatus = false;
                break;
            } else {
                // Got filename, so assign value and advance past it
                cmdLineSettings.inputFile = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // Set the flag to indicate the error and terminate the loop
                processStatus = false;
                break;
            } else {
                // Got filename, so assign value and advance past it
                cmdLineSettings.outputFile = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "-k") {
            // Handle cipher key option
            // Next element is the key unless -k is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -k requires a positive integer argument"
                          << std::endl;
                // Set the flag to indicate the error and terminate the loop
                processStatus = false;
                break;
            } else {
                // Got the key, so assign the value and advance past it
                cmdLineSettings.cipherKey = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "--encrypt") {
            cmdLineSettings.mode = CipherMode::Encrypt;
        } else if (cmdLineArgs[i] == "--decrypt") {
            cmdLineSettings.mode = CipherMode::Decrypt;
        } else {
            // Have encoutered an unknown flag, output an error message,
            // set the flag to indicate the error and terminate the loop
            std::cerr << "[error] unknown argument '" << cmdLineArgs[i]
                      << "'\n";
            processStatus = false;
            break;
        }
    }
    return processStatus;
}