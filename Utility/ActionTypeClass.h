/*
* ActionTypeClass.h
* Date: 2024-12-23
* Description: This file contains the ActionTypeClass.
*/

#ifndef ACTIONTYPECLASS_H
#define ACTIONTYPECLASS_H

#include <QObject>

class ActionTypeClass : public QObject
{
    Q_GADGET
public:
    enum class EActionType : uint16_t
    {
        None = 0,
        FileExplorer,
        Delete,
        Refresh
    };
    Q_ENUM(EActionType)

private:
    explicit ActionTypeClass();
};
typedef ActionTypeClass::EActionType ActionType;

#endif // ACTIONTYPECLASS_H