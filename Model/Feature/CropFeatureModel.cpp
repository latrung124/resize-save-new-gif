/*
* CropFeatureModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the crop feature model.
*/

#include "CropFeatureModel.h"
#include "DetailCropFeatureModel.h"

CropFeatureModel::CropFeatureModel(QObject *parent)
    : AbstractFeatureModel(parent)
{
}

CropFeatureModel::CropFeatureModel(FeatureType featureType, QObject *parent)
    : AbstractFeatureModel(featureType, parent)
{
    m_detailCropFeatureModel = std::make_shared<DetailCropFeatureModel>(parent);
}

CropFeatureModel::~CropFeatureModel()
{
}

QString CropFeatureModel::source() const
{
    return "CropFeature.qml";
}

QString CropFeatureModel::icon() const
{
    return "Resources/crop-sidebar-icon.png";
}

QObject *CropFeatureModel::detailFeatureModel() const
{
    return m_detailCropFeatureModel.get();
}

