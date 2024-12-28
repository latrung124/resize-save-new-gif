/*
* ExportController.cpp
* Author: trung.la
* Date: 2024-12-24
* This is a simple implementation of the ExportController class.
*/

#include "ExportController.h"
#include "GifUtility.h"
#include "IGifDebugger.h"
#include "Implementation/GifConverterImpl.h"

#include "ImageModel.h"

#include <QDebug>
#include <QString>
#include <QFileInfo>
#include <memory>
#include <future>

ExportController::ExportController(QObject *parent)
    : QObject(parent)
    , m_gifDebugger(std::make_unique<IGifDebugger>())
    , m_gifConverter(std::make_unique<GifConverterImpl>())
{
    m_filePrefixExp.setPattern("^file:///+");
}

ExportController::~ExportController()
{
}

void ExportController::exportGif(QObject *model, QString destFileName) {
    if (destFileName.isEmpty()) {
        qDebug() << "ExportController::exportGif: destFileName is empty";
        return;
    }

    qDebug() << "ExportController::exportGif";
    const ImageModel *imageModel = qobject_cast<ImageModel *>(model);
    if (!imageModel) {
        qDebug() << "ExportController::exportGif: model is not ImageModel";
        return;
    }

    TransformDescriptor transformDescriptor;
    transformDescriptor.width = imageModel->width();
    transformDescriptor.height = imageModel->height();
    transformDescriptor.rotation = imageModel->rotationAngle();
    transformDescriptor.flipType = imageModel->flipType();

    const auto fileName = imageModel->imageSource().replace(m_filePrefixExp, "");
    destFileName = destFileName.replace(m_filePrefixExp, "");

    exportGifAsync(fileName, destFileName, transformDescriptor, [this](bool isSuccess) {
        emit exportGifFinished(isSuccess);
    });
}

void ExportController::exportGifAsync(QString fileName, QString destFileName,
                                     const TransformDescriptor &transformDescriptor,
                                     std::function<void(bool)> resCallback) {
    std::thread([this, fileName, destFileName, transformDescriptor, resCallback]() {
        bool isResult = false;
        isResult = m_gifConverter->readGifFile(fileName.toStdString().c_str());
        // Convert back to char* if needed
        QByteArray destFileNameBytes = destFileName.toLocal8Bit();
        const char* destFileNameChar = destFileNameBytes.constData();
        isResult = m_gifConverter->createGifFileFromQImage(fileName.toStdString().c_str(), destFileNameChar, transformDescriptor);

        if (resCallback)
            resCallback(isResult);
    }).detach();
}

void ExportController::printGifInfo(QString fileName) {
    qDebug() << "ExportController::printGifInfo " << fileName;
}
