/*
* ImageController.cpp
* Author: trung.la
* Date: 2024-12-25
* This is the ImageController class source file.
*/

#include "ImageController.h"

#include <QQmlApplicationEngine>
#include <QDebug>

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

void ImageController::onModuleInitialized(EngineWPtr engine)
{
    m_engine = engine;
    if (!initImageModel()) {
        qDebug() << "init ImageModel failed!";
    } else {
        qDebug() << "init ImageModel success!";
    }
}

void ImageController::onModuleDestroyed()
{
    m_imageModel->deleteLater();
}

bool ImageController::initImageModel()
{
    auto engine = m_engine.lock();
    if (!engine) {
        return false;
    }

    auto root = engine->rootObjects().first();
    if (!root) {
        return false;
    }

    auto imageObj =  root->findChild<QObject*>("imageContent");
    if (!imageObj) {
        return false;
    }

    imageObj->setProperty("imageModel", QVariant::fromValue(m_imageModel.get()));
    return true;
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
