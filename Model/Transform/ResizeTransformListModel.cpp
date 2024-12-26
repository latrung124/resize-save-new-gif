/*
* ResizeTransformListModel.cpp
* Author: Trung La
* Date: 2024-12-26
* Description: This file contains the implementation for the resize transform list model.
*/

#include "ResizeTransformListModel.h"
#include "ResizeTransformModel.h"

ResizeTransformListModel::ResizeTransformListModel(QObject *parent)
    : AbstractTransformListModel(parent)
{
    m_resizeTransformModels.push_back(std::make_shared<ResizeTransformModel>(TransformType::ResizeWidth, "", "Resize Width"));
    m_resizeTransformModels.push_back(std::make_shared<ResizeTransformModel>(TransformType::ResizeHeight, "", "Resize Height"));
}

ResizeTransformListModel::~ResizeTransformListModel()
{
}

int ResizeTransformListModel::rowCount(const QModelIndex &parent) const
{
    return m_resizeTransformModels.size();
}

QVariant ResizeTransformListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_resizeTransformModels.size())
        return QVariant();

    const ResizeTransformModelPtr &resizeTransformModel = m_resizeTransformModels[index.row()];
    switch (role)
    {
    case NameRole:
        return QVariant::fromValue(resizeTransformModel->name());
    case IconSourceRole:
        return QVariant::fromValue(resizeTransformModel->iconSource());
    case TransformTypeRole:
        return QVariant::fromValue(resizeTransformModel->transformType());
    }

    return QVariant();
}

QHash<int, QByteArray> ResizeTransformListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconSourceRole] = "iconSource";
    roles[TransformTypeRole] = "transformType";
    return roles;
}

void ResizeTransformListModel::onTransformTrigger(int index)
{
    if (index < 0 || index >= m_resizeTransformModels.size())
        return;

    const ResizeTransformModelPtr &resizeTransformModel = m_resizeTransformModels[index];
    const TransformType type = resizeTransformModel->transformType();

    switch (type)
    {
    case TransformType::ResizeWidth:
        emit resizeTransformModel->resizeWidth(240); // TODO: get width from image
        break;
    case TransformType::ResizeHeight:
        emit resizeTransformModel->resizeHeight(240); // TODO: get height from image
        break;
    default:
        break;
    }
}

