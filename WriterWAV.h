#pragma once
#include <fstream>
#include <vector>


/**
* @class WriterWAV
* @brief A class to write  WAV audio files.
*/
class WriterWAV {
public:
    /**
      * @brief Constructor for the WriterWAV class.
      * @param output_file_path The path to the output WAV file.
    */
    explicit WriterWAV(std::string output_file_path) : output_file_path_(std::move(output_file_path)) {};

    /**
     * @brief Opens the WAV file_ for reading.
    */
    void OpenWAVFile();

    /**
     * @brief Closes the WAV file_.
    */
    void CloseWAVFile();

    /**
    * @brief Writes the WAV file.
    */
    void SaveSamples(std::vector<int16_t> &samples, int start);



private:
    std::fstream file_;          ///< File stream for reading the WAV file.
    std::string output_file_path_; ///< Path to the output WAV file.
};
