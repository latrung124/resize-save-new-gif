/*
* FeatureController.h
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the feature controller.
*/

#ifndef FEATURECONTROLLER_H
#define FEATURECONTROLLER_H

#include <QObject>
#include <vector>
#include <memory>

class SideBarModel;

class FeatureController : public QObject
{
    Q_OBJECT

public:
    using SideBarModelUPtr = std::unique_ptr<SideBarModel>;

    explicit FeatureController(QObject *parent = nullptr);
    ~FeatureController();

private:
    SideBarModelUPtr m_sideBarModel;
};

#endif // FEATURECONTROLLER_H