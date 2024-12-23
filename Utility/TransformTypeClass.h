/*
* TransformTypeClass.h
* Author: Trung La
* Date: 2024-12-23
* Description: This file contains the TransformTypeClass.
*/

#ifndef TRANSFORMTYPECLASS_H
#define TRANSFORMTYPECLASS_H

#include <QObject>

class TransformTypeClass : public QObject
{
    Q_GADGET

public:
    enum class ETransformType : uint16_t
    {
        None = 0,
        Rotation,
        Flip
    };
    Q_ENUM(ETransformType)

private:
    explicit TransformTypeClass();
};
typedef TransformTypeClass::ETransformType TransformType;

#endif // TRANSFORMTYPECLASS_H