/*
* SideBarModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the side bar model.
*/

#include "SideBarModel.h"
#include "AbstractFeatureModel.h"
#include "AspectRatioFeatureModel.h"
#include "CropFeatureModel.h"

SideBarModel::SideBarModel(QObject *parent)
    : QObject(parent)
{
    m_featureModels.push_back(std::make_shared<AspectRatioFeatureModel>(AbstractFeatureModel::FeatureType::AspectRatio, this));
    m_featureModels.push_back(std::make_shared<CropFeatureModel>(AbstractFeatureModel::FeatureType::Crop, this));
}

SideBarModel::~SideBarModel()
{
}
