/*
* SideBarModel.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the side bar model.
*/

#ifndef SIDEBARMODEL_H
#define SIDEBARMODEL_H

#include <QObject>
#include <vector>
#include <memory>

class AbstractFeatureModel;

class SideBarModel : public QObject
{
    Q_OBJECT

public:
    using FeatureModelPtr = std::shared_ptr<AbstractFeatureModel>;

    explicit SideBarModel(QObject *parent = nullptr);
    ~SideBarModel();

private:
    std::vector<FeatureModelPtr> m_featureModels;
};

#endif // SIDEBARMODEL_H