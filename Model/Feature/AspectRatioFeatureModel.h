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
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QObject *rotationTransformListModel READ rotationTransformListModel NOTIFY rotationTransformListModelChanged)
    Q_PROPERTY(QObject *flipTransformListModel READ flipTransformListModel NOTIFY flipTransformListModelChanged)

public:
    using RotationTransformListModelPtr = std::shared_ptr<RotationTransformListModel>;
    using FlipTransformListModelPtr = std::shared_ptr<FlipTransformListModel>;

    explicit AspectRatioFeatureModel(QObject *parent = nullptr);
    AspectRatioFeatureModel(FeatureType featureType, QObject *parent = nullptr);
    ~AspectRatioFeatureModel() override;

    QString source() const;
    void setSource(const QString &source);

    QObject *rotationTransformListModel() const;
    QObject *flipTransformListModel() const;

signals:
    void sourceChanged();
    void rotationTransformListModelChanged();
    void flipTransformListModelChanged();

private:
    QString m_source;
    RotationTransformListModelPtr m_rotationTransformListModel;
    FlipTransformListModelPtr m_flipTransformListModel;
};

#endif // ASPECTRATIOFEATUREMODEL_H
