//
// Created by korikmat on 07.05.2024.
//

#include <iostream>
#include "ModelLoader.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

std::vector<MeshPtr> ModelLoader::loadModel(std::string const &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path,
                                             aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        throw std::exception();
    }

    this->directory = path.substr(0, path.find_last_of('/'));
    this->directory = this->directory.substr(0, path.find_last_of('\\'));

    // recursive
    return processNode(scene->mRootNode, scene);
}

std::vector<MeshPtr> ModelLoader::processNode(aiNode *node, const aiScene *scene) {
    std::vector<MeshPtr> meshes;
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        std::vector<MeshPtr> mesh = processNode(node->mChildren[i], scene);
        meshes.insert(meshes.end(), mesh.begin(), mesh.end());
    }
    return meshes;

}

MeshPtr ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<VertexType> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        VertexType vertex{};
        glm::vec3 vector;

        // coords
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;


        // texture coords
        if (mesh->mTextureCoords[0]) {

            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = 1 - mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = vec;

            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;


            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        } else {
            vertex.tex_coords = glm::vec2(-1.0f, -1.0f);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // Materials
    std::vector<TexturePtr> textures;
    Materials materials = {};

    if (mesh->mMaterialIndex >= scene->mNumMaterials) {
        std::cerr << "No materials found in the mesh." << std::endl;
        return std::make_shared<Mesh>(vertices, indices, textures, materials);
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];


    // Diffuse maps
    std::vector<TexturePtr> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // Specular maps
    std::vector<TexturePtr> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

//    // Normal maps
//    std::vector<TexturePtr> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
//    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
//
//    // Height maps
//    std::vector<TexturePtr> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
//    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    materials = loadMaterials(material);

    MeshPtr newMesh = std::make_shared<Mesh>(vertices, indices, textures, materials);
    if (!diffuseMaps.empty())
        newMesh->hasDiffTexture = true;
    if (!specularMaps.empty())
        newMesh->hasSpecTexture = true;
    return newMesh;
}

std::vector<TexturePtr> ModelLoader::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<TexturePtr> textures;


    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for (auto &texture: textures_loaded) {
            if (std::strcmp(texture->path.data(), str.C_Str()) == 0) {
                textures.push_back(texture);
                skip = true;
                break;
            }
        }
        if (!skip) {
            std::cout << "Loading texture str: " << str.C_Str() << " directory: " << this->directory << std::endl;
            std::string name = str.C_Str();
            name = name.substr(name.find_last_of('/') + 1);
            TexturePtr texture = std::make_shared<Texture>((this->directory + '/' + name).c_str());
            texture->type = typeName;
            texture->path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

Materials ModelLoader::loadMaterials(aiMaterial *mat) {
    Materials materials = {};

    // Material name
    aiString name;
    if (mat->Get(AI_MATKEY_NAME, name) == AI_SUCCESS) {
        materials.name = name.C_Str();
    }

    // Material color
    aiColor4D color;
    if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
        materials.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
    }

    // Material specular color
    if (mat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS) {
        materials.specular = glm::vec4(color.r, color.g, color.b, color.a);
    }

    // Material shininess
    float shininess;
    if (mat->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
        materials.shininess = shininess;
    }
    return materials;
}