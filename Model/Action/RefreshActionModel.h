/*
* RefreshActionModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the refresh action model.
*/

#ifndef REFRESHACTIONMODEL_H
#define REFRESHACTIONMODEL_H

#include "AbstractActionModel.h"

class RefreshActionModel : public AbstractActionModel
{
    Q_OBJECT

public:
    RefreshActionModel(QObject *parent = nullptr);
    ~RefreshActionModel();

    QString icon() const override;
    QObject* action() const override;
};

#endif // REFRESHACTIONMODEL_H