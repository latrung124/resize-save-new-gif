/*
* ResizeTransformListModel.h
* Author: Trung La
* Date: 2024-12-26
* Description: This file contains the definition for the resize transform list model.
*/

#ifndef RESIZETRANSFORMLISTMODEL_H
#define RESIZETRANSFORMLISTMODEL_H

#include "AbstractTransformListModel.h"

class ResizeTransformModel;

class ResizeTransformListModel : public AbstractTransformListModel
{
    Q_OBJECT

public:
    using ResizeTransformModelPtr = std::shared_ptr<ResizeTransformModel>;

    enum ResizeTransformRole
    {
        NameRole = Qt::UserRole + 1,
        IconSourceRole,
        TransformTypeRole
    };

    ResizeTransformListModel(QObject *parent = nullptr);
    ~ResizeTransformListModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void onTransformTrigger(int index) override;

private:
    std::vector<ResizeTransformModelPtr> m_resizeTransformModels;
};

#endif // RESIZETRANSFORMLISTMODEL_H