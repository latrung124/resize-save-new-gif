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

class ImageController : public QObject
{
    Q_OBJECT

public:
    static ImageController *instance();
    ~ImageController() = default;

public slots:
    void slotUpdateImageType(const ImageType &imageType);
    void slotUpdateImageSource(const QString &imageSource);
    void slotUpdateRotationAngle(int rotationAngle);
    void slotUpdateIsFlipped(int flipType);

private:
    explicit ImageController(QObject *parent = nullptr);
    std::unique_ptr<ImageModel> m_imageModel;
};
#endif // IMAGECONTROLLER_H
