/*
* DetailAspectRatioFeatureModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the detail aspect ratio feature model.
*/

#include "ImageController.h"
#include "DetailAspectRatioFeatureModel.h"
#include "RotationTransformListModel.h"
#include "FlipTransformListModel.h"
#include "ResizeTransformModel.h"

DetailAspectRatioFeatureModel::DetailAspectRatioFeatureModel(QObject *parent)
    : QObject(parent)
{
    m_rotationTransformListModel = std::make_shared<RotationTransformListModel>(parent);
    m_flipTransformListModel = std::make_shared<FlipTransformListModel>(parent);
    m_resizeTransformModel = std::make_shared<ResizeTransformModel>(TransformType::Resize, "Resources/resize.png", "Resize", parent);

    connect(ImageController::instance(), &ImageController::updateImageSize, m_resizeTransformModel.get(), &ResizeTransformModel::onUpdateImageSize);
}

DetailAspectRatioFeatureModel::~DetailAspectRatioFeatureModel()
{
    disconnect(ImageController::instance(), &ImageController::updateImageSize, m_resizeTransformModel.get(), &ResizeTransformModel::onUpdateImageSize);
}

QObject *DetailAspectRatioFeatureModel::rotationTransformListModel() const
{
    return m_rotationTransformListModel.get();
}

QObject *DetailAspectRatioFeatureModel::flipTransformListModel() const
{
    return m_flipTransformListModel.get();
}

QObject *DetailAspectRatioFeatureModel::resizeTransformModel() const
{
    return m_resizeTransformModel.get();
}
