/*
* FeatureController.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the feature controller.
*/

#include <QQmlApplicationEngine>

#include "FeatureController.h"
#include "SideBarModel.h"

FeatureController::FeatureController(QObject *parent)
    : QObject(parent)
    , m_sideBarModel(std::make_unique<SideBarModel>(this))
{
}

FeatureController::~FeatureController()
{
}

void FeatureController::onModuleInitialized(EngineWPtr engine)
{
    m_engine = engine;
    initSideBarModel();
}

void FeatureController::initSideBarModel()
{
    auto engine = m_engine.lock();
    if (!engine) {
        return;
    }

    auto root = engine->rootObjects().first();
    if (!root) {
        return;
    }

    auto sideBarObj = root->findChild<QObject*>("sideBar");
    if (!sideBarObj) {
        return;
    }

    sideBarObj->setProperty("sideBarModel", QVariant::fromValue(m_sideBarModel.get()));
}
