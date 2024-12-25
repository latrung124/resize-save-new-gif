/*
* RotationTransformModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the rotation transform model.
*/

#include "RotationTransformModel.h"
#include "ImageController.h"

RotationTransformModel::RotationTransformModel(QObject *parent)
    : AbstractTransformModel(parent)
{
}

RotationTransformModel::RotationTransformModel(
    const TransformType &transformType,
    const QString &iconSource,
    const QString &name,
    QObject *parent)
    : AbstractTransformModel(transformType, iconSource, name)
{
    startConnection();
}

RotationTransformModel::~RotationTransformModel()
{
    endConnection();
}

void RotationTransformModel::startConnection()
{
    connect(this, &RotationTransformModel::rotate, ImageController::instance(), &ImageController::slotUpdateRotationAngle);
}

void  RotationTransformModel::endConnection()
{
    disconnect(this, &RotationTransformModel::rotate, ImageController::instance(), &ImageController::slotUpdateRotationAngle);
}
