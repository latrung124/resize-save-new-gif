/*
* SideBarModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the side bar model.
*/

#ifndef SIDEBARMODEL_H
#define SIDEBARMODEL_H

#include <QAbstractListModel>
#include <vector>
#include <memory>

#include "AbstractFeatureModel.h"

class SideBarModel : public QAbstractListModel
{
    Q_OBJECT

public:
    using FeatureModelPtr = std::shared_ptr<AbstractFeatureModel>;

    enum Role {
        IconRole = Qt::UserRole + 1,
        SourceRole,
        DetailFeatureModelRole
    };

    explicit SideBarModel(QObject *parent = nullptr);
    ~SideBarModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<FeatureModelPtr> m_featureModels;
};

#endif // SIDEBARMODEL_H
