/*
* Gif89aReader.cpp
* Author: trung.la
* Date: 2024-12-24
* This is a simple implementation of the Gif89aReader class.
*/

#include "Gif89aReader.h"

#include <QtGlobal>
#include <iostream>
#include <cstring>
#include <memory>

Gif89aReader::Gif89aReader()
    : hasGlobalColorTable(false)
    , colorTableSize(0)
{
}

Gif89aReader::~Gif89aReader() {
    if (file.is_open()) {
        file.close();
    }
}

uint16_t Gif89aReader::readLittleEndian()
{
    uint16_t value;
    file.read(reinterpret_cast<char*>(&value), 2);
    return value;
}

std::vector<gif_util::gif_89a::ColorTableEntry> Gif89aReader::readColorTable(int size) {
    std::vector<gif_util::gif_89a::ColorTableEntry> colorTable(size);
    readFromStream(file, colorTable.data());
    return colorTable;
}

bool Gif89aReader::readGifFile(const char *filename) {
    file.open(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    // Read header
    readFromStream(file, header.signature);
    readFromStream(file, header.version);
    if (std::strncmp(header.signature, "GIF", 3) != 0 ||
        std::strncmp(header.version, "89a", 3) != 0) {
        std::cerr << "Invalid GIF89a format" << std::endl;
        file.close();
        return false;
    }

    // Read logical screen descriptor
    header.width = readLittleEndian();
    header.height = readLittleEndian();
    readFromStream(file, &header.packed);
    readFromStream(file, &header.bgColorIndex);
    readFromStream(file, &header.pixelAspectRatio);

    // Read global color table if present
    hasGlobalColorTable = (header.packed & 0x80) != 0;
    colorTableSize = 1 << ((header.packed & 0x07) + 1);
    if (hasGlobalColorTable) {
        globalColorTable = readColorTable(colorTableSize);
    }

    // Read application extensions
    while (file.peek() == 0x21) {
        uint8_t extensionType;
        readFromStream(file, &extensionType);
        switch (extensionType) {
            case 0xFF: // Application extension
                applicationExtensions.push_back(readApplicationExtension());
                break;
            default: {
                std::cerr << "Unsupported extension type: " << (int)extensionType << std::endl;
                file.close();
                return false;
            }
        }
    }

    file.close();
    return true;
}

std::vector<gif_util::gif_89a::ColorTableEntry> Gif89aReader::getGlobalColorTable() const
{
    return globalColorTable;
}

gif_util::gif_89a::ApplicationExtension Gif89aReader::readApplicationExtension() {
    ApplicationExtension appExt;
    uint8_t blockSize;

    // Read block size (should be 11 for application extensions)
    file.read(reinterpret_cast<char*>(&blockSize), 1);
    if (blockSize != 11) {
        std::cerr << "Invalid application extension block size" << std::endl;
        return appExt;
    }
    // Read application identifier (8 bytes)
    char identifier[9] = {0};
    readFromStream(file, identifier);
    appExt.identifier = identifier;
    // Read authentication code (3 bytes)
    char authCode[4] = {0};
    readFromStream(file, authCode);
    appExt.authCode = authCode;
    // Read data sub-blocks
    while (file.read(reinterpret_cast<char*>(&blockSize), 1) && blockSize > 0) {
        size_t currentSize = appExt.data.size();
        appExt.data.resize(currentSize + blockSize);
        file.read(reinterpret_cast<char*>(appExt.data.data() + currentSize), blockSize);
        auto const datasubblock = appExt.data.data() + currentSize;
        readFromStream(file, datasubblock);
    }
    return appExt;
}

