/*
* File: AbstractFeatureModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation of the abstract feature model.
*/

#include "AbstractFeatureModel.h"

AbstractFeatureModel::AbstractFeatureModel(QObject *parent)
    : QObject(parent)
{
}

AbstractFeatureModel::AbstractFeatureModel(FeatureType featureType, QObject *parent)
    : QObject(parent)
    , m_featureType(featureType)
{
}

AbstractFeatureModel::~AbstractFeatureModel()
{
}

AbstractFeatureModel::FeatureType AbstractFeatureModel::featureType() const
{
    return m_featureType;
}

