/*
* RotationTransformModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the rotation transform model.
*/

#include "RotationTransformModel.h"

RotationTransformModel::RotationTransformModel(QObject *parent)
    : AbstractTransformModel(parent)
{
}

RotationTransformModel::RotationTransformModel(const QString &iconSource, const QString &name, QObject *parent)
    : AbstractTransformModel(iconSource, name)
{
}

RotationTransformModel::~RotationTransformModel()
{
}

void RotationTransformModel::applyTransform(const QImage &image)
{
    Q_UNUSED(image);
}
