/*
* Utility.h
* Author: trung.la
* Date: 2024-12-20
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <QHash>

namespace Utility {

enum class ModuleType {
    GuiComponent,
};

struct ModuleInfo {
    ModuleInfo() = default;
    ModuleInfo(ModuleType type, QString path, QString name)
        : type(type)
        , name(path)
        , path(name)
    {
    }

    ModuleType type;
    QString name;
    QString path;
};

static QHash<ModuleType, ModuleInfo> moduleInfo = {
    {ModuleType::GuiComponent, {ModuleType::GuiComponent, "GuiComponent", "MainWindow"}},
};

} // namespace Utility
#endif // UTILITY_H
