/*
* CropFeatureModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the crop feature model.
*/

#ifndef CROPFEATUREMODEL_H
#define CROPFEATUREMODEL_H

#include "AbstractFeatureModel.h"

enum FeatureType : uint16_t;

class CropFeatureModel : public AbstractFeatureModel
{
    Q_OBJECT

public:
    explicit CropFeatureModel(QObject *parent = nullptr);
    CropFeatureModel(FeatureType featureType, QObject *parent = nullptr);
    ~CropFeatureModel() override;
};

#endif // CROPFEATUREMODEL_H