/*
* ModuleController.cpp
* Author: trung.la
* Date: 2024-12-20
*/

#include "ModuleController.h"
#include "ExportController.h"
#include "../Utility.h"

#include <QQmlContext>
#include <QUrl>
#include <QDebug>

ModuleController::ModuleController(QObject* parent)
    : QObject(parent)
    , m_engine(std::make_shared<QQmlApplicationEngine>())
    , m_exportController(std::make_shared<ExportController>())
{
    connect(m_engine.get(), &QQmlApplicationEngine::objectCreated, this, &ModuleController::onObjectCreated);
    connect(m_exportController.get(), &ExportController::exportGifFinished, this, &ModuleController::onExportGifFinished);
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
    m_engine->rootContext()->setContextProperty("exportController", m_exportController.get());

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

void ModuleController::onExportGifFinished(bool isSuccess)
{
    if (!m_engine) {
        return;
    }
    qDebug() << "ModuleController::onExportGifFinished";
}

