/*
* IGifConverter.h
* Author: trung.la
* Date: 2024-12-20
*/

#ifndef IGIFCONVERTER_H
#define IGIFCONVERTER_H

class IGifConverter
{
public:
    IGifConverter() = default;
    ~IGifConverter() = default;

    virtual void createGifFileFromQImage(const char* srcFileName, const char* destFileName) = 0;
};

#endif // IGIFCONVERTER_H