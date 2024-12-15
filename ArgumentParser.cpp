#include "ArgumentParser.h"
#include <getopt.h>
#include <string>
#include <iostream>
#include <stdexcept>

const std::string kRED = "\033[1;31m";
const std::string kRESET = "\033[0m";
const std::string kYELLOW = "\033[33m";

void ArgumentParser::Parse() {
    int opt;
    int opt_idx;
    while ((opt = getopt_long(argc_, argv_, short_option_, long_options_, &opt_idx)) != -1) {
        switch (opt) {
            case 'c':
                config_file_ = std::string(optarg);
                break;
            case 'h':
                PrintHelp();
                exit(1);
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
}

std::vector<std::string> ArgumentParser::GetInputFiles() const{
    return input_files_;
}

std::string ArgumentParser::GetOutputFile() const{
    return output_file_;
}

std::string ArgumentParser::GetConfigFile() const{
    return config_file_;
}

const void ArgumentParser::PrintHelp() {
    std::cout << kYELLOW;
    std::cout << "Usage: ./sound_processor [-h] [-c config.txt] output.wav input1.wav [input2.wav ...]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help                Show this help message and exit" << std::endl;
    std::cout << "  -c, --config CONFIG_FILE  Specify the configuration file" << std::endl;
    std::cout << "  output.wav                Output WAV file" << std::endl;
    std::cout << "  input1.wav                First input WAV file" << std::endl;
    std::cout << "  [input2.wav ...]         Additional input WAV files (optional)" << std::endl;
    std::cout << kRESET;
}
