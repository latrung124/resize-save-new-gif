/*
* RefreshAction.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the refresh action.
*/

#include "RefreshAction.h"

RefreshAction::RefreshAction(QObject *parent)
    : AbstractAction(parent)
{
    m_actionType = ActionType::Refresh;
}

RefreshAction::~RefreshAction()
{
}

void RefreshAction::execute()
{
    // TODO: Implement the refresh action
}
