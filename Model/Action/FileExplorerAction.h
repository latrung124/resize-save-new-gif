/*
* FileExplorerAction.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the file explorer action.
*/

#ifndef FILEEXPLORERACTION_H
#define FILEEXPLORERACTION_H

#include "AbstractAction.h"

class FileExplorerAction : public AbstractAction
{
    Q_OBJECT

public:
    explicit FileExplorerAction(QObject *parent = nullptr);
    ~FileExplorerAction() override;

    virtual void execute() override;

signals:
    void fileSelected(const QString &filePath);
};

#endif // FILEEXPLORERACTION_H