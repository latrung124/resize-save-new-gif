/*
* Gif89aReader.h
* Author: trung.la
* Date: 2024-12-24
* Description: This file contains the Gif89aReader class.
*/

#ifndef GIF89AREADER_H
#define GIF89AREADER_H

#include "GifUtility.h"

#include <vector>
#include <fstream>

class Gif89aReader
{
public:
    using GifHeader = gif_util::gif_89a::GifHeader;
    using ColorTableEntry = gif_util::gif_89a::ColorTableEntry;
    using ApplicationExtension = gif_util::gif_89a::ApplicationExtension;

    Gif89aReader();
    ~Gif89aReader();

    bool readGifFile(const char* fileName);
    std::vector<ColorTableEntry> getGlobalColorTable() const;
    const std::vector<ApplicationExtension>& getApplicationExtensions() const;

private:
    uint16_t readLittleEndian();
    std::vector<ColorTableEntry> readColorTable(int size);
    ApplicationExtension readApplicationExtension();

    GifHeader header;
    std::vector<ColorTableEntry> globalColorTable;
    bool hasGlobalColorTable;
    int colorTableSize;
    std::vector<ApplicationExtension> applicationExtensions;
    std::ifstream file;
};

#endif // GIF89AREADER_H
