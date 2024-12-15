#include <string>
#include <iostream>
#include <filesystem>
#include "Converter.h"
#include "WAVHeader.h"

const std::string kRESET = "\033[0m";
const std::string kGREEN = "\033[32m";
const std::string kRED = "\033[1;31m";
const std::string kYELLOW = "\033[33m";


MuteOption MuteOption(uint32_t left, uint32_t right) {
    if (left < 0 || right < 0) {
        std::cerr << kRED << "Incorrect data: " << left << " " << right << kRESET << std::endl;
        std::cerr << kYELLOW << "Check for correctness, plese: " << "left > 0, right > 0";
        exit (4);
    }

    if (left > right) {

    }
}

void MuteOption::Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) {
    std::cout << kGREEN << "mute " << left_ << " " << right_ << kRESET << std::endl;

    if(!(std::filesystem::exists(input_file))) {
        std::cerr << kRED << "File: " << input_file << "does not exist." << kRESET << std::endl;
        exit(3);
    }

    if(!(std::filesystem::exists(output_file))) {
        std::cerr << kRED << "File: " << output_file << "does not exist." << kRESET << std::endl;
        exit(3);
    }

    std::filesystem::copy(input_file, output_file, std::filesystem::copy_options::overwrite_existing);

    int count_sec = left_ - right_;


    std::vector<int16_t> samples(FIXED_SAMPLE_RATE, 0);
    while (count_sec)
    {
        writer.SaveSamples(samples, left_);
        --count_sec;
    }

    writer.CloseWAVFile();
}
