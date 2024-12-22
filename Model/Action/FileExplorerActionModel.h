/*
* FileExplorerActionModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the file explorer feature model.
*/

#ifndef FILEEXPLORERACTIONMODEL_H
#define FILEEXPLORERACTIONMODEL_H

#include "AbstractActionModel.h"
#include <memory>

class FileExplorerActionModel : public AbstractActionModel
{
    Q_OBJECT

public:
    explicit FileExplorerActionModel(QObject *parent = nullptr);
    ~FileExplorerActionModel() override;

    QString icon() const override;
    QObject* action() const override;
};

#endif // FILEEXPLORERACTIONMODEL_H