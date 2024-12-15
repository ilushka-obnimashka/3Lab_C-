#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "ReaderWAV.h"
#include "WriterWAV.h"


class Converter {
public:
    Converter() = default;

    virtual ~Converter() = default;

    virtual void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) = 0;
};

class MuteOption : public Converter {
public:
    MuteOption(uint32_t left, uint32_t right) {};

    void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

private:
    uint32_t left_;
    uint32_t right_;
};

class MixOption : public Converter {
public:
    MixOption(std::string src_file, uint32_t start) : src_file_(src_file), start_(start) {
    };

    void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

private:
    std::string src_file_;
    uint32_t start_;

    void AvgSamples(std::vector<int16_t> &samples, std::vector<int16_t> &scr_samples);
};

class Distortion : public Converter {
    public:
        Distortion(float gain) : gain_(gain) {}

        void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

    private:
        float gain_;

        void applyDistortion(std::vector<int16_t> &samples);
};


