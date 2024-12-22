/*
* ModuleController.h
* Author: trung.la
* Date: 2024-12-20
*/

#ifndef MODULECONTROLLER_H
#define MODULECONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>

class ModuleController : public QObject
{
    Q_OBJECT
public:
    ModuleController(QObject* parent = nullptr);
    ~ModuleController();

    void init();

private:
    void loadQmlModule();

    QQmlApplicationEngine* m_engine;
};

#endif // MODULECONTROLLER_H