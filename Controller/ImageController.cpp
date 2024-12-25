/*
* ImageController.cpp
* Author: trung.la
* Date: 2024-12-25
* This is the ImageController class source file.
*/

#include "ImageController.h"

ImageController::ImageController(QObject *parent)
    : QObject(parent)
    , m_imageModel(std::make_unique<ImageModel>())
{
}

ImageController *ImageController::instance()
{
    static ImageController instance;
    return &instance;
}

void ImageController::slotUpdateImageType(const ImageType &imageType)
{
    m_imageModel->setImageType(imageType);
}

void ImageController::slotUpdateImageSource(const QString &imageSource)
{
    m_imageModel->setImageSource(imageSource);
}

void ImageController::slotUpdateRotationAngle(int rotationAngle)
{
    m_imageModel->setRotationAngle(rotationAngle);
}

void ImageController::slotUpdateIsFlipped(int flipType)
{
    m_imageModel->setFlipType(flipType);
}
