/*
* CropFeatureModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the crop feature model.
*/

#ifndef CROPFEATUREMODEL_H
#define CROPFEATUREMODEL_H

#include "AbstractFeatureModel.h"
#include <memory>

class DetailCropFeatureModel;

class CropFeatureModel : public AbstractFeatureModel
{
    Q_OBJECT

public:
    using DetailCropFeatureModelPtr = std::shared_ptr<DetailCropFeatureModel>;

    explicit CropFeatureModel(QObject *parent = nullptr);
    CropFeatureModel(FeatureType featureType, QObject *parent = nullptr);
    ~CropFeatureModel() override;

    QString source() const override;
    QString icon() const override;
    QObject *detailFeatureModel() const override;

private:
    DetailCropFeatureModelPtr m_detailCropFeatureModel;
};

#endif // CROPFEATUREMODEL_H
