/*
* ExportController.h
* Author: trung.la
* Date: 2024-12-24
* Description: This file contains the ExportController class.
*/

#ifndef EXPORTCONTROLLER_H
#define EXPORTCONTROLLER_H

#include <QObject>
#include <QString>
#include <QRegularExpression>

#include <thread>
#include <functional>

class IGifDebugger;
class IGifConverter;

namespace gif_util::gif_89a {
    struct TransformDescriptor;
}

class ExportController : public QObject
{
    Q_OBJECT

public:
    using TransformDescriptor = gif_util::gif_89a::TransformDescriptor;

    ExportController(QObject *parent = nullptr);
    ~ExportController();

    Q_INVOKABLE void exportGif(QObject *model, QString destFileName);
    Q_INVOKABLE void printGifInfo(QString fileName);

signals:
    void exportGifFinished(bool isSuccess);

private:
    void exportGifAsync(QString fileName, QString destFileName,
                    const TransformDescriptor &transformDescriptor,
                    std::function<void(bool)> resCallback);

    std::unique_ptr<IGifDebugger> m_gifDebugger;
    std::unique_ptr<IGifConverter> m_gifConverter;
    QRegularExpression m_filePrefixExp;
    std::thread m_exportThread;
};

#endif // EXPORTCONTROLLER_H
