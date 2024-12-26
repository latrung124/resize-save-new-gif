/*
* ActionController.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation of the action controller.
*/

#include "ActionController.h"
#include "BottomBarModel.h"

#include <QQmlApplicationEngine>

ActionController::ActionController(QObject *parent)
    : QObject(parent)
    , m_bottomBarModel(std::make_unique<BottomBarModel>(this))
{
}

ActionController::~ActionController()
{
}

void ActionController::onModuleInitialized(EngineWPtr engine)
{
    m_engine = engine;
    initBottomBarModel();
}

void ActionController::onModuleDestroyed()
{
    m_bottomBarModel->deleteLater();
}

void ActionController::initBottomBarModel()
{
    auto engine = m_engine.lock();
    if (!engine) {
        return;
    }

    auto root = engine->rootObjects().first();
    if (!root) {
        return;
    }

    auto imageContentObj = root->findChild<QObject*>("imageContent");
    if (!imageContentObj) {
        return;
    }

    imageContentObj->setProperty("bottomBarModel", QVariant::fromValue(m_bottomBarModel.get()));
}
