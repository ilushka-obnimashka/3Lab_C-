/**
 * @file Creators.cpp
 * @brief Implementation of the creator classes for different converter types.
 */

#include "Creators.h"
#include "Converter.h"

/**
 * @brief Creates a MuteOption converter.
 * @param left The left boundary for the mute operation.
 * @param right The right boundary for the mute operation.
 * @return A pointer to a new MuteOption object.
 */
Converter *MuteCreater::CreateConverter(uint32_t left, uint32_t right) {
    return new MuteOption(left, right);
}

/**
 * @brief Creates a MixOption converter.
 * @param start The starting point for the mix operation.
 * @param name_src_file The name of the source file to mix.
 * @return A pointer to a new MixOption object.
 */
Converter *MixCreater::CreateConverter(uint32_t start, std::string name_src_file) {
    return new MixOption(name_src_file, start);
}

/**
 * @brief Creates a DistortionOption converter.
 * @param gain The gain value for the distortion operation.
 * @return A pointer to a new DistortionOption object.
 */
Converter *DistortionCreater::CreateConverter(double gain) {
    return new DistortionOption(gain);
}
