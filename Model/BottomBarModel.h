/*
* BottomBarModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the bottom bar model.
*/

#ifndef BOTTOMBARMODEL_H
#define BOTTOMBARMODEL_H

#include <QAbstractListModel>
#include <vector>
#include <memory>

class AbstractActionModel;

class BottomBarModel : public QAbstractListModel
{
    Q_OBJECT

public:
    using AbstractActionModelPtr = std::shared_ptr<AbstractActionModel>;

    enum Role
    {
        IconRole = Qt::UserRole + 1,
        ActionRole = Qt::UserRole + 2
    };

    explicit BottomBarModel(QObject *parent = nullptr);
    ~BottomBarModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<AbstractActionModelPtr> m_actionModels;
};

#endif // BOTTOMBARMODEL_H