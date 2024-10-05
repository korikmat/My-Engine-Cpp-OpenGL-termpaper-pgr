/// @file UVRegion.h
/// @brief This file contains the definition of the UVRegion class.
///
/// Created by korikmat.

#ifndef PROJECT_UVREGION_H_
#define PROJECT_UVREGION_H_

/// @class UVRegion
/// @brief The UVRegion class represents a region in a texture using UV coordinates.
/// @details This class is used to define a rectangular area in a texture map using UV coordinates, which range from 0.0 to 1.0.
class UVRegion {
public:
    /// @brief The U coordinate of the top-left corner.
    float u1;

    /// @brief The V coordinate of the top-left corner.
    float v1;

    /// @brief The U coordinate of the bottom-right corner.
    float u2;

    /// @brief The V coordinate of the bottom-right corner.
    float v2;

    /// @brief Constructs a UVRegion with specified coordinates.
    /// @param u1 The U coordinate of the top-left corner.
    /// @param v1 The V coordinate of the top-left corner.
    /// @param u2 The U coordinate of the bottom-right corner.
    /// @param v2 The V coordinate of the bottom-right corner.
    UVRegion(float u1, float v1, float u2, float v2)
        : u1(u1), v1(v1), u2(u2), v2(v2) {}

    /// @brief Constructs a UVRegion with default coordinates (0.0, 0.0, 1.0, 1.0).
    UVRegion() : u1(0.0f), v1(0.0f), u2(1.0f), v2(1.0f) {}
};

#endif /* PROJECT_UVREGION_H_ */
