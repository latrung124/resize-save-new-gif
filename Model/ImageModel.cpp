/*
* ImageModel.cpp
* Author: trung.la
* Date: 2024-12-25
* This is a simple implementation of the ImageModel class.
*/

#include "ImageModel.h"

#include <QImage>
#include <QRegularExpression>

ImageModel::ImageModel(QObject *parent)
    : QObject(parent)
    , m_imageType(ImageType::None)
    , m_imageSource("")
    , m_rotationAngle(0)
    , m_flipType(1)
    , m_width(0)
    , m_height(0)
{
}

ImageModel::~ImageModel()
{
}

void ImageModel::resetImage()
{
    auto tempImageSource = m_imageSource;
    const auto fileName = tempImageSource.replace(QRegularExpression("^file:///+"), "");
    QImage image(fileName);
    if (image.isNull()) {
        setWidth(0);
        setHeight(0);
    } else {
        setWidth(image.width());
        setHeight(image.height());
    }
    setFlipType(1);
    m_rotationAngle = 0;
    emit updateImageSize(m_width, m_height);
    emit rotationAngleChanged();

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
    m_imageSource = imageSource;
    resetImage();
    emit imageSourceChanged();
}

int ImageModel::rotationAngle() const
{
    return m_rotationAngle;
}

void ImageModel::setRotationAngle(int rotationAngle)
{
    m_rotationAngle = (m_rotationAngle + rotationAngle) % 360;
    int tempWidth = m_width;
    m_width = m_height;
    m_height = tempWidth;
    emit updateImageSize(m_width, m_height);
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

int ImageModel::width() const
{
    return m_width;
}

void ImageModel::setWidth(int width)
{
    m_width = width;
    emit widthChanged();
}

int ImageModel::height() const
{
    return m_height;
}

void ImageModel::setHeight(int height)
{
    m_height = height;
    emit heightChanged();
}
