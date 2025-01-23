/*
* GifConverterImpl.cpp
* Author: trung.la
* Date: 2024-12-20
*/

#include "GifConverterImpl.h"

#include <QImage>
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QBuffer>
#include <QImageReader>
#include <QIODevice>
#include <QFile>
#include <QImageWriter>
#include <QVariant>
#include "gif_lib.h"

extern "C" {
#include "getarg.h"
}

#include <sstream>

bool GifConverterImpl::convertImageByFrame(const QImage &qImage, GifFileType *GifFile) {
    if (qImage.isNull()) {
        return false;
    }

    int Width = qImage.width();
    int Height = qImage.height();
    int ColorMapSize = 256;

    GifByteType *RedBuffer = (GifByteType *)malloc(Width * Height);
    GifByteType *GreenBuffer = (GifByteType *)malloc(Width * Height);
    GifByteType *BlueBuffer = (GifByteType *)malloc(Width * Height);

    memset(RedBuffer, 0, Width * Height);
    memset(GreenBuffer, 0, Width * Height);
    memset(BlueBuffer, 0, Width * Height);

    for (int y = 0; y < Height; ++y) {
        for (int x = 0; x < Width; ++x) {
            QColor pixelColor = qImage.pixelColor(x, y);
            int colorIndex = y * Width + x;
            RedBuffer[colorIndex] = pixelColor.red();
            GreenBuffer[colorIndex] = pixelColor.green();
            BlueBuffer[colorIndex] = pixelColor.blue();
        }
    }

    ColorMapObject *OutputColorMap = NULL;
    GifByteType *OutputBuffer = NULL;

    if ((OutputColorMap = GifMakeMapObject(ColorMapSize, NULL)) == NULL ||
        (OutputBuffer = (GifByteType *)malloc(
             Width * Height * sizeof(GifByteType))) == NULL) {
        qDebug() << "Failed to allocate memory required, aborted.";
        return false;
    }

    if (GifQuantizeBuffer(Width, Height, &ColorMapSize, RedBuffer,
                          GreenBuffer, BlueBuffer, OutputBuffer,
                          OutputColorMap->Colors) == GIF_ERROR) {
        qDebug() << "Failed to quantize image";
        return false;
    }
    free((char *)RedBuffer);
    free((char *)GreenBuffer);
    free((char *)BlueBuffer);

    if (EGifPutImageDesc(GifFile, 0, 0, Width, Height, false, OutputColorMap) == GIF_ERROR) {
        qDebug() << "Failed to write image descriptor";
        return false;
    }

    GifByteType *Ptr = OutputBuffer;

    for (int i = 0; i < Height; i++) {
        if (EGifPutLine(GifFile, Ptr, Width) == GIF_ERROR) {
            qDebug() << "Failed to write line";
            return false;
        }
        Ptr += Width;
    }

    return true;
}

void GifConverterImpl::PrintExtensionBlockHexToDebug(const ExtensionBlock *extBlock) {
    if (extBlock == NULL) {
        qDebug() << "ExtensionBlock is NULL.";
        return;
    }

    std::stringstream ss;

    ss << "Extension Function: 0x" << std::hex << std::uppercase << extBlock->Function << std::endl;
    ss << "Byte Count: " << extBlock->ByteCount << std::endl;

    ss << "Hex Data: ";
    for (int i = 0; i < extBlock->ByteCount; ++i) {
        ss << "0x" << std::hex << std::uppercase << (int)extBlock->Bytes[i] << " ";
    }
    ss << std::endl;

    qDebug() << QString::fromStdString(ss.str());
}

