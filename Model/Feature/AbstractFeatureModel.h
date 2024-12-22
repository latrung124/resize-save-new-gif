/*
* AbstractFeatureModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the abstract feature model.
*/

#ifndef ABSTRACTFEATUREMODEL_H
#define ABSTRACTFEATUREMODEL_H

#include <QObject>

class AbstractFeatureModel : public QObject
{
    Q_OBJECT

public:
    enum class FeatureType : uint16_t
    {
        None = 0,
        AspectRatio = 1,
        Crop = 2
    };
    Q_ENUM(FeatureType)

    explicit AbstractFeatureModel(QObject *parent = nullptr);
    AbstractFeatureModel(FeatureType featureType, QObject *parent = nullptr);
    virtual ~AbstractFeatureModel();

    FeatureType featureType() const;

private:
    FeatureType m_featureType = FeatureType::None;
};

#endif // ABSTRACTFEATUREMODEL_H