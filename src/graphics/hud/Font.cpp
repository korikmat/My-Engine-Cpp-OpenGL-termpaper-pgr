#include "Font.h"

#include <utility>
#include <iostream>
#include "../Texture.h"
#include "Batch2D.h"

Font::Font(std::string filename) {
    for (size_t i = 0; i <= 4; i++) {
        Texture *texture = new Texture((filename + "_" + std::to_string(i) + ".png").c_str());
        if (texture == nullptr) {
            std::cerr << "failed to load bitmap font (missing page " << std::to_string(i) << ")" << std::endl;
            throw std::exception();
        }
        pages.push_back(texture);
    }
}

Font::~Font() {
    for (auto &texture: pages)
        delete texture;
}

int Font::getGlyphWidth(char c) {
    switch (c) {
        case 'l':
        case 'i':
        case 'j':
        case '|':
        case '.':
        case ',':
        case ':':
        case ';':
            return 7;
        case 't':
            return 8;
        case ' ':
            return 7;
    }
    return 7;
}


bool Font::isPrintableChar(int c) {
    switch (c) {
        case ' ':
        case '\t':
        case '\n':
        case '\f':
        case '\r':
            return false;
        default:
            return true;
    }
}

#define RES 16

void Font::draw(Batch2D *batch, std::wstring text, int x, int y) {
    draw(batch, std::move(text), x, y, STYLE_NONE);
}

void Font::draw(Batch2D *batch, std::wstring text, int x, int y, int style) {
    int page = 0;
    int next = 10000;
    int init_x = x;
    do {
        for (unsigned c: text) {
            if (isPrintableChar(c)) {
                int charpage = c >> 8;
                if (charpage == page) {
                    Texture *texture = pages[charpage];
                    if (texture == nullptr) {
                        texture = pages[0];
                    }
                    batch->texture(pages[charpage]);

                    switch (style) {
                        case STYLE_SHADOW:
                            batch->sprite(x + 1, y + 1, RES, RES, 16, c, vec4(0.0f, 0.0f, 0.0f, 1.0f));
                            break;
                        case STYLE_OUTLINE:
                            for (int oy = -1; oy <= 1; oy++) {
                                for (int ox = -1; ox <= 1; ox++) {
                                    if (ox || oy)
                                        batch->sprite(x + ox, y + oy, RES, RES, 16, c, vec4(0.0f, 0.0f, 0.0f, 1.0f));
                                }
                            }
                            break;
                    }

                    batch->sprite(x, y, RES, RES, 16, c, batch->color);
                } else if (charpage > page && charpage < next) {
                    next = charpage;
                }
            }
            x += getGlyphWidth(c);
        }
        page = next;
        next = 10000;
        x = init_x;
    } while (page < 10000);
}
