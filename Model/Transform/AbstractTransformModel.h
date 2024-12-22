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

class AbstractTransformModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged)

public:
    explicit AbstractTransformModel(QObject *parent = nullptr);
    AbstractTransformModel(const QString &iconSource, const QString &name, QObject *parent = nullptr);
    virtual ~AbstractTransformModel();

    QString name() const;
    void setName(const QString &name);

    QString iconSource() const;
    void setIconSource(const QString &iconSource);

signals:
    void nameChanged();
    void iconSourceChanged();

public slots:
    virtual void applyTransform(const QImage &image) = 0;

private:
    QString m_name;
    QString m_iconSource;
};

#endif // ABSTRACTTRANSFORMMODEL_H
