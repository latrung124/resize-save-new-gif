/*
* FlipTransformModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the flip transform model.
*/

#ifndef FLIPTRANSFORMMODEL_H
#define FLIPTRANSFORMMODEL_H

#include "AbstractTransformModel.h"

class FlipTransformModel : public AbstractTransformModel
{
    Q_OBJECT

public:
    explicit FlipTransformModel(QObject *parent = nullptr);
    FlipTransformModel(const QString &iconSource, const QString &name, QObject *parent = nullptr);
    ~FlipTransformModel() override;

    TransformType transformType() const override;

public slots:
    void applyTransform(const QImage &image) override;
};

#endif // FLIPTRANSFORMMODEL_H