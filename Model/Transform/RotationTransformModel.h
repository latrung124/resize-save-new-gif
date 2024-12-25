/*
* RotationTransformModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the rotation transform model.
*/

#ifndef ROTATIONTRANSFORMMODEL_H
#define ROTATIONTRANSFORMMODEL_H

#include "AbstractTransformModel.h"

class RotationTransformModel : public AbstractTransformModel
{
    Q_OBJECT

public:
    explicit RotationTransformModel(QObject *parent = nullptr);
    RotationTransformModel(const TransformType &transformType,
        const QString &iconSource,
        const QString &name,
        QObject *parent = nullptr);
    ~RotationTransformModel() override;

signals:
    void rotate(int angle);

private:
    void startConnection();
    void endConnection();
};

#endif // ROTATIONTRANSFORMMODEL_H
