/*
* BottomBarModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the bottom bar model.
*/

#include "BottomBarModel.h"
#include "AbstractActionModel.h"
#include "FileExplorerActionModel.h"
#include "RefreshActionModel.h"
#include "DeleteActionModel.h"

BottomBarModel::BottomBarModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_actionModels.push_back(std::make_unique<FileExplorerActionModel>(this));
    m_actionModels.push_back(std::make_unique<RefreshActionModel>(this));
    m_actionModels.push_back(std::make_unique<DeleteActionModel>(this));
}

BottomBarModel::~BottomBarModel()
{
}

int BottomBarModel::rowCount(const QModelIndex &parent) const
{
    return m_actionModels.size();
}

QVariant BottomBarModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_actionModels.size()) {
        return QVariant();
    }

    const AbstractActionModelPtr &actionModel = m_actionModels[index.row()];
    switch (role)
    {
    case IconRole:
        return actionModel->icon();
    case ActionRole:
        return QVariant::fromValue(actionModel->action());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> BottomBarModel::roleNames() const
{
    return {{IconRole, "icon"},
            {ActionRole, "action"}};
}
