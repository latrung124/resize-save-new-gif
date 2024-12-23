/*
* AspectRatioFeatureModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the aspect ratio feature model.
*/

#ifndef ASPECTRATIOFEATUREMODEL_H
#define ASPECTRATIOFEATUREMODEL_H

#include "AbstractFeatureModel.h"

#include <memory>

class DetailAspectRatioFeatureModel;
class AspectRatioFeatureModel : public AbstractFeatureModel
{
    Q_OBJECT

public:
    using DetailAspectRatioFeatureModelPtr = std::shared_ptr<DetailAspectRatioFeatureModel>;

    explicit AspectRatioFeatureModel(QObject *parent = nullptr);
    AspectRatioFeatureModel(FeatureType featureType, QObject *parent = nullptr);
    ~AspectRatioFeatureModel() override;

    QString source() const override;
    QString icon() const override;
    QObject *detailFeatureModel() const override;

private:
    DetailAspectRatioFeatureModelPtr m_detailAspectRatioFeatureModel;
};

#endif // ASPECTRATIOFEATUREMODEL_H
