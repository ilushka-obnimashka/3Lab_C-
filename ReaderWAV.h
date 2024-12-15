#pragma once
#include <fstream>
#include <vector>
#include "WAVHeader.h"

/**
* @class ReaderWAV
* @brief A class to read and handle WAV audio files.
*/
class ReaderWAV {
public:
    /**
      * @brief Constructor for the ReaderWAV class.
      * @param input_file_path The path to the input WAV file.
    */
    explicit ReaderWAV(std::string input_file_path) : input_file_path_(std::move(input_file_path)) {};

    /**
     * @brief Opens the WAV file_ for reading.
    */
    void OpenWAVFile();

    /**
     * @brief Closes the WAV file_.
    */

    void CloseWAVFile();

    /**
    * @brief Reads the header of the WAV file.
    */
    void ReadHead();

    /**
    * @brief Validates that the WAV file is in the proper format and has specific properties.
    *
    * This method checks the header of the WAV file to ensure that it is a valid WAV file
    * and that it meets the required properties for this program. Specifically, it checks:
    * - The chunk ID is "RIFF" and the RIFF type ID is "WAVE".
    * - The format tag is PCM (1).
    * - The number of channels is 1 (mono audio).
    * - The sample rate is 44100 Hz.
    * - The bits per sample is 16.
    *
    * If any of these conditions are not met, the method throws a std::runtime_error with an appropriate message.
    * If all conditions are met, the method returns true.
    *
    * @return true if the WAV file is valid and meets the required properties.
    * @throw std::runtime_error if the WAV file is not valid or does not meet the required properties.
    */
    bool CheckingFileValidity() const;

    /**
     * @brief Reads a portion of audio samples from the WAV file.
     *
     * This method reads a specified range of audio samples from the WAV file and stores them in the provided vector.
     * The range is defined by the start and end seconds. The method calculates the offset in the file where the
     * audio samples start and reads the samples into the vector.
     *
     * @param samples A reference to a vector of int16_t where the audio samples will be stored.
     * @param start The starting second from which to begin reading audio samples.
     * @param end The ending second up to which to read audio samples.
     * @return true if the samples were successfully read, false otherwise.
    */
    bool GetSamples (std::vector<int16_t> &samples, uint32_t start, uint32_t end);

    WAVHeader *GetWAVHeader();
    /**
    * @brief Calculates the size of the WAV file in seconds.
    * @return The duration of the audio data in seconds.
    */
    int GetSizeFileInSec();

private:
    std::ifstream file_;          ///< File stream for reading the WAV file.
    std::string input_file_path_; ///< Path to the input WAV file.
    uint64_t remaining_audio_data_size_; ///< Remaining size of the audio data in the WAV file.
    struct WAVHeader *WAVHeader_; ///< Pointer to the WAV header structure.
};
