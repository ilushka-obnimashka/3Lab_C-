#include "Converter.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

void MuteOption::Convert() {

}

void MixOption::Convert() {

}

void Distortion::Convert(std::string input_file, std::string output_file, ReadWAV &reader, WriteWAV &writer) {
    std::vector<int16_t> samples;
    reader.Read(input_file, samples);

    applyDistortion(samples);

    writer.Write(output_file, samples);

}

void Distortion::applyDistortion(std::vector<int16_t> &samples) {
    for(auto &sample : samples) {
        float normalizedSample = sample / 32767;
        float distortedSample = tanh(gain_ * normalizedSample);
        sample = static_cast<int16_t>(distortedSample * 32767);
    }
}