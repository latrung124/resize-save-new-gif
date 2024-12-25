/*
* FlipTransformListModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the flip transform list model.
*/

#include "FlipTransformListModel.h"
#include "FlipTransformModel.h"

FlipTransformListModel::FlipTransformListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_flipTransformModels.push_back(std::make_shared<FlipTransformModel>(TransformType::FlipHorizontalLeft, "Resources/flip-horizontal-left.png", "Flip Horizontal Left"));
    m_flipTransformModels.push_back(std::make_shared<FlipTransformModel>(TransformType::FlipHorizontalRight, "Resources/flip-horizontal-right.png", "Flip Horizontal Right"));
}

FlipTransformListModel::~FlipTransformListModel()
{
}

int FlipTransformListModel::rowCount(const QModelIndex &parent) const
{
    return m_flipTransformModels.size();
}

QVariant FlipTransformListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_flipTransformModels.size())
        return QVariant();

    const FlipTransformModelPtr &flipTransformModel = m_flipTransformModels[index.row()];
    switch (role)
    {
    case NameRole:
        return QVariant::fromValue(flipTransformModel->name());
    case IconSourceRole:
        return QVariant::fromValue(flipTransformModel->iconSource());
    case TransformTypeRole:
        return QVariant::fromValue(flipTransformModel->transformType());
    }

    return QVariant();
}

QHash<int, QByteArray> FlipTransformListModel::roleNames() const
{
    return {
        {NameRole, "name"},
        {IconSourceRole, "icon"},
        {TransformTypeRole, "transformType"}
    };
}

void FlipTransformListModel::onFlipTransformSelected(int index, int flipType)
{
    if (index < 0 && index >= m_flipTransformModels.size()) {
        return;
    }

    const FlipTransformModelPtr &flipTransformModel = m_flipTransformModels[index];
    emit flipTransformModel->flip(flipType);
}

