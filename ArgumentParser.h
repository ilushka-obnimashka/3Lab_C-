#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <getopt.h>
#include <vector>
#include <string>


/** @brief class ArgumentParser : ArgumentParser provides a convenient interface for parsing command line arguments using the getopt_long(3) function.
 */
class ArgumentParser {
public:
    /** @brief Constructor of the ArgumentParser class.
     * @param argc counter the number of command line arguments.
     * @param argv pointer to an array of single- or multi-byte strings that contains the program's arguments.
     */
    ArgumentParser(int argc, char *argv[])
        : argc_(argc), argv_(argv), short_option_("c:h"), output_file_(std::string("")), input_files_() {
        long_options_[0] = {"config", 1, nullptr, 'c'};
        long_options_[1] = {"help", 0, nullptr, 'h'};;
        long_options_[2] = {nullptr, 0, nullptr, 0};
    }

    /**
     * @brief Method for parsing **argv_ using getopt_long(3),
     * char * short_option_, struct option long_options_[4] -command line options that need to be supported.
     * @return true - if help command not called, false - otherwise.
     */
    bool Parse();

    /**
     * @return std::vector<std::string> input_samples_ .
     */
    std::vector<std::string> GetInputFiles() const;

    /**
     * @return std::string output_file_ .
     */
    std::string GetOutputFile() const;

    /**
     * @return std::string config_file_ .
     */
    std::string GetConfigFile() const;

    /**
     * @brief method for printing help message. Will be called when the user runs the program with the -h or --help option.
     */
    const void PrintHelp();

private:
    int argc_;
    char **argv_;
    const char *short_option_;
    struct option long_options_[3];

    std::vector<std::string> input_files_;
    std::string config_file_;
    std::string output_file_;
};

#endif //ARGUMENTPARSER_H
