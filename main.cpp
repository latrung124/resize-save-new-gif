#include "ModuleController/ModuleController.h"
#include <QGuiApplication>

#include "WrapperGifLib/IGifConverter.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    ModuleController controller;
    controller.init();

    return a.exec();
}
