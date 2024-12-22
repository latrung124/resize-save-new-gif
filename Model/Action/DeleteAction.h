/*
* DeleteAction.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the delete action.
*/

#ifndef DELETEACTION_H
#define DELETEACTION_H

#include "AbstractAction.h"

class DeleteAction : public AbstractAction
{
    Q_OBJECT

public:
    explicit DeleteAction(QObject *parent = nullptr);
    ~DeleteAction() override;

    virtual void execute() override;
};

#endif // DELETEACTION_H