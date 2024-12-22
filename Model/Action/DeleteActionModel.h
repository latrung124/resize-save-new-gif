/*
* DeleteActionModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the delete action model.
*/

#ifndef DELETEACTIONMODEL_H
#define DELETEACTIONMODEL_H

#include "AbstractActionModel.h"

class DeleteActionModel : public AbstractActionModel
{
    Q_OBJECT

public:
    DeleteActionModel(QObject *parent = nullptr);
    ~DeleteActionModel();

    QString icon() const override;
    QObject* action() const override;
};

#endif // DELETEACTIONMODEL_H