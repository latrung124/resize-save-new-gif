/*
* SideBarModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the side bar model.
*/

#include "SideBarModel.h"
#include "AspectRatioFeatureModel.h"
#include "CropFeatureModel.h"

SideBarModel::SideBarModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_featureModels.push_back(std::make_shared<AspectRatioFeatureModel>(this));
    m_featureModels.push_back(std::make_shared<CropFeatureModel>(this));
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
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> SideBarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IconRole] = "icon";
    roles[SourceRole] = "source";
    return roles;
}

