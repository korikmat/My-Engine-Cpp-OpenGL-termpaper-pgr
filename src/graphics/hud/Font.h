/// @file Font.h
/// @brief This file contains the definition of the Font class and related constants.
///
/// Created by korikmat.

#ifndef PROJECT_FONT_H_
#define PROJECT_FONT_H_

#include <string>
#include <vector>

class Texture;
class Batch2D;

/// @def STYLE_NONE
/// @brief Constant for no text style.
#define STYLE_NONE 0

/// @def STYLE_SHADOW
/// @brief Constant for shadow text style.
#define STYLE_SHADOW 1

/// @def STYLE_OUTLINE
/// @brief Constant for outline text style.
#define STYLE_OUTLINE 2

/// @class Font
/// @brief The Font class is used for managing and rendering text using different styles.
/// @details This class handles loading font textures and rendering text to a 2D batch.
class Font {
public:
    /// @brief A vector of texture pages used by the font.
    std::vector<Texture *> pages;

    /// @brief Constructs a Font object from the specified filename.
    /// @param filename The filename of the font file.
    explicit Font(std::string filename);

    /// @brief Destructor for Font.
    ~Font();

    /// @brief Gets the width of the specified glyph.
    /// @param c The character for which to get the width.
    /// @return The width of the glyph.
    int getGlyphWidth(char c);

    /// @brief Checks if the specified character is printable.
    /// @param c The character to check.
    /// @return True if the character is printable, false otherwise.
    bool isPrintableChar(int c);

    /// @brief Draws the specified text using the provided batch at the given position.
    /// @param batch The Batch2D object used for rendering.
    /// @param text The text to be drawn.
    /// @param x The x coordinate for the text.
    /// @param y The y coordinate for the text.
    void draw(Batch2D *batch, std::wstring text, int x, int y);

    /// @brief Draws the specified text using the provided batch at the given position with the specified style.
    /// @param batch The Batch2D object used for rendering.
    /// @param text The text to be drawn.
    /// @param x The x coordinate for the text.
    /// @param y The y coordinate for the text.
    /// @param style The style to be applied to the text (e.g., STYLE_NONE, STYLE_SHADOW, STYLE_OUTLINE).
    void draw(Batch2D *batch, std::wstring text, int x, int y, int style);
};

#endif /* PROJECT_FONT_H_ */
