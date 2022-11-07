
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ProcessCommandLine.hpp"
/*
Could test that each individual flag is being falagged appropriately. I.e.
 -h gives  the same as --help which both change the appropriate boolean. 

But it kinda just feels like a waste of time to test that? Weird. 
*/

TEST_CASE("Help flag", "CmdLine")
{
    const std::vector<std::string> args{"-h"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    processCommandLine(args, settings);
    REQUIRE(processCommandLine(args, settings) == true);
    REQUIRE(settings.help == true);
}

TEST_CASE("Help flag 2", "CmdLine")
{
    const std::vector<std::string> args{"--help"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    processCommandLine(args, settings);

    REQUIRE(settings.help == true);
}

TEST_CASE("Version flag", "CmdLine")
{
    const std::vector<std::string> args{"-v"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    processCommandLine(args, settings);

    REQUIRE(settings.version == true);
}

TEST_CASE("Input flag", "CmdLine")
{
    const std::vector<std::string> args{"-i", "inputFile.txt"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    processCommandLine(args, settings);

    REQUIRE(settings.inputFile == "inputFile.txt");
}

TEST_CASE("output flag", "CmdLine")
{
    const std::vector<std::string> args{"-o", "outputFile.txt"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    processCommandLine(args, settings);

    REQUIRE(settings.inputFile == "outputFile.txt");
}

TEST_CASE("Cipher Key", "CmdLine")
{
    const std::vector<std::string> args{"-k", "5"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    processCommandLine(args, settings);

    REQUIRE(settings.cipherKey == "5");
}

//Change the default setting else this would be redundant.
TEST_CASE("Encrypt", "CmdLine")
{
    const std::vector<std::string> args{"--encrypt"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Decrypt    //encrypt
    };
    processCommandLine(args, settings);

    REQUIRE(settings.mode == CipherMode::Encrypt);
}

TEST_CASE("Decrypt", "CmdLine")
{
    const std::vector<std::string> args{"--decrypt"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    processCommandLine(args, settings);

    REQUIRE(settings.mode == CipherMode::Decrypt);
}

TEST_CASE("Unknown Argument", "CmdLine")
{
    const std::vector<std::string> args{"-p"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    const bool cmdLineStatus{processCommandLine(args, settings)};

    REQUIRE(cmdLineStatus == false);
}

TEST_CASE("No inputfile", "CmdLine")
{
    const std::vector<std::string> args{"-i"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    const bool cmdLineStatus{processCommandLine(args, settings)};

    REQUIRE(cmdLineStatus == false);
}

TEST_CASE("No outputfile", "CmdLine")
{
    const std::vector<std::string> args{"-o"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    const bool cmdLineStatus{processCommandLine(args, settings)};

    REQUIRE(cmdLineStatus == false);
}

TEST_CASE("No key", "CmdLine")
{
    const std::vector<std::string> args{"-k"};
    ProgramSettings settings{
        false,                 // help
        false,                 // version
        "",                    //inputFile
        "",                    //outputFile
        "",                    //cipherKey
        CipherMode::Encrypt    //encrypt
    };
    const bool cmdLineStatus{processCommandLine(args, settings)};

    REQUIRE(cmdLineStatus == false);
}
