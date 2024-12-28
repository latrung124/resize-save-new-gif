/*
* GifUtility.h
* Author: trung.la
* Date: 2024-12-20
* This is a simple utility class that wraps the GifLib library.
*/

#ifndef GIFUTILITY_H
#define GIFUTILITY_H

#include <cstdint>
#include <vector>
#include <string>

namespace gif_util {

namespace gif_89a {

struct GifHeader {
    char signature[3];
    char version[3];
    uint16_t width;
    uint16_t height;
    uint8_t packed;
    uint8_t bgColorIndex;
    uint8_t pixelAspectRatio;
};

struct ColorTableEntry {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct GraphicsControlExtension {
    uint8_t blockSize;
    uint8_t packed;
    uint16_t delayTime;
    uint8_t transparentColorIndex;
};

struct ApplicationExtension {
    std::string identifier;     // 8 characters
    std::string authCode;       // 3 characters
    std::vector<uint8_t> data;  // Application-specific data
};

struct ImageDescriptor {
    uint16_t left;
    uint16_t top;
    uint16_t width;
    uint16_t height;
    uint8_t packed;
};

struct TransformDescriptor {
    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    int16_t rotation = 0;
    int16_t flipType = 0;
};

} // namespace gif_89a

} // namespace gif_util

#endif // GIFUTILITY_H