/*
* AspectRatioFeatureModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the aspect ratio feature model.
*/

#include "AspectRatioFeatureModel.h"
#include "DetailAspectRatioFeatureModel.h"

AspectRatioFeatureModel::AspectRatioFeatureModel(QObject *parent)
    : AbstractFeatureModel(parent)
{
}

AspectRatioFeatureModel::AspectRatioFeatureModel(FeatureType featureType, QObject *parent)
    : AbstractFeatureModel(featureType, parent)
{
    m_detailAspectRatioFeatureModel = std::make_shared<DetailAspectRatioFeatureModel>(parent);
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

QObject *AspectRatioFeatureModel::detailFeatureModel() const
{
    return m_detailAspectRatioFeatureModel.get();
}
