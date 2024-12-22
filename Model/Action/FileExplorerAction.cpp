/*
* FileExplorerAction.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the file explorer action.
*/

#include "FileExplorerAction.h"

FileExplorerAction::FileExplorerAction(QObject *parent)
    : AbstractAction(parent)
{
    m_actionType = ActionType::FileExplorer;
}

FileExplorerAction::~FileExplorerAction()
{
}

void FileExplorerAction::execute()
{
    // TODO: Implement the file explorer action
}
