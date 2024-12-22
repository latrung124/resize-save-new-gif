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

class QQmlApplicationEngine;

class SideBarModel;

class FeatureController : public QObject
{
    Q_OBJECT

public:
    using SideBarModelUPtr = std::unique_ptr<SideBarModel>;
    using EngineWPtr = std::weak_ptr<QQmlApplicationEngine>;

    explicit FeatureController(QObject *parent = nullptr);
    ~FeatureController();

public slots:
    void onModuleInitialized(EngineWPtr engine);

private:
    void initSideBarModel();

    SideBarModelUPtr m_sideBarModel;
    EngineWPtr m_engine;
};

#endif // FEATURECONTROLLER_H
