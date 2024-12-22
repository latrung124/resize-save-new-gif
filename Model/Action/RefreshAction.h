/*
* RefreshAction.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the refresh action.
*/

#ifndef REFRESHACTION_H
#define REFRESHACTION_H

#include "AbstractAction.h"

class RefreshAction : public AbstractAction
{
    Q_OBJECT

public:
    explicit RefreshAction(QObject *parent = nullptr);
    ~RefreshAction() override;

    virtual void execute() override;
};

#endif // REFRESHACTION_H