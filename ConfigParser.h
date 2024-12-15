/**
 * @file ConfigParser.h
 * @brief Header file for the ConfigParser class.
 */

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
 * @brief Class ConfigParser provides a convenient interface for parsing a configuration file using std::regex.
 */
class ConfigParser {
public:
    /**
     * @brief Constructor for the ConfigParser class.
     * @param config_file_name The name of the configuration file to parse.
     */
    ConfigParser(const std::string& config_file_name);

    /**
     * @brief Parses the configuration file and creates a queue of Converter objects.
     * @param input_files A vector of input file names.
     * @return A queue of Converter objects created based on the configuration file.
     */
    std::queue<Converter*> Parse(const std::vector<std::string>& input_files);

private:
    std::string configFileName; ///< The name of the configuration file.
    std::regex muteRegex;       ///< Regular expression for the mute command.
    std::regex mixRegex;        ///< Regular expression for the mix command.
    std::regex distortionRegex; ///< Regular expression for the distortion command.

    /**
     * @brief Initializes the regular expressions used for parsing the configuration file.
     */
    void InitializeRegex();
};

#endif // CONFIGPARSER_H
