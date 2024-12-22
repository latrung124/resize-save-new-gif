/*
* DeleteActionModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the delete action model.
*/

#include "DeleteActionModel.h"
#include "DeleteAction.h"

DeleteActionModel::DeleteActionModel(QObject *parent)
    : AbstractActionModel(parent)
{
    m_action = std::make_unique<DeleteAction>();
}

DeleteActionModel::~DeleteActionModel()
{
}

QString DeleteActionModel::icon() const
{
    return "Resources/delete.png";
}

QObject* DeleteActionModel::action() const
{
    return m_action.get();
}

