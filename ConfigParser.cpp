#include "ConfigParser.h"
#include "Converter.h"

ConfigParser::ConfigParser(const std::string& configFileName) : configFileName(configFileName) {
    initializeRegex();
}

void ConfigParser::initializeRegex() {
    muteRegex = std::regex(R"(mute\s+(\d+)\s+(\d+))");
    mixRegex = std::regex(R"(mix\s+\$(\d+)\s+(\d+))");
    distortionRegex = std::regex(R"(distortion\s+([0-9]+(\.[0-9]+)?))");
}

std::queue<Converter*> ConfigParser::parse(const std::vector<std::string>& inputFiles) {
    std::queue<Converter*> converters;
    std::ifstream configFile(configFileName);
    if (!configFile.is_open()) {
        std::cerr << "\033[31mFailed to open the configuration file\033[0m\n";
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(configFile, line)) {
        std::smatch matches;

        if (std::regex_search(line, matches, muteRegex)) {
            uint32_t left = std::stoi(matches[1]);
            uint32_t right = std::stoi(matches[2]);
            converters.push(createMuteConverter(left, right));
        } else if (std::regex_search(line, matches, mixRegex)) {
            uint32_t fileIndex = std::stoi(matches[1]);
            uint32_t start = std::stoi(matches[2]);
            if (fileIndex >= inputFiles.size()) {
                std::cerr << "\033[31mInvalid file index in mix command\033[0m\n";
                exit(EXIT_FAILURE);
            }
            converters.push(createMixConverter(start, inputFiles[fileIndex]));
        } else if (std::regex_search(line, matches, distortionRegex)) {
            float gain = std::stof(matches[1]);
            converters.push(createDistortionConverter(gain));
        } else if (!line.empty() && line[0] != '#') {
            std::cerr << "\033[31mUnknown command in configuration file\033[0m\n";
            exit(EXIT_FAILURE);
        }
    }

    return converters;
}

Converter* ConfigParser::createMuteConverter(uint32_t left, uint32_t right) {
    return new MuteOption(left, right);
}

Converter* ConfigParser::createMixConverter(uint32_t start, const std::string& srcFile) {
    return new MixOption(srcFile, start);
}

Converter* ConfigParser::createDistortionConverter(float gain) {
    return new Distortion(gain);
}
