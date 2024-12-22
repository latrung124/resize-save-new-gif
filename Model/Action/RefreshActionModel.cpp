/*
* RefreshActionModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the refresh action model.
*/

#include "RefreshActionModel.h"
#include "RefreshAction.h"

RefreshActionModel::RefreshActionModel(QObject *parent)
    : AbstractActionModel(parent)
{
    m_action = std::make_unique<RefreshAction>();
}

RefreshActionModel::~RefreshActionModel()
{
}

QString RefreshActionModel::icon() const
{
    return "Resources/refresh.png";
}

QObject* RefreshActionModel::action() const
{
    return m_action.get();
}
