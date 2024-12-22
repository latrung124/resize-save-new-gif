#include "ModuleController.h"
#include "FeatureController.h"
#include <QGuiApplication>

#include "WrapperGifLib/IGifConverter.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    ModuleController controller;
    FeatureController featureController;
    QObject::connect(&controller, &ModuleController::moduleInitialized, &featureController,
                     &FeatureController::onModuleInitialized);
    controller.init();

    return a.exec();
}
