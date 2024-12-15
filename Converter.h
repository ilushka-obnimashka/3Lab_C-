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
    MuteOption(uint32_t left, uint32_t right);

    void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

private:
    uint32_t left_;
    uint32_t right_;
};

class MixOption : public Converter {
public:
    MixOption(std::string src_file, uint32_t start);

    void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

private:
    std::string src_file_;
    uint32_t start_;

    void AvgSamples(std::vector<int16_t> &samples, std::vector<int16_t> &scr_samples);
};

class DistortionOption : public Converter {
    public:
        DistortionOption(double gain);

        void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

    private:
        float gain_;

        void applyDistortionOption(std::vector<int16_t> &samples);
};


