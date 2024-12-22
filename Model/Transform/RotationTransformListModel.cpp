/*
* RotationTransformListModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the rotation transform list model.
*/

#include "RotationTransformListModel.h"
#include "RotationTransformModel.h"

RotationTransformListModel::RotationTransformListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_rotationTransformModels.push_back(std::make_shared<RotationTransformModel>("Resources/rotate-90-degrees.png", "Rotate Left"));
    m_rotationTransformModels.push_back(std::make_shared<RotationTransformModel>("Resources/rotate-90-degrees-cw.png", "Rotate Right"));
}

RotationTransformListModel::~RotationTransformListModel()
{
}

int RotationTransformListModel::rowCount(const QModelIndex &parent) const
{
    return m_rotationTransformModels.size();
}

QVariant RotationTransformListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_rotationTransformModels.size())
        return QVariant();

    const RotationTransformModelPtr &rotationTransformModel = m_rotationTransformModels[index.row()];
    switch (role)
    {
    case NameRole:
        return QVariant::fromValue(rotationTransformModel->name());
    case IconSourceRole:
        return QVariant::fromValue(rotationTransformModel->iconSource());
    }

    return QVariant();
}

QHash<int, QByteArray> RotationTransformListModel::roleNames() const
{
    return {
        {NameRole, "name"},
        {IconSourceRole, "iconSource"}
    };
}
