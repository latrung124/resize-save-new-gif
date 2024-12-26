/*
* RotationTransformListModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the rotation transform list model.
*/

#include "RotationTransformListModel.h"
#include "RotationTransformModel.h"
#include <QDebug>

RotationTransformListModel::RotationTransformListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_rotationTransformModels.push_back(std::make_shared<RotationTransformModel>(TransformType::RotateLeft, "Resources/rotate-90-degrees.png", "Rotate Left"));
    m_rotationTransformModels.push_back(std::make_shared<RotationTransformModel>(TransformType::RotateRight,  "Resources/rotate-90-degrees-cw.png", "Rotate Right"));
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
    case TransformTypeRole:
        return QVariant::fromValue(rotationTransformModel->transformType());
    }

    return QVariant();
}

QHash<int, QByteArray> RotationTransformListModel::roleNames() const
{
    return {
        {NameRole, "name"},
        {IconSourceRole, "icon"},
        {TransformTypeRole, "transformType"}
    };
}

void RotationTransformListModel::onTransformTrigger(int index)
{
    if (index < 0 && index >= m_rotationTransformModels.size()) {
        return;
    }

    const RotationTransformModelPtr &rotationTransformModel = m_rotationTransformModels[index];
    const TransformType type = rotationTransformModel->transformType();

    switch (type) {
    case TransformType::RotateLeft:
        emit rotationTransformModel->rotate(-90);
        break;
    case TransformType::RotateRight:
        emit rotationTransformModel->rotate(90);
        break;
    default:
        break;
    }
}
