/*
* AbstractActionModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the abstract action model.
*/

#ifndef ABSTRACTACTIONMODEL_H
#define ABSTRACTACTIONMODEL_H

#include "AbstractAction.h"

#include <QObject>

class AbstractActionModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString icon READ icon CONSTANT)
    Q_PROPERTY(QObject* action READ action CONSTANT)

public:
    using AbstractActionPtr = std::shared_ptr<AbstractAction>;

    explicit AbstractActionModel(QObject *parent = nullptr);
    virtual ~AbstractActionModel() override;

    virtual QString icon() const = 0;
    virtual QObject* action() const = 0;

protected:
    AbstractActionPtr m_action;
};

#endif // ABSTRACTACTIONMODEL_H
