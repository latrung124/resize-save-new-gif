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

public:
    explicit ResizeTransformModel(QObject *parent = nullptr);
    ResizeTransformModel(const TransformType &transformType
        , const QString &iconSource
        , const QString &name
        , QObject *parent = nullptr);
    ~ResizeTransformModel() override;

signals:
    void resizeWidth(int width);
    void resizeHeight(int height);

private:
    void startConnection();
    void endConnection();
};

#endif // RESIZETRANSFORMMODEL_H