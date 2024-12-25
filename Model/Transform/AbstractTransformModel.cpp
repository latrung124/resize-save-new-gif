/*
* AbstractTransformModel.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the abstract transform model.
*/

#include "AbstractTransformModel.h"

AbstractTransformModel::AbstractTransformModel(QObject *parent)
    : QObject(parent)
{
}

AbstractTransformModel::AbstractTransformModel(const TransformType &transformType, const QString &iconSource, const QString &name, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_iconSource(iconSource)
    , m_transformType(transformType)
{
}

AbstractTransformModel::~AbstractTransformModel()
{
}

QString AbstractTransformModel::name() const
{
    return m_name;
}

void AbstractTransformModel::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}

QString AbstractTransformModel::iconSource() const
{
    return m_iconSource;
}

void AbstractTransformModel::setIconSource(const QString &iconSource)
{
    if (m_iconSource == iconSource) {
        return;
    }

    m_iconSource = iconSource;
    emit iconSourceChanged();
}

TransformType AbstractTransformModel::transformType() const
{
    return m_transformType;
}
