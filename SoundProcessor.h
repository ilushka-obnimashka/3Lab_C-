#pragma once
#include "ArgumentParser.h"

class SoundProcessor {
public:
    void Control(int argc, char* argv[]);
    void Processing(ArgumentParser& argument_parser);
    void HeplPrint();
};
