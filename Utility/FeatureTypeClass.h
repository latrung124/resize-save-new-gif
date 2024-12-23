/*
* FeatureTypeClass.h
* Author: Trung La
* Date: 2024-12-23
* Description: This file contains the FeatureTypeClass.
*/

#ifndef FEATURETYPECLASS_H
#define FEATURETYPECLASS_H

#include <QObject>

class FeatureTypeClass : public QObject
{
    Q_GADGET

public:
    enum class EFeatureType : uint16_t
    {
        None = 0,
        AspectRatio,
        Crop
    };
    Q_ENUM(EFeatureType)

private:
    explicit FeatureTypeClass();
};
typedef FeatureTypeClass::EFeatureType FeatureType;

#endif // FEATURETYPECLASS_H