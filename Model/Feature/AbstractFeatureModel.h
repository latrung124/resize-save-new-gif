/*
* AbstractFeatureModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the abstract feature model.
*/

#ifndef ABSTRACTFEATUREMODEL_H
#define ABSTRACTFEATUREMODEL_H

#include "FeatureTypeClass.h"

#include <QObject>

class RotationTransformListModel;
class FlipTransformListModel;

class AbstractFeatureModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source CONSTANT)
    Q_PROPERTY(QString icon READ icon CONSTANT)
    Q_PROPERTY(QObject *detailFeatureModel READ detailFeatureModel CONSTANT)

public:
    explicit AbstractFeatureModel(QObject *parent = nullptr);
    AbstractFeatureModel(FeatureType featureType, QObject *parent = nullptr);
    virtual ~AbstractFeatureModel();

    FeatureType featureType() const;

    virtual QString source() const = 0;
    virtual QString icon() const = 0;
    virtual QObject *detailFeatureModel() const = 0;

private:
    FeatureType m_featureType = FeatureType::None;
};

#endif // ABSTRACTFEATUREMODEL_H