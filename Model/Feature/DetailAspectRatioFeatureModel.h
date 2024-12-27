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
class ResizeTransformListModel;
class ResizeTransformModel;

class DetailAspectRatioFeatureModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *rotationTransformListModel READ rotationTransformListModel CONSTANT)
    Q_PROPERTY(QObject *flipTransformListModel READ flipTransformListModel CONSTANT)
    Q_PROPERTY(QObject *resizeTransformModel READ resizeTransformModel CONSTANT)

public:
    using RotationTransformListModelPtr = std::shared_ptr<RotationTransformListModel>;
    using FlipTransformListModelPtr = std::shared_ptr<FlipTransformListModel>;
    using ResizeTransformModelPtr = std::shared_ptr<ResizeTransformModel>;

    explicit DetailAspectRatioFeatureModel(QObject *parent = nullptr);
    ~DetailAspectRatioFeatureModel() override;

    QObject *rotationTransformListModel() const;
    QObject *flipTransformListModel() const;
    QObject *resizeTransformModel() const;

private:
    RotationTransformListModelPtr m_rotationTransformListModel;
    FlipTransformListModelPtr m_flipTransformListModel;
    ResizeTransformModelPtr m_resizeTransformModel;
};

#endif // DETAILASPECTRATIOFEATUREMODEL_H
