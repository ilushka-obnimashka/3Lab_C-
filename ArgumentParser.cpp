/**
 * @file ArgumentParser.cpp
 * @brief Implementation of the ArgumentParser class.
 */

#include <getopt.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include "ArgumentParser.h"

const std::string kRED = "\033[1;31m";
const std::string kRESET = "\033[0m";
const std::string kYELLOW = "\033[33m";

/**
 * @brief Parses the command line arguments.
 *
 * This function uses getopt_long to parse the command line arguments
 * and sets the corresponding member variables.
 *
 * @return true if parsing is successful, false if help is requested.
 * @throw std::invalid_argument if there is an error in the arguments.
 */
bool ArgumentParser::Parse() {
    int opt;
    int opt_idx;
    while ((opt = getopt_long(argc_, argv_, short_option_, long_options_, &opt_idx)) != -1) {
        switch (opt) {
            case 'c':
                config_file_ = std::string(optarg);
                break;
            case 'h':
                PrintHelp();
                return false;
            default:
                throw std::invalid_argument(
                    "Usage: ./sound_processor [-h] [-c config.txt] output.wav input1.wav [input2.wav ...]");
        }
    }

    if (optind < argc_) {
        output_file_ = std::string(argv_[optind++]);
    } else {
        throw std::invalid_argument("Output file is missing");
    }

    while (optind < argc_) {
        if (input_files_.size() >= 10) {
            throw std::invalid_argument("Too many input samples");
        }
        input_files_.push_back(std::string(argv_[optind++]));
    }
    return true;
}

/**
 * @brief Gets the list of input files.
 *
 * @return A vector of input file names.
 */
std::vector<std::string> ArgumentParser::GetInputFiles() const{
    return input_files_;
}

/**
 * @brief Gets the output file name.
 *
 * @return The output file name.
 */
std::string ArgumentParser::GetOutputFile() const{
    return output_file_;
}

/**
 * @brief Gets the configuration file name.
 *
 * @return The configuration file name.
 */
std::string ArgumentParser::GetConfigFile() const{
    return config_file_;
}

/**
 * @brief Prints the help message.
 *
 * This function prints the usage information and available options
 * to the standard output.
 */
const void ArgumentParser::PrintHelp() {
    std::cout << kYELLOW;
    std::cout << "Usage: ./sound_processor [-h] [-c config.txt] output.wav input1.wav [input2.wav ...]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help                Show this help message and exit" << std::endl;
    std::cout << "  -c, --config CONFIG_FILE  Specify the configuration file" << std::endl;
    std::cout << "  output.wav                Output WAV file" << std::endl;
    std::cout << "  input1.wav                First input WAV file" << std::endl;
    std::cout << "  [input2.wav ...]          Additional input WAV files (optional)" << std::endl;
    std::cout << kRESET;
}
