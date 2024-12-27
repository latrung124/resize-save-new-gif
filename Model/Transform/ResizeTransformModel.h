/*
* ResizeTransformModel.h
* Author: Trung La
* Date: 2024-12-26
* Description: This file contains the definition for the resize transform model.
*/

#ifndef RESIZETRANSFORMMODEL_H
#define RESIZETRANSFORMMODEL_H

#include "AbstractTransformModel.h"

class ResizeTransformModel : public AbstractTransformModel
{
    Q_OBJECT
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)

public:
    explicit ResizeTransformModel(QObject *parent = nullptr);
    ResizeTransformModel(const TransformType &transformType
        , const QString &iconSource
        , const QString &name
        , QObject *parent = nullptr);
    ~ResizeTransformModel() override;

    int width() const;
    void setWidth(int width);
    int height() const;
    void setHeight(int height);

signals:
    void resizeWidth(int width);
    void resizeHeight(int height);
    void widthChanged();
    void heightChanged();

public slots:
    void onResize(int width, int height);
    void onUpdateImageSize(int width, int height);

private:
    void startConnection();
    void endConnection();

    int m_width;
    int m_height;
};

#endif // RESIZETRANSFORMMODEL_H
