/*
* SideBarModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the side bar model.
*/

#include "SideBarModel.h"
#include "AspectRatioFeatureModel.h"
#include "CropFeatureModel.h"
#include "DetailAspectRatioFeatureModel.h"
#include "DetailCropFeatureModel.h"

SideBarModel::SideBarModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_featureModels.push_back(std::make_shared<AspectRatioFeatureModel>(FeatureType::AspectRatio, this));
    m_featureModels.push_back(std::make_shared<CropFeatureModel>(FeatureType::Crop, this));
}

SideBarModel::~SideBarModel()
{
}

int SideBarModel::rowCount(const QModelIndex &parent) const
{
    return m_featureModels.size();
}

QVariant SideBarModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_featureModels.size() || index.row() < 0) {
        return QVariant();
    }

    switch (role) {
    case IconRole:
        return m_featureModels[index.row()]->icon();
    case SourceRole:
        return m_featureModels[index.row()]->source();
    case DetailFeatureModelRole: {
        if (m_featureModels[index.row()]->featureType() == FeatureType::AspectRatio) {
            return QVariant::fromValue(dynamic_cast<DetailAspectRatioFeatureModel*>(m_featureModels[index.row()]->detailFeatureModel()));
        } else if (m_featureModels[index.row()]->featureType() == FeatureType::Crop) {
            return QVariant::fromValue(dynamic_cast<DetailCropFeatureModel*>(m_featureModels[index.row()]->detailFeatureModel()));
        } else {
            return QVariant();
        }
    }
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> SideBarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IconRole] = "icon";
    roles[SourceRole] = "source";
    roles[DetailFeatureModelRole] = "detailFeatureModel";
    return roles;
}


