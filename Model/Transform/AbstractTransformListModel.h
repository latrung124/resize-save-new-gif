/*
* AbstractTransformListModel.h
* Author: Trung La
* Date: 2024-12-26
* Description: This file contains the definition for the abstract transform list model.
*/

#ifndef ABSTRACTTRANSFORMLISTMODEL_H
#define ABSTRACTTRANSFORMLISTMODEL_H

#include <QAbstractListModel>

class AbstractTransformModel;

class AbstractTransformListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    using AbstractTransformModelPtr = std::shared_ptr<AbstractTransformModel>;

    AbstractTransformListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    ~AbstractTransformListModel() override {}

public slots:
    virtual void onTransformTrigger(int index) = 0;
};

#endif // ABSTRACTTRANSFORMLISTMODEL_H