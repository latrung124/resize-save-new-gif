#include "ModuleController.h"
#include "FeatureController.h"
#include "ActionController.h"
#include <QGuiApplication>

#include "WrapperGifLib/IGifConverter.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

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