void GifConverterImpl::printInfoOfGif(const char* fileName) {
    qDebug() << Q_FUNC_INFO;
    int error;
    GifFileType *gif = DGifOpenFileName(fileName, &error);
    if (gif == NULL) {
        qDebug() << "Error opening GIF file: \n" << fileName << GifErrorString(error);
        exit(1);
    }

    if (DGifSlurp(gif) == GIF_ERROR) {
        qDebug() << "Error reading GIF file: \n" << fileName << GifErrorString(gif->Error);
        exit(1);
    }

    qDebug() << "GIF file information:\n";
    qDebug() <<"Screen size: %dx%d\n"<< gif->SWidth << gif->SHeight;
    qDebug() <<"Color resolution: %d\n" << gif->SColorResolution;
    qDebug() <<"Background color index: %d\n" << gif->SBackGroundColor;
    qDebug() <<"Aspect ratio: %d\n" << gif->AspectByte;
    qDebug() <<"Image count: %d\n" << gif->ImageCount;

    if (gif->SColorMap != NULL) {
        qDebug() <<"Color map: %s\n" << (gif->SColorMap ? "yes" : "no");
        qDebug() <<"Color map size: %d\n" << gif->SColorMap->ColorCount;
        qDebug() <<"Color map bits per pixel: %d\n" << gif->SColorMap->BitsPerPixel;
        qDebug() <<"Color map colors:\n";
        for (int i = 0; i < gif->SColorMap->ColorCount; i++) {
            GifColorType color = gif->SColorMap->Colors[i];
            qDebug() <<"    Color i:" << i << " r: " << color.Red << " g: " << color.Green << " b: " << color.Blue;
        }
    }


    if (gif->ImageCount == 0) {
        qDebug() << "failed!";
        return;
    }
    for (int i = 0; i < gif->ImageCount; i++) {
        SavedImage *image = &gif->SavedImages[i];
        qDebug() <<"Image number: " << i + 1;
        qDebug() <<"  Image position: left: " << image->ImageDesc.Left << " top: " << image->ImageDesc.Top;
        qDebug() <<"  Image size: width: " << image->ImageDesc.Width << " height: " << image->ImageDesc.Height;
        qDebug() <<"  Interlaced: " << image->ImageDesc.Interlace;

        if (image->ExtensionBlocks != NULL) {
            qDebug() <<"  Extension blocks: " << image->ExtensionBlockCount;
            for (int j = 0; j < image->ExtensionBlockCount; j++) {
                ExtensionBlock *block = &image->ExtensionBlocks[j];
                qDebug() <<"    Extension block " << j + 1;
                PrintExtensionBlockHexToDebug(block);
                qDebug() <<"      Block size: " << block->ByteCount;
                qDebug() <<"      Block type: " << block->Function;
                if (block->Function == GRAPHICS_EXT_FUNC_CODE) {
                    qDebug() <<"      GRAPHICS_EXT_FUNC_CODE ";
                    GraphicsControlBlock gcb;
                    if (DGifExtensionToGCB(block->ByteCount, block->Bytes, &gcb) == GIF_ERROR) {
                        qDebug() <<"      Error converting extension block to GCB";
                    } else {
                        qDebug() <<"      GCB disposal mode: " << gcb.DisposalMode;
                        qDebug() <<"      GCB delay time: " << gcb.DelayTime;
                        qDebug() <<"      GCB transparent color: " << gcb.TransparentColor;
                    }
                } else if (block->Function == APPLICATION_EXT_FUNC_CODE) {
                    qDebug() <<"      APPLICATION_EXT_FUNC_CODE ";
                } else if (block->Function == CONTINUE_EXT_FUNC_CODE){
                    qDebug() <<"      CONTINUE_EXT_FUNC_CODE ";
                } else if (block->Function == COMMENT_EXT_FUNC_CODE){
                    qDebug() <<"      CONTINUE_EXT_FUNC_CODE ";
                } else if (block->Function == PLAINTEXT_EXT_FUNC_CODE){
                    qDebug() <<"      CONTINUE_EXT_FUNC_CODE ";
                } else {
                    qDebug() <<"      error code ";
                }
            }
        }
    }

    qDebug() << "Externsion blocks: " << gif->ExtensionBlockCount;
    if (gif->ExtensionBlocks) {
        for (int i = 0; i < gif->ExtensionBlockCount; i++) {
            ExtensionBlock *block = &gif->ExtensionBlocks[i];
            qDebug() << "Extension block %d:\n" << i + 1;
            qDebug() << "  Block size: %d\n" << block->ByteCount;
            qDebug() << "  Block type: %d\n" << block->Function;
            qDebug() << "  Block data: %s\n" << block->Bytes;
        }
    }

    if (DGifCloseFile(gif, &error) == GIF_ERROR) {
        qDebug() << "Error closing GIF file: %s\n" << GifErrorString(error);
        exit(1);
    }
    qDebug() << "read done!";
}

