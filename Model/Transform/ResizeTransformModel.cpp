/*
* ResizeTransformModel.cpp
* Author: Trung La
* Date: 2024-12-26
* Description: This file contains the implementation for the resize transform model.
*/

#include "ResizeTransformModel.h"
#include "ImageController.h"

ResizeTransformModel::ResizeTransformModel(QObject *parent)
    : AbstractTransformModel(parent)
{
}

ResizeTransformModel::ResizeTransformModel(const TransformType &transformType
    , const QString &iconSource
    , const QString &name
    , QObject *parent)
    : AbstractTransformModel(transformType, iconSource, name, parent)
{
    startConnection();
}

ResizeTransformModel::~ResizeTransformModel()
{
    endConnection();
}

void ResizeTransformModel::startConnection()
{
    connect(this, &ResizeTransformModel::resizeWidth, ImageController::instance(), &ImageController::slotResizeWidth);
    connect(this, &ResizeTransformModel::resizeHeight, ImageController::instance(), &ImageController::slotResizeHeight);
}

void ResizeTransformModel::endConnection()
{
    disconnect(this, &ResizeTransformModel::resizeWidth, ImageController::instance(), &ImageController::slotResizeWidth);
    disconnect(this, &ResizeTransformModel::resizeHeight, ImageController::instance(), &ImageController::slotResizeHeight);
}
