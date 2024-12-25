/*
* FlipTransformModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the flip transform model.
*/

#ifndef FLIPTRANSFORMMODEL_H
#define FLIPTRANSFORMMODEL_H

#include "AbstractTransformModel.h"

class FlipTransformModel : public AbstractTransformModel
{
    Q_OBJECT

public:
    explicit FlipTransformModel(QObject *parent = nullptr);
    FlipTransformModel(const TransformType &transformType
        , const QString &iconSource
        , const QString &name
        , QObject *parent = nullptr);
    ~FlipTransformModel() override;

signals:
    void flip(int flipType);

private:
    void startConnection();
    void endConnection();
};

#endif // FLIPTRANSFORMMODEL_H