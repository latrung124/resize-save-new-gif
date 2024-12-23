/*
* AbstractAction.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the abstract action.
*/

#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include "ActionTypeClass.h"

#include <QObject>
#include <memory>

class AbstractAction : public QObject
{
    Q_OBJECT
public:
    explicit AbstractAction(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~AbstractAction() override = default;

    Q_INVOKABLE virtual void execute() = 0;

    Q_INVOKABLE ActionType actionType() const { return m_actionType; }

protected:
    ActionType m_actionType = ActionType::None;
};

#endif // ABSTRACTACTION_H
