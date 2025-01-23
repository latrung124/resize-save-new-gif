/*
* IGifConverter.h
* Author: trung.la
* Date: 2024-12-20
*/

#ifndef IGIFCONVERTER_H
#define IGIFCONVERTER_H

namespace gif_util::gif_89a {
    struct TransformDescriptor;
}

class IGifConverter
{
public:
    IGifConverter() = default;
    ~IGifConverter() = default;

    virtual bool readGifFile(const char* fileName) = 0;
    virtual bool createGifFileFromQImage(const char* srcFileName, const char* destFileName, const gif_util::gif_89a::TransformDescriptor& transformDescriptor) = 0;
    virtual void printInfoOfGif(const char* fileName) = 0;
};

#endif // IGIFCONVERTER_H
