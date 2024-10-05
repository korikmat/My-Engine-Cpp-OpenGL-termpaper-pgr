/// @file ClassFactory.h
/// @brief This file contains the definition of the ClassFactory class and related macros.
///
/// Created by korikmat on 17.05.2024.

#ifndef PROJECT_CLASSFACTORY_H
#define PROJECT_CLASSFACTORY_H

#include <map>
#include "../graphics/models/Model.h"

/// @def REGISTER_CLASS(TYPE)
/// @brief Macro for registering a class type with the ClassFactory.
/// @param TYPE The class type to be registered.
#define REGISTER_CLASS(TYPE) \
    ClassFactory::instance().registerClass(#TYPE, [](std::string const &path, size_t ID, bool copy = false) \
                                                        -> ModelPtr { return std::make_shared<TYPE>(path, ID, copy); })

/// @def GET_CLASS_NAME(TYPE)
/// @brief Macro for getting the class name as a string.
/// @param TYPE The class type.
#define GET_CLASS_NAME(TYPE) #TYPE

/// @class ClassFactory
/// @brief The ClassFactory class is responsible for creating instances of models.
/// @details This class uses a map of creator functions to instantiate objects based on their type names.
class ClassFactory {
public:
    /// @brief Type definition for the function pointer used to create model instances.
    using CreateFunction = ModelPtr (*)(std::string const &path, size_t ID, bool copy);

    /// @brief Gets the singleton instance of the ClassFactory.
    /// @return Reference to the singleton instance of ClassFactory.
    static ClassFactory &instance();

    /// @brief Registers a class type with the factory.
    /// @param type The name of the class type.
    /// @param func The function to create instances of the class type.
    void registerClass(const std::string &type, CreateFunction func);

    /// @brief Creates an instance of a registered class type.
    /// @param type The name of the class type.
    /// @param path The file path to the model object.
    /// @param ID The unique identifier for the model instance.
    /// @param copy A flag indicating whether the model is a copy. Default is false.
    /// @return A shared pointer to the created model instance.
    ModelPtr create(const std::string &type, std::string const &path, size_t ID, bool copy = false);

private:
    /// @brief Map of type names to their corresponding creator functions.
    std::map<std::string, CreateFunction> creators;
};

#endif //PROJECT_CLASSFACTORY_H
