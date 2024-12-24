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

void ExportController::exportGif(QString fileName) {
    qDebug() << "ExportController::exportGif";
    fileName.replace(m_filePrefixExp, "");
    // Convert to QString for easier manipulation
    QFileInfo fileInfo(fileName);

    // Create new filename with "-converted" before extension
    QString destFileName = fileInfo.path() + "/" +
                         fileInfo.completeBaseName() + "-converted." +
                         fileInfo.suffix();

    exportGifAsync(fileName, destFileName, [this](bool isSuccess) {
        emit exportGifFinished(isSuccess);
    });
}

void ExportController::exportGifAsync(QString fileName, QString destFileName, std::function<void(bool)> resCallback) {
    std::thread([this, fileName, destFileName, resCallback]() {
        bool isResult = false;
        isResult = m_gifConverter->readGifFile(fileName.toStdString().c_str());
        // Convert back to char* if needed
        QByteArray destFileNameBytes = destFileName.toLocal8Bit();
        const char* destFileNameChar = destFileNameBytes.constData();
        isResult = m_gifConverter->createGifFileFromQImage(fileName.toStdString().c_str(), destFileNameChar);

        if (resCallback)
            resCallback(isResult);
    }).detach();
}

void ExportController::printGifInfo(QString fileName) {
    qDebug() << "ExportController::printGifInfo " << fileName;
}
