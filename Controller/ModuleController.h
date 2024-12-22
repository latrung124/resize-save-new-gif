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

    std::shared_ptr<QQmlApplicationEngine> m_engine;
};

#endif // MODULECONTROLLER_H