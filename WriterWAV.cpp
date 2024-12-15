/**
 * @file WriterWAV.cpp
 * @brief Implementation of the WriterWAV class for writing WAV files.
 */

#include <iostream>
#include <fstream>
#include "WAVHeader.h"
#include "WriterWAV.h"

const std::string kRED = "\033[1;31m";
const std::string kRESET = "\033[0m";
const std::string kYELLOW = "\033[33m";

/**
 * @brief Opens the WAV file for writing.
 */
void WriterWAV::OpenWAVFile() {
    file_.open(output_file_path_, std::ios::in | std::ios::out | std::ios::binary);
    if (!file_.is_open()) {
        std::cerr << kRED << "Failed to open the file. Please check the file name or path and try again" << kRESET << std::endl;
        exit(2);
    }
}

/**
 * @brief Closes the WAV file.
 */
void WriterWAV::CloseWAVFile() {
    file_.close();
}

/**
 * @brief Saves audio samples to the WAV file.
 *
 * This method writes the provided audio samples to the WAV file starting from the specified position.
 * The offset is calculated based on the sample rate and the starting position.
 *
 * @param samples A reference to a vector of int16_t containing the audio samples to be written.
 * @param start The starting second from which to begin writing audio samples.
 */
void WriterWAV::SaveSamples(std::vector<int16_t> &samples, int start) {
    uint64_t offset = 2 * static_cast<uint64_t>(FIXED_SAMPLE_RATE) * static_cast<uint64_t>(start) + static_cast<uint64_t>(sizeof(WAVHeader));

    std::streampos currentPos = file_.tellp();

    if (currentPos < offset)
        file_.seekp(offset, std::ios::beg);

    file_.write((const char*)(samples.data()), samples.size() * sizeof(int16_t));
}
