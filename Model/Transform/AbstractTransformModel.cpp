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

AbstractTransformModel::AbstractTransformModel(const QString &iconSource, const QString &name, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_iconSource(iconSource)
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

void AbstractTransformModel::applyTransform(const QImage &image)
{
    Q_UNUSED(image);
}
