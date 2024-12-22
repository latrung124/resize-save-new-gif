/*
* RotationTransformModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the rotation transform model.
*/

#ifndef ROTATIONTRANSFORMMODEL_H
#define ROTATIONTRANSFORMMODEL_H

#include "AbstractTransformModel.h"

class RotationTransformModel : public AbstractTransformModel
{
    Q_OBJECT

public:
    explicit RotationTransformModel(QObject *parent = nullptr);
    RotationTransformModel(const QString &iconSource, const QString &name, QObject *parent = nullptr);
    ~RotationTransformModel() override;

public slots:
    void applyTransform(const QImage &image) override;

signals:
    void transformApplied(const QImage &image);
};

#endif // ROTATIONTRANSFORMMODEL_H