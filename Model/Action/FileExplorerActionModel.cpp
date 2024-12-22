/*
* FileExplorerActionModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the file explorer feature model.
*/

#include "FileExplorerActionModel.h"
#include "FileExplorerAction.h"

FileExplorerActionModel::FileExplorerActionModel(QObject *parent)
    : AbstractActionModel(parent)
{
    m_action = std::make_unique<FileExplorerAction>();
}

FileExplorerActionModel::~FileExplorerActionModel()
{
}

QString FileExplorerActionModel::icon() const
{
    return "Resources/file-explorer.png";
}

QObject* FileExplorerActionModel::action() const
{
    return m_action.get();
}

