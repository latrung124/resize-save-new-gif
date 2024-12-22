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
}   

AspectRatioFeatureModel::~AspectRatioFeatureModel()
{
}

QString AspectRatioFeatureModel::source() const
{
    return m_source;
}

void AspectRatioFeatureModel::setSource(const QString &source)
{
    m_source = source;
    emit sourceChanged();
}

QObject *AspectRatioFeatureModel::rotationTransformListModel() const
{
    return static_cast<QObject *>(m_rotationTransformListModel.get());
}

QObject *AspectRatioFeatureModel::flipTransformListModel() const
{
    return static_cast<QObject *>(m_flipTransformListModel.get());
}
