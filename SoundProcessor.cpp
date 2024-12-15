#include <string>
#include <queue>
#include <filesystem>
#include "SoundProcessor.h"
#include "ArgumentParser.h"
#include "ConfigParser.h"
#include "RegistrarorConvertors.h"



void SoundProcessor::Control(int argc, char *argv[]) {
    ArgumentParser argument_parser(argc, argv);

    if (argument_parser.Parse()) {
        Processing(argument_parser);
    }
    else {
        HeplPrint();
    }
}

void SoundProcessor::Processing(ArgumentParser& argument_parser){
    std::string config_file = argument_parser.GetConfigFile();

    ConfigParser config_parser (config_file);

    std::vector<std::string> input_files = argument_parser.GetInputFiles();
    std::queue<Converter *> convverters = config_parser.Parse(input_files);

    const std::string main_file = input_files[0];
    const std::string out_file = argument_parser.GetOutputFile();

    std::filesystem::copy(main_file, "./tmp1.wav", std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy(main_file, "./tmp2.wav", std::filesystem::copy_options::overwrite_existing);
    std::pair<std::string, std::string> names{"./tmp1.wav", "./tmp2.wav"};

    if (std::filesystem::exists(out_file))
        std::filesystem::remove(out_file);

    while (!convverters.empty()) {
        Converter* conv = convverters.front();
        convverters.pop();
        conv->Convert(names.first, names.second);
        std::swap(names.first, names.second);
    }

    std::filesystem::remove(names.second);
    std::rename(names.first.c_str(), out_file.c_str());
}

void SoundProcessor::HeplPrint() {
    RegistrarConvertors& registrar_convertors = RegistrarConvertors::GetInstance();

    registrar_convertors.RegisterConverter(std::make_unique<MuteOption>(MuteOption(1,2)));
    registrar_convertors.RegisterConverter(std::make_unique<MixOption>(MixOption("in",2)));
    registrar_convertors.RegisterConverter(std::make_unique<DistortionOption>(DistortionOption(4.5)));

    registrar_convertors.printHelp();

}





