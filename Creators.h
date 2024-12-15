/**
* @file Creators.h
* @brief This file contains the declaration of the Creater base class and its derived classes: MuteCreater, MixCreater, and DistortionCreater.
*/
#pragma once
#include <string>
#include "Converter.h"

/**
* @class Creater
* @brief Base class for factory method. Base class for all creater classes.
*/
class Creater {
public:
    /**
    * @brief Default constructor.
    */
    Creater() = default;
    /**
    * @brief Virtual destructor.
    */
    virtual ~Creater() = default;
};

/**
* @class MuteCreater
* @brief class responsible for the creation of Mute Converter.
*/
class MuteCreater : public Creater {
public:
    /**
    * @brief Creates a Mute converter.
    *
    * @param start The start time in seconds.
    * @param end The end time in seconds.
    * @return A pointer to the created Converter object.
    */
    Converter* CreateConverter(u_int32_t start, u_int32_t end);
};

/**
 * @class MixCreater
 * @brief Dclass responsible for the creation of Mix converters.
 */
class MixCreater : public Creater {
public:
    /**
     * @brief Creates a Mix converter.
     *
     * @param start The start time in seconds.
     * @param file The name of the file to mix.
     * @return A pointer to the created Converter object.
     */
    Converter* CreateConverter(uint32_t start, std::string file);
};

/**
 * @class DistortionCreater
 * @brief class responsible for the creation of Distort Converter.
 */
class DistortionCreater : public Creater {
public:
    /**
    * @brief Creates a Distortion converter.
    *
    * @param gain The gain level.
    * @return A pointer to the created Converter object.
    */
    Converter* CreateConverter(double gain);
};
