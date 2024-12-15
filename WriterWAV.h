/**
 * @file WriterWAV.h
 * @brief Header file for the WriterWAV class, which handles writing WAV audio files.
 */

#pragma once
#include <fstream>
#include <vector>

/**
 * @class WriterWAV
 * @brief A class to write WAV audio files.
 */
class WriterWAV {
public:
    /**
     * @brief Constructor for the WriterWAV class.
     * @param output_file_path The path to the output WAV file.
     */
    explicit WriterWAV(std::string output_file_path) : output_file_path_(std::move(output_file_path)) {};

    /**
     * @brief Opens the WAV file for writing.
     */
    void OpenWAVFile();

    /**
     * @brief Closes the WAV file.
     */
    void CloseWAVFile();

    /**
     * @brief Writes audio samples to the WAV file.
     *
     * This method writes the provided audio samples to the WAV file starting from the specified position.
     * The offset is calculated based on the sample rate and the starting position.
     *
     * @param samples A reference to a vector of int16_t containing the audio samples to be written.
     * @param start The starting second from which to begin writing audio samples.
     */
    void SaveSamples(std::vector<int16_t> &samples, int start);

private:
    std::fstream file_;          ///< File stream for writing the WAV file.
    std::string output_file_path_; ///< Path to the output WAV file.
};
