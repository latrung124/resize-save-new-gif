/*
* DetailCropFeatureModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the detail crop feature model.
*/

#ifndef DETAILCROPFEATUREMODEL_H
#define DETAILCROPFEATUREMODEL_H

#include <QObject>

class DetailCropFeatureModel : public QObject
{
    Q_OBJECT

public:
    explicit DetailCropFeatureModel(QObject *parent = nullptr);
    ~DetailCropFeatureModel() override;
};

#endif // DETAILCROPFEATUREMODEL_H