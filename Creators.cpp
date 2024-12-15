#include "Creators.h"
#include "Converter.h"

Converter *MuteCreater::CreateConverter(uint32_t left, uint32_t rigth)
{
    return new MuteOption(left, rigth);
}

Converter *MixCreater::CreateConverter(uint32_t start, std::string name_src_file)
{
    return new MixOption(name_src_file, start);
}

Converter *DistortionCreater::CreateConverter(double gain)
{
    return new DistortionOption(gain);
}
