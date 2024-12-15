#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <regex>
#include <stdexcept>
#include "converter.h"

/**
* @brief class CongigParser provides a convenient interface for parsing config file using std::regex.
*/
class ConfigParser {
public:
    ConfigParser(std::string& configFileName);
    std::queue<Converter*> parse(const std::vector<std::string>& inputFiles);

private:
    std::string configFileName;
    std::regex muteRegex;
    std
};
#endif //CONFIGPARSER_H