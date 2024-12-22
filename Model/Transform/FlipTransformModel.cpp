/*
* FlipTransformModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the flip transform model.
*/

#include "FlipTransformModel.h"

FlipTransformModel::FlipTransformModel(QObject *parent)
    : AbstractTransformModel(parent)
{
}

FlipTransformModel::FlipTransformModel(const QString &iconSource, const QString &name, QObject *parent)
    : AbstractTransformModel(iconSource, name)
{
}

FlipTransformModel::~FlipTransformModel()
{
}

void FlipTransformModel::applyTransform(const QImage &image)
{
    Q_UNUSED(image);
}
