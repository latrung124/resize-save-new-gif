/*
* ImageTypeClass.h
* Author: trung.la
* Date: 2024-12-24
* This is a simple implementation of the ImageTypeClass class.
*/

#ifndef IMAGETYPECLASS_H
#define IMAGETYPECLASS_H

#include <QObject>

class ImageTypeClass
{
    Q_GADGET

public:
    enum class EImageType : uint16_t
    {
        None = 0,
        PNG,
        JPEG,
        BMP,
        GIF
    };
    Q_ENUM(EImageType)

private:
    explicit ImageTypeClass();
};
typedef ImageTypeClass::EImageType ImageType;

#endif // IMAGETYPECLASS_H