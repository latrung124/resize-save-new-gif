/*
* ImageModel.cpp
* Author: trung.la
* Date: 2024-12-25
* This is a simple implementation of the ImageModel class.
*/

#include "ImageModel.h"

ImageModel::ImageModel(QObject *parent)
    : QObject(parent)
    , m_imageType(ImageType::None)
    , m_imageSource("")
    , m_rotationAngle(0)
    , m_flipType(0)
{
}

ImageModel::~ImageModel()
{
}

ImageType ImageModel::imageType() const
{
    return m_imageType;
}

void ImageModel::setImageType(const ImageType &imageType)
{
    if (m_imageType == imageType) {
        return;
    }
    m_imageType = imageType;
    emit imageTypeChanged();
}

QString ImageModel::imageSource() const
{
    return m_imageSource;
}

void ImageModel::setImageSource(const QString &imageSource)
{
    if (m_imageSource == imageSource) {
        return;
    }
    m_imageSource = imageSource;
    emit imageSourceChanged();
}

int ImageModel::rotationAngle() const
{
    return m_rotationAngle;
}

void ImageModel::setRotationAngle(int rotationAngle)
{
    if (m_rotationAngle == rotationAngle) {
        return;
    }
    m_rotationAngle = rotationAngle;
    emit rotationAngleChanged();
}

int ImageModel::flipType() const
{
    return m_flipType;
}

void ImageModel::setFlipType(int flipType)
{
    if (m_flipType == flipType) {
        return;
    }
    m_flipType = flipType;
    emit flipTypeChanged();
}
