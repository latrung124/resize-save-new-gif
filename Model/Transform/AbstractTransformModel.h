/*
* AbstractTransformModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the abstract transform model.
*/

#ifndef ABSTRACTTRANSFORMMODEL_H
#define ABSTRACTTRANSFORMMODEL_H

#include <QObject>
#include <QString>
#include <QVariant>

#include "TransformTypeClass.h"

class AbstractTransformModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged)
    Q_PROPERTY(TransformType transformType READ transformType CONSTANT)

public:
    explicit AbstractTransformModel(QObject *parent = nullptr);
    AbstractTransformModel(const TransformType &transformType, const QString &iconSource, const QString &name, QObject *parent = nullptr);
    virtual ~AbstractTransformModel();

    QString name() const;
    void setName(const QString &name);

    QString iconSource() const;
    void setIconSource(const QString &iconSource);

    TransformType transformType() const;

signals:
    void nameChanged();
    void iconSourceChanged();

private:
    QString m_name;
    QString m_iconSource;
    TransformType m_transformType = TransformType::None;
};

#endif // ABSTRACTTRANSFORMMODEL_H
