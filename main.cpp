#include "ModuleController.h"
#include "FeatureController.h"
#include "ActionController.h"
#include <QGuiApplication>

#include "WrapperGifLib/IGifConverter.h"
#include "ActionTypeClass.h"
#include "FeatureTypeClass.h"
#include "TransformTypeClass.h"

static void registerTypes()
{
    qRegisterMetaType<ActionType>("ActionType");
    qmlRegisterUncreatableType<ActionTypeClass>(
        "App.Enums",                    // QML namespace
        1, 0,                          // Major and minor versions
        "ActionType",                 // Enum group name in QML
        "Cannot create AuthenticationType in QML. Access enums only.");

    qRegisterMetaType<FeatureType>("FeatureType");
    qmlRegisterUncreatableType<FeatureTypeClass>(
        "App.Enums",                    // QML namespace
        1, 0,                          // Major and minor versions
        "FeatureType",                 // Enum group name in QML
        "Cannot create FeatureType in QML. Access enums only.");

    qRegisterMetaType<TransformType>("TransformType");
    qmlRegisterUncreatableType<TransformTypeClass>(
        "App.Enums",                    // QML namespace
        1, 0,                          // Major and minor versions
        "TransformType",               // Enum group name in QML
        "Cannot create TransformType in QML. Access enums only.");
}

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    registerTypes();

    ModuleController moduleController;
    FeatureController featureController;
    ActionController actionController;
    QObject::connect(&moduleController, &ModuleController::moduleInitialized, &featureController,
                     &FeatureController::onModuleInitialized);
    QObject::connect(&moduleController, &ModuleController::moduleInitialized, &actionController,
                     &ActionController::onModuleInitialized);

    moduleController.init();

    return a.exec();
}
