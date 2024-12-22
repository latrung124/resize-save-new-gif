/*
* CropFeatureModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the crop feature model.
*/

#include "CropFeatureModel.h"

CropFeatureModel::CropFeatureModel(QObject *parent)
    : AbstractFeatureModel(parent)
{
}

CropFeatureModel::CropFeatureModel(FeatureType featureType, QObject *parent)
    : AbstractFeatureModel(featureType, parent)
{
}

CropFeatureModel::~CropFeatureModel()
{
}