/// @file Terrain.h
/// @brief This file contains the definition of the Terrain class.
///
/// Created by korikmat on 17.05.2024.

#ifndef PROJECT_TERRAIN_H
#define PROJECT_TERRAIN_H

#include "Model.h"

/// @class Terrain
/// @brief The Terrain class represents a terrain model in the scene.
/// @details This class inherits from the Model class and is used to handle terrain-specific functionalities.
class Terrain : public Model {
public:
    /// @brief Constructs a Terrain object with the specified path and ID.
    /// @param path The file path to the terrain model.
    /// @param ID The unique identifier for the terrain model.
    /// @param originalObjectID The unique identifier for the original object. Default is 0.
    explicit Terrain(std::string const &path, size_t ID = 0, size_t originalObjectID = 0) : Model(path, ID, originalObjectID) {}
};

#endif //PROJECT_TERRAIN_H
