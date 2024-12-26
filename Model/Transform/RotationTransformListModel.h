/*
* RotationTransformListModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the rotation transform list model.
*/

#ifndef ROTATIONTRANSFORMLISTMODEL_H
#define ROTATIONTRANSFORMLISTMODEL_H

#include "AbstractTransformListModel.h"

#include <memory>
#include <vector>

class RotationTransformModel;

class RotationTransformListModel : public AbstractTransformListModel
{
    Q_OBJECT
public:
    enum RotationTransformRole
    {
        NameRole = Qt::UserRole + 1,
        IconSourceRole,
        TransformTypeRole
    };

    using RotationTransformModelPtr = std::shared_ptr<RotationTransformModel>;
    explicit RotationTransformListModel(QObject *parent = nullptr);
    ~RotationTransformListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void onTransformTrigger(int index) override;

private:
    std::vector<RotationTransformModelPtr> m_rotationTransformModels;
};

#endif // ROTATIONTRANSFORMLISTMODEL_H
