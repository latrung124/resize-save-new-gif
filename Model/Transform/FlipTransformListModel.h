/*
* FlipTransformListModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the declaration for the flip transform list model.
*/

#ifndef FLIPTRANSFORMLISTMODEL_H
#define FLIPTRANSFORMLISTMODEL_H

#include <QAbstractListModel>
#include <memory>
#include <vector>

class FlipTransformModel;

class FlipTransformListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    using FlipTransformModelPtr = std::shared_ptr<FlipTransformModel>;

    enum FlipTransformRole
    {
        NameRole = Qt::UserRole + 1,
        IconSourceRole
    };

    explicit FlipTransformListModel(QObject *parent = nullptr);
    ~FlipTransformListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<FlipTransformModelPtr> m_flipTransformModels;
};

#endif // FLIPTRANSFORMLISTMODEL_H