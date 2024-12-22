/*
* ModuleController.cpp
* Author: trung.la
* Date: 2024-12-20
*/

#include "ModuleController.h"
#include "../Utility.h"

#include <QUrl>
#include <QDebug>

ModuleController::ModuleController(QObject* parent)
    : QObject(parent)
    , m_engine(std::make_shared<QQmlApplicationEngine>())
{
    connect(m_engine.get(), &QQmlApplicationEngine::objectCreated, this, &ModuleController::onObjectCreated);
}

ModuleController::~ModuleController()
{
    m_engine->deleteLater();
}

void ModuleController::init()
{
    loadQmlModule();
}

void ModuleController::loadQmlModule()
{
    if (!m_engine) {
        return;
    }

    auto module = Utility::moduleInfo[Utility::ModuleType::GuiComponent];
    m_engine->loadFromModule(module.name, module.path);
}

void ModuleController::onObjectCreated(QObject* object, const QUrl& url)
{
    if (!object) {
        return;
    }

    emit moduleInitialized(m_engine);
}

