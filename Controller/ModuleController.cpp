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
    , m_engine(new QQmlApplicationEngine())
{
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
    if (m_engine == nullptr) {
        return;
    }

    auto module = Utility::moduleInfo[Utility::ModuleType::GuiComponent];
    m_engine->loadFromModule(module.name, module.path);
}

