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
    , m_width(0)
    , m_height(0)
{
}

ResizeTransformModel::ResizeTransformModel(const TransformType &transformType
    , const QString &iconSource
    , const QString &name
    , QObject *parent)
    : AbstractTransformModel(transformType, iconSource, name, parent)
    , m_width(0)
    , m_height(0)
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

void ResizeTransformModel::transformResizeTrigger(int width, int height)
{
    emit resizeWidth(width);
    emit resizeHeight(height);
}

void ResizeTransformModel::onUpdateImageSize(int width, int height)
{
    setWidth(width);
    setHeight(height);
}

int ResizeTransformModel::width() const
{
    return m_width;
}

void ResizeTransformModel::setWidth(int width)
{
    m_width = width;
    emit widthChanged();
}

int ResizeTransformModel::height() const
{
    return m_height;
}

void ResizeTransformModel::setHeight(int height)
{
    m_height = height;
    emit heightChanged();
}
