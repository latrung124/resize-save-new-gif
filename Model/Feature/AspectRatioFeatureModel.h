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

enum FeatureType : uint16_t;

class RotationTransformListModel;
class FlipTransformListModel;

class AspectRatioFeatureModel : public AbstractFeatureModel
{
    Q_OBJECT
    Q_PROPERTY(QObject *rotationTransformListModel READ rotationTransformListModel CONSTANT)
    Q_PROPERTY(QObject *flipTransformListModel READ flipTransformListModel CONSTANT)

public:
    using RotationTransformListModelPtr = std::shared_ptr<RotationTransformListModel>;
    using FlipTransformListModelPtr = std::shared_ptr<FlipTransformListModel>;

    explicit AspectRatioFeatureModel(QObject *parent = nullptr);
    AspectRatioFeatureModel(FeatureType featureType, QObject *parent = nullptr);
    ~AspectRatioFeatureModel() override;

    QString source() const override;
    QString icon() const override;

    QObject *rotationTransformListModel() const;
    QObject *flipTransformListModel() const;

private:
    RotationTransformListModelPtr m_rotationTransformListModel;
    FlipTransformListModelPtr m_flipTransformListModel;
};

#endif // ASPECTRATIOFEATUREMODEL_H
