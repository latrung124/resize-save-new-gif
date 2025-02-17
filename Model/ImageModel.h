/*
* ImageModel.h
* Author: trung.la
* Date: 2024-12-25
* This is a simple implementation of the ImageModel class.
*/

#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include "ImageTypeClass.h"

#include <QObject>
#include <QString>

class ImageModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ImageType imageType READ imageType WRITE setImageType NOTIFY imageTypeChanged)
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(int rotationAngle READ rotationAngle WRITE setRotationAngle NOTIFY rotationAngleChanged)
    Q_PROPERTY(int flipType READ flipType WRITE setFlipType NOTIFY flipTypeChanged)

public:
    ImageModel(QObject *parent = nullptr);
    ~ImageModel();

    ImageType imageType() const;
    void setImageType(const ImageType &imageType);

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

    QString imageSource() const;
    void setImageSource(const QString &imageSource);

    int rotationAngle() const;
    void setRotationAngle(int rotationAngle);

    int flipType() const;
    void setFlipType(int flipType);

signals:
    void imageTypeChanged();
    void imageSourceChanged();
    void widthChanged();
    void heightChanged();
    void rotationAngleChanged();
    void flipTypeChanged();
    void updateImageSize(int width, int height);

private:
    void resetImage();

    ImageType m_imageType;
    QString m_imageSource;
    int m_rotationAngle;
    int m_flipType;
    int m_width;
    int m_height;
};

#endif // IMAGEMODEL_H
