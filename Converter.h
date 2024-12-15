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

    virtual void help() const = 0;
};

class MuteOption : public Converter {
public:
    MuteOption(uint32_t left, uint32_t right);

    void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

    void help() const override {
        std::cout << "MuteOption converter: \n";
        std::cout << "Provide muting the audio from <n> to <m> seconds. \n" << std::endl;
        std::cout << "Example: mute 1 4" << std::endl; 
    }

private:
    uint32_t left_;
    uint32_t right_;
};

class MixOption : public Converter {
public:
    MixOption(std::string src_file, uint32_t start);

    void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

    void help() const override {
        std::cout << "MixOption converter\n" << std::endl;
        std::cout << "Provide mixig of two audio in one\n" << std::endl;
        std::cout << "Example: mix $2 10\n" << std::endl;
        std::cout << "It means that we mixed audio with file 2 starting from 10 seconds\n" << std::endl;
    }

private:
    std::string src_file_;
    uint32_t start_;

    void AvgSamples(std::vector<int16_t> &samples, std::vector<int16_t> &scr_samples);
};

class DistortionOption : public Converter {
    public:
        DistortionOption(double gain);

        void Convert(std::string input_file, std::string output_file, ReaderWAV &reader, WriterWAV &writer) override;

        void help() const override {
            std::cout << "DistortionOption converter:\n" << std::endl;
            std::cout << "Provide overdriving of the original sound\n" << std::endl;
            std::cout << "Example: distortion 1.5\n" << std::endl;
        }

    private:
        float gain_;

        void applyDistortionOption(std::vector<int16_t> &samples);
};


