/*
* DetailAspectRatioFeatureModel
* DetailAspectRatioFeatureModel.qml
* Author: Trung La
* Date: 2024-12-22
* Description: DetailAspectRatioFeatureModel is a model for the aspect ratio feature.
*/

#ifndef DETAILASPECTRATIOFEATUREMODEL_H
#define DETAILASPECTRATIOFEATUREMODEL_H

#include <QObject>
#include <memory>

class RotationTransformListModel;
class FlipTransformListModel;

class DetailAspectRatioFeatureModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *rotationTransformListModel READ rotationTransformListModel CONSTANT)
    Q_PROPERTY(QObject *flipTransformListModel READ flipTransformListModel CONSTANT)

public:
    using RotationTransformListModelPtr = std::shared_ptr<RotationTransformListModel>;
    using FlipTransformListModelPtr = std::shared_ptr<FlipTransformListModel>;

    explicit DetailAspectRatioFeatureModel(QObject *parent = nullptr);
    ~DetailAspectRatioFeatureModel() override;

    QObject *rotationTransformListModel() const;
    QObject *flipTransformListModel() const;

private:
    RotationTransformListModelPtr m_rotationTransformListModel;
    FlipTransformListModelPtr m_flipTransformListModel;
};

#endif // DETAILASPECTRATIOFEATUREMODEL_H
