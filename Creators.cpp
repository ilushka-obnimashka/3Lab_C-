#include "Creators.h"
#include "Converter.h"

Converter *MuteCreater::creatConverter(uint32_t left, uint32_t rigth)
{
    MuteOption *mute = new MuteOption(left, rigth);
    return mute;
}

Converter *MixCreater::creatConverter(uint32_t start, std::string name_src_file)
{
    MixOption *mix = new MixOption(name_src_file, start);
    return mix;
}

Converter *DistortionCreater::creatConverter(double gain)
{
    DistortionOption *distortion = new DistortionOption(gain);
    return distortion;
}
