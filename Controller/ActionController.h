/*
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the interface for the action controller.
*/

#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <QObject>

class QQmlApplicationEngine;

class BottomBarModel;

class ActionController : public QObject
{
    Q_OBJECT

public:
    using EngineWPtr = std::weak_ptr<QQmlApplicationEngine>;
    using BottomBarModelUPtr = std::unique_ptr<BottomBarModel>;

    explicit ActionController(QObject *parent = nullptr);
    ~ActionController();

public slots:
    void onModuleInitialized(EngineWPtr engine);
    void onModuleDestroyed();

private:
    void initBottomBarModel();

    BottomBarModelUPtr m_bottomBarModel;
    EngineWPtr m_engine;
};

#endif // ACTIONCONTROLLER_H