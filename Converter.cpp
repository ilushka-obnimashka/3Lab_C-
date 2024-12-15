/**
 * @file Converter.cpp
 * @brief Implementation of the Converter class and its derived classes.
 */

#include <string>
#include <iostream>
#include <filesystem>
#include <cmath>
#include "Converter.h"
#include "WAVHeader.h"

/**
 * @brief Constructor for the MuteOption class.
 * @param left The left boundary for the mute operation.
 * @param right The right boundary for the mute operation.
 */
MuteOption::MuteOption(uint32_t left, uint32_t right) {
    if (left > right) {
        std::cerr << kYELLOW << "Error: Left boundary is greater than right boundary. Swapping them." << kRESET << std::endl;
        std::swap(left, right);
    }
    left_ = left;
    right_ = right;
}

/**
 * @brief Applies the mute operation to the input file and saves the result to the output file.
 * @param input_file The input WAV file.
 * @param output_file The output WAV file.
 */
void MuteOption::Convert(std::string input_file, std::string output_file) {
    std::cout << kGREEN << "mute " << left_ << " " << right_ << kRESET << std::endl;

    if (!std::filesystem::exists(input_file)) {
        std::cerr << kRED << "File: " << input_file << " does not exist." << kRESET << std::endl;
        exit(3);
    }

    if (!std::filesystem::exists(output_file)) {
        std::cerr << kRED << "File: " << output_file << " does not exist." << kRESET << std::endl;
        exit(3);
    }

    std::filesystem::copy(input_file, output_file, std::filesystem::copy_options::overwrite_existing);

    int count_sec = left_ - right_;

    WriterWAV writer(output_file);
    writer.OpenWAVFile();
    std::vector<int16_t> samples(FIXED_SAMPLE_RATE, 0);
    while (count_sec) {
        writer.SaveSamples(samples, left_);
        --count_sec;
    }

    writer.CloseWAVFile();
}

/**
 * @brief Constructor for the MixOption class.
 * @param src_file The source file to mix.
 * @param start The starting point for the mix operation.
 */
MixOption::MixOption(std::string src_file, uint32_t start) : src_file_(src_file), start_(start) {}

/**
 * @brief Applies the mix operation to the input file and saves the result to the output file.
 * @param input_file The input WAV file.
 * @param output_file The output WAV file.
 */
void MixOption::Convert(std::string input_file, std::string output_file) {
    std::cout << kGREEN << "mix " << src_file_ << " " << start_ << kRESET << std::endl;

    if (!std::filesystem::exists(input_file)) {
        std::cerr << kRED << "File: " << input_file << " does not exist." << kRESET << std::endl;
        exit(3);
    }
    if (!std::filesystem::exists(src_file_)) {
        std::cerr << kRED << "File: " << src_file_ << " does not exist." << kRESET << std::endl;
        exit(3);
    }

    std::filesystem::copy(input_file, output_file, std::filesystem::copy_options::overwrite_existing);

    ReaderWAV src_reader(src_file_);
    src_reader.OpenWAVFile();
    src_reader.ReadHead();
    if (!src_reader.CheckingFileValidity()) {
        std::cerr << kRED << "Source file is not a valid WAV format" << kRESET << std::endl;
        exit(3);
    }

    ReaderWAV reader(input_file);
    reader.OpenWAVFile();
    reader.ReadHead();
    if (!reader.CheckingFileValidity()) {
        std::cerr << kRED << "Input file is not a valid format" << kRESET << std::endl;
        exit(3);
    }

    WriterWAV writer(output_file);
    writer.OpenWAVFile();

    int input_size = reader.GetSizeFileInSec();
    int src_size = src_reader.GetSizeFileInSec();

    std::vector<int16_t> input_samples;
    std::vector<int16_t> src_samples;

    bool flag = true;
    while (src_reader.GetSamples(src_samples, 0, src_size) && flag) {
        flag = reader.GetSamples(input_samples, start_, input_size);
        AvgSamples(input_samples, src_samples);
        writer.SaveSamples(input_samples, start_);
    }

    reader.CloseWAVFile();
    src_reader.CloseWAVFile();
    writer.CloseWAVFile();
}

/**
 * @brief Averages the samples from the input and source files.
 * @param samples The input samples.
 * @param src_samples The source samples.
 */
void MixOption::AvgSamples(std::vector<int16_t> &samples, std::vector<int16_t> &src_samples) {
    auto it1 = samples.begin();
    auto it2 = src_samples.begin();

    while (it1 != samples.end() && it2 != src_samples.end()) {
        *it1 = (*it1 + *it2) / 2;
        ++it1;
        ++it2;
    }
}

/**
 * @brief Constructor for the DistortionOption class.
 * @param gain The gain value for the distortion operation.
 */
DistortionOption::DistortionOption(double gain) : gain_(gain) {
    if (gain < 0) {
        std::cerr << kRED << "Incorrect data: " << gain << kRESET << std::endl;
        std::cerr << kYELLOW << "Check for correctness, please: " << "gain > 0" << std::endl;
        exit(4);
    }
}

/**
 * @brief Applies the distortion operation to the input file and saves the result to the output file.
 * @param input_file The input WAV file.
 * @param output_file The output WAV file.
 */
void DistortionOption::Convert(std::string input_file, std::string output_file) {
    std::cout << kGREEN << "DistortionOption " << gain_ << kRESET << std::endl;

    if (!std::filesystem::exists(input_file)) {
        std::cerr << kRED << "File: " << input_file << " does not exist." << kRESET << std::endl;
        exit(3);
    }

    std::filesystem::copy(input_file, output_file, std::filesystem::copy_options::overwrite_existing);

    ReaderWAV reader(input_file);
    reader.OpenWAVFile();
    reader.ReadHead();
    if (!reader.CheckingFileValidity()) {
        std::cerr << kRED << "Input file is not a valid WAV file." << kRESET << std::endl;
        exit(3);
    }

    WriterWAV writer(output_file);
    writer.OpenWAVFile();

    int input_size = reader.GetSizeFileInSec();
    std::vector<int16_t> samples;

    for (int i = 0; i < input_size; ++i) {
        if (reader.GetSamples(samples, i, i + 1)) {
            applyDistortionOption(samples);
            writer.SaveSamples(samples, i);
        }
    }

    reader.CloseWAVFile();
    writer.CloseWAVFile();
}

/**
 * @brief Applies the distortion effect to the samples.
 * @param samples The samples to apply the distortion to.
 */
void DistortionOption::applyDistortionOption(std::vector<int16_t> &samples) {
    for (auto &sample : samples) {
        double normalizedSample = sample / 32767;
        double distortedSample = std::tanh(gain_ * normalizedSample);
        sample = static_cast<int16_t>(distortedSample * 32767);
    }
}
