/**
 * @file Converter.h
 * @brief Header file for the Converter class and its derived classes.
 */

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "ReaderWAV.h"
#include "WriterWAV.h"

const std::string kRESET = "\033[0m";
const std::string kGREEN = "\033[32m";
const std::string kRED = "\033[1;31m";
const std::string kYELLOW = "\033[33m";

/**
 * @brief Base class for audio converters.
 */
class Converter {
public:
    /**
     * @brief Default constructor.
     */
    Converter() = default;

    /**
     * @brief Default destructor.
     */
    virtual ~Converter() = default;

    /**
     * @brief Pure virtual function to convert audio files.
     * @param input_file The input WAV file.
     * @param output_file The output WAV file.
     * @param reader The ReaderWAV object to read the input file.
     * @param writer The WriterWAV object to write the output file.
     */
    virtual void Convert(std::string input_file, std::string output_file) = 0;

    /**
     * @brief Pure virtual function to display help information.
     */
    virtual void help() const = 0;
};

/**
 * @brief Class for muting a section of an audio file.
 */
class MuteOption : public Converter {
public:
    MuteOption(uint32_t left, uint32_t right);

    void Convert(std::string input_file, std::string output_file) override;

    /**
     * @brief Displays help information for the MuteOption converter.
     */
    void help() const override {
        std::cout << kGREEN << "MuteOption converter: " << kRESET << std::endl;
        std::cout << "Provide muting the audio from <n> to <m> seconds." << std::endl;
        std::cout << "Example: mute 1 4" << std::endl;
    }

private:
    uint32_t left_; ///< The left boundary for the mute operation.
    uint32_t right_; ///< The right boundary for the mute operation.
};

/**
 * @brief Class for mixing two audio files.
 */
class MixOption : public Converter {
public:
    MixOption(std::string src_file, uint32_t start);

    void Convert(std::string input_file, std::string output_file) override;

    /**
     * @brief Displays help information for the MixOption converter.
     */
    void help() const override {
        std::cout << kGREEN << "MixOption converter" << kRESET << std::endl;
        std::cout << "Provide mixing of two audio files into one" << std::endl;
        std::cout << "Example: mix $2 10" << std::endl;
        std::cout << "It means that we mixed audio with file 2 starting from 10 seconds" << std::endl;
    }

private:
    std::string src_file_; ///< The source file to mix.
    uint32_t start_; ///< The starting point for the mix operation.

    /**
     * @brief Averages the samples from the input and source files.
     * @param samples The input samples.
     * @param scr_samples The source samples.
     */
    void AvgSamples(std::vector<int16_t> &samples, std::vector<int16_t> &scr_samples);
};

/**
 * @brief Class for applying distortion to an audio file.
 */
class DistortionOption : public Converter {
    public:
        DistortionOption(double gain);
        void Convert(std::string input_file, std::string output_file) override;

    /**
     * @brief Displays help information for the DistortionOption converter.
     */
    void help() const override {
        std::cout << kGREEN << "DistortionOption converter: " << kRESET <<std::endl;
        std::cout << "Provide overdriving of the original sound " << std::endl;
        std::cout << "Example: distortion 1.5 " << std::endl;
    }

private:
    double gain_; ///< The gain value for the distortion operation.

    /**
     * @brief Applies the distortion effect to the samples.
     * @param samples The samples to apply the distortion to.
     */
    void applyDistortionOption(std::vector<int16_t> &samples);
};
