/*
* FlipTransformModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the flip transform model.
*/

#include "FlipTransformModel.h"
#include "ImageController.h"

FlipTransformModel::FlipTransformModel(QObject *parent)
    : AbstractTransformModel(parent)
{
}

FlipTransformModel::FlipTransformModel(
    const TransformType &transformType,
    const QString &iconSource,
    const QString &name, QObject *parent)
    : AbstractTransformModel(transformType, iconSource, name)
{
    startConnection();
}

FlipTransformModel::~FlipTransformModel()
{
    endConnection();
}

void FlipTransformModel::startConnection()
{
    connect(this, &FlipTransformModel::flip, ImageController::instance(), &ImageController::slotUpdateIsFlipped);
}

void FlipTransformModel::endConnection()
{
    disconnect(this, &FlipTransformModel::flip, ImageController::instance(), &ImageController::slotUpdateIsFlipped);
}
