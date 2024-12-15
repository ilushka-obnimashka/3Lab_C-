
#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <regex>
#include <stdexcept>
#include "Converter.h"

/**
* @brief class ConfigParser provides a convenient interface for parsing config file using std::regex.
*/

class ConfigParser {
public:
    ConfigParser(const std::string& config_file_name);
    std::queue<Converter*> parse(const std::vector<std::string>& input_files);

private:
    std::string configFileName;
    std::regex muteRegex;
    std::regex mixRegex;
    std::regex distortionRegex;

    void initializeRegex();
    Converter* createMuteConverter(uint32_t left, uint32_t right);
    Converter* createMixConverter(uint32_t start, const std::string& src_file);
    Converter* createDistortionConverter(float gain);
};

#endif // CONFIGPARSER_H
