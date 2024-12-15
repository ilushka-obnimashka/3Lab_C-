#include <string>
#include <iostream>
#include <filesystem>
#include <cmath>
#include "Converter.h"
#include "WAVHeader.h"

const std::string kRESET = "\033[0m";
const std::string kGREEN = "\033[32m";
const std::string kRED = "\033[1;31m";
const std::string kYELLOW = "\033[33m";


MuteOption::MuteOption(uint32_t left, uint32_t right) {
    {
        std::cerr << kYELLOW << "Error: Left boundary is greater than right boundary. Swapping them." << kRESET << std::endl;
        std::swap(left, right);
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

MixOption::MixOption(std::string src_file, uint32_t start) : src_file_(src_file), start_(start) {};

void MixOption::Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) {
    std::cout << kGREEN << "mix " << src_file_ << " " << start_ << kRESET << std::endl;

    if(!std::filesystem::exists(input_file)) {
        std::cerr << kRED << "File: " << input_file << " does not exist." << kRESET << std::endl;
        exit(3);
    }
    if(!std::filesystem::exists(src_file_)) {
        std::cerr << kRED << "File: " << src_file_ << " does not exist." << kRESET << std::endl;
        exit(3);
    }

    std::filesystem::copy(input_file, output_file, std::filesystem::copy_options::overwrite_existing);

    ReaderWAV src_reader(src_file_);
    src_reader.OpenWAVFile();
    src_reader.ReadHead();
    if(!src_reader.CheckingFileValidity()) {
        std::cerr << kRED << "Source file is not a valid WAV format" << kRESET << std::endl;
        exit(3);
    }

    reader.OpenWAVFile();
    reader.ReadHead();
    if(!reader.CheckingFileValidity()) {
        std::cerr << kRED << "Input file is not a valid format" << kRESET << std::endl;
        exit(3);
    }

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

void MixOption::AvgSamples(std::vector<int16_t> &samples, std::vector<int16_t> &src_samples) {
    auto it1 = samples.begin();
    auto it2 = src_samples.begin();

    while (it1 != samples.end() && it2 != src_samples.end()) {
        *it1 = (*it1 + *it2) / 2;
        ++it1;
        ++it2;
    }
}

DistortionOption::DistortionOption(double gain) : gain_(gain) {
    if (gain < 0) {
        std::cerr << kRED << "Incorrect data: " << gain << kRESET << std::endl;
        std::cerr << kYELLOW << "Check for correctness, please: " << "gain > 0" << std::endl;
        exit(4);
    }
}

void DistortionOption::Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) {
    std::cout << kGREEN << "DistortionOption " << gain_ << kRESET << std::endl;

    if (!std::filesystem::exists(input_file)) {
        std::cerr << kRED << "File: " << input_file << " does not exist." << kRESET << std::endl;
        exit(3);
    }

    std::filesystem::copy(input_file, output_file, std::filesystem::copy_options::overwrite_existing);

    reader.OpenWAVFile();
    reader.ReadHead();
    if (!reader.CheckingFileValidity()) {
        std::cerr << kRED << "Input file is not a valid WAV file." << kRESET << std::endl;
        exit(3);
    }

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

void DistortionOption::applyDistortionOption(std::vector<int16_t> &samples) {
    for (auto &sample : samples) {
        double normalizedSample = sample / 32767;
        double distortedSample = std::tanh(gain_ * normalizedSample);
        sample = static_cast<int16_t>(distortedSample * 32767);
    }
}
