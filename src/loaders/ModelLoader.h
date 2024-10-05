/// @file ModelLoader.h
/// @brief This file contains the definition of the ModelLoader class.
///
/// Created by korikmat on 07.05.2024.

#ifndef PROJECT_MODELLOADER_H
#define PROJECT_MODELLOADER_H

#include <vector>
#include "../graphics/models/Mesh.h"
#include "assimp/scene.h"

/// @class ModelLoader
/// @brief The ModelLoader class is responsible for loading 3D models from files.
/// @details This class handles loading models using the Assimp library, processing nodes and meshes, and loading textures and materials.
class ModelLoader {
public:
    /// @brief Destructor for ModelLoader.
    ~ModelLoader() = default;

    /// @brief Loads a model from the specified file path.
    /// @param path The file path to the model.
    /// @return A vector of MeshPtr representing the loaded model.
    std::vector<MeshPtr> loadModel(std::string const &path);

private:
    /// @brief The file path to the model being loaded.
    std::string path_;

    /// @brief A vector of textures that have already been loaded.
    std::vector<TexturePtr> textures_loaded;

    /// @brief The directory of the model file.
    std::string directory;

    /// @brief Processes a node in the Assimp scene graph.
    /// @param node The node to process.
    /// @param scene The Assimp scene containing the node.
    /// @return A vector of MeshPtr representing the processed meshes.
    std::vector<MeshPtr> processNode(aiNode *node, const aiScene *scene);

    /// @brief Processes a mesh in the Assimp scene.
    /// @param mesh The mesh to process.
    /// @param scene The Assimp scene containing the mesh.
    /// @return A MeshPtr representing the processed mesh.
    MeshPtr processMesh(aiMesh *mesh, const aiScene *scene);

    /// @brief Loads textures from a material.
    /// @param mat The material to load textures from.
    /// @param type The type of texture to load.
    /// @param typeName The name of the texture type.
    /// @return A vector of TexturePtr representing the loaded textures.
    std::vector<TexturePtr> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    /// @brief Loads material properties from a material.
    /// @param mat The material to load properties from.
    /// @return A Materials struct representing the loaded material properties.
    Materials loadMaterials(aiMaterial *mat);
};

#endif //PROJECT_MODELLOADER_H
