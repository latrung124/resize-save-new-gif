/*
* ModuleController.h
* Author: trung.la
* Date: 2024-12-20
*/

#ifndef MODULECONTROLLER_H
#define MODULECONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <memory>

class ExportController;

class ModuleController : public QObject
{
    Q_OBJECT
public:
    ModuleController(QObject* parent = nullptr);
    ~ModuleController();

    void init();
    void onObjectCreated(QObject* object, const QUrl& url);

signals:
    void moduleInitialized(std::weak_ptr<QQmlApplicationEngine> engine);

private:
    void loadQmlModule();
    void onExportGifFinished(bool isSuccess);

    std::shared_ptr<QQmlApplicationEngine> m_engine;
    std::shared_ptr<ExportController> m_exportController;
};

#endif // MODULECONTROLLER_H