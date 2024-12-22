/*
* DetailAspectRatioFeatureModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the detail aspect ratio feature model.
*/

#include "DetailAspectRatioFeatureModel.h"
#include "RotationTransformListModel.h"
#include "FlipTransformListModel.h"

DetailAspectRatioFeatureModel::DetailAspectRatioFeatureModel(QObject *parent)
    : QObject(parent)
{
    m_rotationTransformListModel = std::make_shared<RotationTransformListModel>(parent);
    m_flipTransformListModel = std::make_shared<FlipTransformListModel>(parent);
}

DetailAspectRatioFeatureModel::~DetailAspectRatioFeatureModel()
{
}

QObject *DetailAspectRatioFeatureModel::rotationTransformListModel() const
{
    return m_rotationTransformListModel.get();
}

QObject *DetailAspectRatioFeatureModel::flipTransformListModel() const
{
    return m_flipTransformListModel.get();
}
