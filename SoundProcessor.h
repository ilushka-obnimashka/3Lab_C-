#pragma once
#include "ArgumentParser.h"

class SoundProcessor {
public:
    void Control(int argc, char* argv[]);
private:
    void Processing(ArgumentParser& argument_parser);
    void HeplPrint();
};
