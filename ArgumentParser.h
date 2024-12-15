/**
 * @file ArgumentParser.h
 * @brief Header file for the ArgumentParser class.
 */

#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <getopt.h>
#include <vector>
#include <string>

/**
 * @brief Class ArgumentParser provides a convenient interface for parsing command line arguments using the getopt_long(3) function.
 */
class ArgumentParser {
public:
    /**
     * @brief Constructor of the ArgumentParser class.
     * @param argc Counter for the number of command line arguments.
     * @param argv Pointer to an array of single- or multi-byte strings that contains the program's arguments.
     */
    ArgumentParser(int argc, char *argv[])
        : argc_(argc), argv_(argv), short_option_("c:h"), output_file_(std::string("")), input_files_() {
        long_options_[0] = {"config", 1, nullptr, 'c'};
        long_options_[1] = {"help", 0, nullptr, 'h'};
        long_options_[2] = {nullptr, 0, nullptr, 0};
    }

    /**
     * @brief Method for parsing argv_ using getopt_long(3),
     * char * short_option_, struct option long_options_[4] - command line options that need to be supported.
     * @return true if help command not called, false otherwise.
     */
    bool Parse();

    /**
     * @brief Gets the list of input files.
     * @return A vector of input file names.
     */
    std::vector<std::string> GetInputFiles() const;

    /**
     * @brief Gets the output file name.
     * @return The output file name.
     */
    std::string GetOutputFile() const;

    /**
     * @brief Gets the configuration file name.
     * @return The configuration file name.
     */
    std::string GetConfigFile() const;

    /**
     * @brief Method for printing the help message. Will be called when the user runs the program with the -h or --help option.
     */
    const void PrintHelp();

private:
    int argc_;                      ///< Number of command line arguments.
    char **argv_;                   ///< Array of command line arguments.
    const char *short_option_;      ///< Short options string.
    struct option long_options_[3]; ///< Array of long options.

    std::vector<std::string> input_files_; ///< Vector of input file names.
    std::string config_file_;              ///< Configuration file name.
    std::string output_file_;              ///< Output file name.
};

#endif // ARGUMENTPARSER_H
