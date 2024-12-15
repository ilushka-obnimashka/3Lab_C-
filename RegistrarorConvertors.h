/**
* @brief This .h file implements a class for creating dynamic help about converters in the general code.
*/
#pragma once
#include <memory>
#include <vector>
#include "Converter.h"
/**
* @brief The RegistrarConvertors class implements the Singleton pattern to manage a collection of converters.
*
* This class ensures that only one instance of RegistrarConvertors exists throughout the application.
* It provides methods to register converters and print help information about them.
*
* @see [Singleton Pattern Documentation](https://refactoring.guru/design-patterns/singleton)
*/
class RegistrarConvertors {
public:
    /**
    * @brief Deleted copy constructor to prevent copying of the Singleton instance.
    */
    RegistrarConvertors(RegistrarConvertors& other) = delete;

    /**
    * @brief Deleted assignment operator to prevent assignment of the Singleton instance.
    */
    void operator=(const RegistrarConvertors&) = delete;

    /**
    * @brief Returns the single instance of the RegistrarConvertors class.
    *
    * This method ensures that only one instance of the class is created.
    *
    * @return The single instance of the RegistrarConvertors class.
    */
    static RegistrarConvertors& GetInstance();

    /**
    * @brief Registers a converter.
    *
    * This method adds a converter to the internal collection of converters.
    *
    * @param converter A unique pointer to a Converter object.
    */
    void RegisterConverter(std::unique_ptr<Converter> converter);

    /**
    * @brief Prints help information for all registered converters.
    *
    * This method iterates through the collection of converters and calls their help method.
    */
    void printHelp() {
        for (const auto& converter : converters_) {
            converter->help();
        }
    }

private:
    /**
    * @brief The single instance of the RegistrarConvertors class.
    */
    static std::unique_ptr<RegistrarConvertors> singleton_;

    /**
    * @brief Private constructor to prevent instantiation from outside the class.
    */
    RegistrarConvertors() = default;

    /**
    * @brief The collection of converters.
    */
    std::vector<std::unique_ptr<Converter>> converters_;
};

/**
 * @brief The single instance of the RegistrarConvertors class.
 */
std::unique_ptr<RegistrarConvertors> RegistrarConvertors::singleton_ = nullptr;

/**
 * @brief Returns the single instance of the RegistrarConvertors class.
 *
 * This method ensures that only one instance of the class is created.
 *
 * @return The single instance of the RegistrarConvertors class.
 */
RegistrarConvertors& RegistrarConvertors::GetInstance() {
    if (singleton_ == nullptr) {
        singleton_ = std::unique_ptr<RegistrarConvertors>(new RegistrarConvertors());
    }
    return *singleton_;
}
