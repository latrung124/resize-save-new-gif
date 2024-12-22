/*
* AspectRatioFeatureModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the aspect ratio feature model.
*/

#include "AspectRatioFeatureModel.h"
#include "RotationTransformListModel.h"
#include "FlipTransformListModel.h"

AspectRatioFeatureModel::AspectRatioFeatureModel(QObject *parent)
    : AbstractFeatureModel(parent)
{
}

AspectRatioFeatureModel::AspectRatioFeatureModel(FeatureType featureType, QObject *parent)
    : AbstractFeatureModel(featureType, parent)
{
    m_rotationTransformListModel = std::make_shared<RotationTransformListModel>(parent);
    m_flipTransformListModel = std::make_shared<FlipTransformListModel>(parent);
}   

AspectRatioFeatureModel::~AspectRatioFeatureModel()
{
}

QString AspectRatioFeatureModel::source() const
{
    return "AspectRatioFeature.qml";
}

QString AspectRatioFeatureModel::icon() const
{
    return "Resources/aspect-ratio.png";
}

QObject *AspectRatioFeatureModel::rotationTransformListModel() const
{
    return static_cast<QObject *>(m_rotationTransformListModel.get());
}

QObject *AspectRatioFeatureModel::flipTransformListModel() const
{
    return static_cast<QObject *>(m_flipTransformListModel.get());
}