bool GifConverterImpl::AddGraphicsControlExtension(GifFileType *gifFile, int imageIndex, int delayTimeCentiseconds) {
    if (gifFile == nullptr || imageIndex < 0 || imageIndex >= gifFile->ImageCount) return false;

    GraphicsControlBlock gcb;
    gcb.DisposalMode = DISPOSAL_UNSPECIFIED;
    gcb.UserInputFlag = false;
    gcb.DelayTime = delayTimeCentiseconds;
    gcb.TransparentColor = NO_TRANSPARENT_COLOR;

    if (EGifGCBToSavedExtension(&gcb, gifFile, imageIndex) == GIF_ERROR) {
        qDebug() << Q_FUNC_INFO << " failed!";
        return false;
    }

    return true;
}

bool GifConverterImpl::readGifFile(const char *fileName) {
    return m_gifReader.readGifFile(fileName);
}

bool GifConverterImpl::createGifFileFromQImage(const char *srcFileName, const char *destFileName,
                                               const TransformDescriptor& transformDescriptor) {
    QImageReader reader(QString::fromLocal8Bit(srcFileName));

    GifFileType *GifFile = NULL;
    if ((GifFile = EGifOpenFileName(destFileName, true, NULL)) == NULL) {
        qDebug() << "Failed to create GIF file";
        return false;
    }

    EGifSetGifVersion(GifFile, true);

    ColorMapObject *ColorMap = GifMakeMapObject(256, NULL);
    if (ColorMap == NULL) {
        qDebug() << "Failed to create color map";
        return false;
    }

    auto globalColorTable = m_gifReader.getGlobalColorTable();
    for (int i = 0; i < globalColorTable.size(); ++i) {
        ColorMap->Colors[i].Red = globalColorTable[i].r;
        ColorMap->Colors[i].Green = globalColorTable[i].g;
        ColorMap->Colors[i].Blue = globalColorTable[i].b;
    }

    //TODO: handle color table size = 0

    if (EGifPutScreenDesc(GifFile, transformDescriptor.width, transformDescriptor.height, 8, 0, ColorMap) == GIF_ERROR) {
        qDebug() << "Failed to write screen descriptor";
        return false;
    }

    GifFile->SavedImages = (SavedImage *)malloc(sizeof(SavedImage) * reader.imageCount());

    for (int i = 0; i < reader.imageCount(); ++i) {
        QImage image = reader.read();
        if (image.isNull()) {
            qDebug() << "Failed to read image";
            return false;
        }
        image = image.convertToFormat(QImage::Format_Indexed8);
        double rotationRadians = transformDescriptor.rotation * M_PI / 180.0;
        image = image.transformed(QTransform().rotateRadians(rotationRadians), Qt::SmoothTransformation);
        image = image.scaled(QSize(transformDescriptor.width, transformDescriptor.height), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if (transformDescriptor.flipType == -1) {
            QTransform flipTransform;
            QPointF flipPoint(image.width() / 2, image.height() / 2);
            flipTransform.translate(flipPoint.x(), flipPoint.y());
            flipTransform.scale(-1, 1);
            flipTransform.translate(-flipPoint.x(), -flipPoint.y());
            image = image.transformed(flipTransform, Qt::SmoothTransformation);
        }

        if (i == 0) {
            ExtensionBlock *loopExtBlock = (ExtensionBlock *)malloc(sizeof(ExtensionBlock) * 2);
            if (!loopExtBlock) {
                qDebug() << "Memory allocation failed for loopExtBlock";
                return false;
            }

            loopExtBlock[0].ByteCount = 11;
            loopExtBlock[0].Bytes = (GifByteType *)malloc(11);
            loopExtBlock[0].Function = APPLICATION_EXT_FUNC_CODE;
            if (!loopExtBlock[0].Bytes) {
                free(loopExtBlock);
                qDebug() << "Memory allocation failed for loopExtBlock[0].Bytes";
                return false;
            }
            memcpy(loopExtBlock[0].Bytes, "NETSCAPE2.0", 11);

            loopExtBlock[1].ByteCount = 3;
            loopExtBlock[1].Bytes = (GifByteType *)malloc(3);
            loopExtBlock[1].Function = CONTINUE_EXT_FUNC_CODE;
            if (!loopExtBlock[1].Bytes) {
                free(loopExtBlock[0].Bytes);
                free(loopExtBlock);
                qDebug() << "Memory allocation failed for loopExtBlock[1].Bytes";
                return false;
            }
            loopExtBlock[1].Bytes[0] = 0x01;
            loopExtBlock[1].Bytes[1] = 0x00;
            loopExtBlock[1].Bytes[2] = 0x00;

            bool success = (EGifPutExtensionLeader(GifFile, APPLICATION_EXT_FUNC_CODE) != GIF_ERROR &&
                          EGifPutExtensionBlock(GifFile, 11, loopExtBlock[0].Bytes) != GIF_ERROR &&
                          EGifPutExtensionBlock(GifFile, 3, loopExtBlock[1].Bytes) != GIF_ERROR &&
                          EGifPutExtensionTrailer(GifFile) != GIF_ERROR);

            free(loopExtBlock[0].Bytes);
            free(loopExtBlock[1].Bytes);
            free(loopExtBlock);

            if (!success) {
                qDebug() << "Failed to write Netscape Extension blocks";
                return false;
            }

            GraphicsControlBlock gcb;
            gcb.DisposalMode = 1;
            gcb.DelayTime = reader.nextImageDelay()/10;
            gcb.TransparentColor = -1;
            
            GifByteType *GifExtension = (GifByteType*)malloc(4);
            if (!GifExtension) {
                qDebug() << "Memory allocation failed for GifExtension";
                return false;
            }

            EGifGCBToExtension(&gcb, GifExtension);
            success = (EGifPutExtension(GifFile, GRAPHICS_EXT_FUNC_CODE, 4, GifExtension) != GIF_ERROR);
            free(GifExtension);

            if (!success) {
                qDebug() << "Failed to write first frame delay";
                return false;
            }
        } else {
            GraphicsControlBlock gcb;
            gcb.DisposalMode = 1;
            gcb.DelayTime = reader.nextImageDelay()/10;
            gcb.TransparentColor = -1;

            GifByteType *GifExtension = (GifByteType*)malloc(4);
            if (!GifExtension) {
                qDebug() << "Memory allocation failed for GifExtension";
                return false;
            }

            EGifGCBToExtension(&gcb, GifExtension);
            bool success = (EGifPutExtension(GifFile, GRAPHICS_EXT_FUNC_CODE, 4, GifExtension) != GIF_ERROR);
            free(GifExtension);

            if (!success) {
                qDebug() << "EGifPutExtension failed!";
                return false;
            }
        }

        if (convertImageByFrame(image, GifFile) == false) {
            qDebug() << "Failed to convert image";
            return false;
        }

        reader.jumpToNextImage();
    }

    if (EGifCloseFile(GifFile, NULL) == GIF_ERROR) {
        qDebug() << "Failed to close GIF file";
        return false;
    }

    return true;
}
