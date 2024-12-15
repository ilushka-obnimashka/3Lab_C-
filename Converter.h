/**
 * @file Converter.h
 * @brief Header file for the Converter class and its derived classes.
 */

#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "ReaderWAV.h"
#include "WriterWAV.h"

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
    virtual void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) = 0;

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
    /**
     * @brief Constructor for the MuteOption class.
     * @param left The left boundary for the mute operation.
     * @param right The right boundary for the mute operation.
     */
    MuteOption(uint32_t left, uint32_t right);

    /**
     * @brief Applies the mute operation to the input file and saves the result to the output file.
     * @param input_file The input WAV file.
     * @param output_file The output WAV file.
     * @param reader The ReaderWAV object to read the input file.
     * @param writer The WriterWAV object to write the output file.
     */
    void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

    /**
     * @brief Displays help information for the MuteOption converter.
     */
    void help() const override {
        std::cout << "MuteOption converter: \n";
        std::cout << "Provide muting the audio from <n> to <m> seconds. \n" << std::endl;
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
    /**
     * @brief Constructor for the MixOption class.
     * @param src_file The source file to mix.
     * @param start The starting point for the mix operation.
     */
    MixOption(std::string src_file, uint32_t start);

    /**
     * @brief Applies the mix operation to the input file and saves the result to the output file.
     * @param input_file The input WAV file.
     * @param output_file The output WAV file.
     * @param reader The ReaderWAV object to read the input file.
     * @param writer The WriterWAV object to write the output file.
     */
    void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

    /**
     * @brief Displays help information for the MixOption converter.
     */
    void help() const override {
        std::cout << "MixOption converter\n" << std::endl;
        std::cout << "Provide mixing of two audio files into one\n" << std::endl;
        std::cout << "Example: mix $2 10\n" << std::endl;
        std::cout << "It means that we mixed audio with file 2 starting from 10 seconds\n" << std::endl;
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
    /**
     * @brief Constructor for the DistortionOption class.
     * @param gain The gain value for the distortion operation.
     */
    DistortionOption(double gain);

    /**
     * @brief Applies the distortion operation to the input file and saves the result to the output file.
     * @param input_file The input WAV file.
     * @param output_file The output WAV file.
     * @param reader The ReaderWAV object to read the input file.
     * @param writer The WriterWAV object to write the output file.
     */
    void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

    /**
     * @brief Displays help information for the DistortionOption converter.
     */
    void help() const override {
        std::cout << "DistortionOption converter:\n" << std::endl;
        std::cout << "Provide overdriving of the original sound\n" << std::endl;
        std::cout << "Example: distortion 1.5\n" << std::endl;
    }

private:
    double gain_; ///< The gain value for the distortion operation.

    /**
     * @brief Applies the distortion effect to the samples.
     * @param samples The samples to apply the distortion to.
     */
    void applyDistortionOption(std::vector<int16_t> &samples);
};
