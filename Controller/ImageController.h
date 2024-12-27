/*
* ImageController.h
* Author: trung.la
* Date: 2024-12-25
* This is a simple implementation of the ImageController class.
*/

#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <QObject>
#include <memory>

#include "ImageModel.h"

class QQmlApplicationEngine;

class ImageController : public QObject
{
    Q_OBJECT

public:
    using EngineWPtr = std::weak_ptr<QQmlApplicationEngine>;

    static ImageController *instance();
    ~ImageController() = default;

signals:
    void updateImageSize(int width, int height);

public slots:
    void onModuleInitialized(EngineWPtr engine);
    void onModuleDestroyed();

    void slotUpdateImageLoaded();
    void slotUpdateImageType(const ImageType &imageType);
    void slotUpdateImageSource(const QString &imageSource);
    void slotUpdateRotationAngle(int rotationAngle);
    void slotUpdateIsFlipped(int flipType);
    void slotResizeWidth(int width);
    void slotResizeHeight(int height);

private:
    explicit ImageController(QObject *parent = nullptr);
    bool initImageModel();

    std::unique_ptr<ImageModel> m_imageModel;
    EngineWPtr m_engine;
};
#endif // IMAGECONTROLLER_H
