#include "ArgumentParser.h"
#include "WAVHeader.h"
#include <iostream>

int main(int argc, char* argv[]) {
    ArgumentParser parser(argc, argv);

    try {
        if (!parser.Parse()) {
            std::cout << "Help requested. Usage: \n";
            std::cout << "./3Lab_C++ [-h] [-c config.txt] output.wav input1.wav [unput2.wav ...]\n";
            return 0;
        }
        std::string config_file = parser.GetConfigFile();
        std::string output_file = parser.GetOutputFile();
        std::vector<std::string> input_samples = parser.GetInputSamples();

        std::cout << "Config file: " << (config_file.empty() ? "None" : config_file) << std::endl;
        std::cout << "Outputfile: " << output_file << std::endl;
        std::cout << "Input samples: ";
        for (const auto& sample : input_samples) {
            std::cout << sample << " ";
        }
        std::cout << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

