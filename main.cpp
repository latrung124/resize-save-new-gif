#include <QCoreApplication>
#include <QGuiApplication>
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
#include <QPainter>
#include "qgiflibhandler.h"
#include "gifhandler.h"
extern "C" {
    #include "getarg.h"
}

#include <set>
#include <thread>
#include <sstream>


#define NETSCAPE_LOOP_EXTENSION 0xFF
#define NETSCAPE_LOOP_SUB_BLOCK_SIZE 3

void convertTo565RGBBMP(const QString &inputPath, const QString &outputPath) {
    // Load the image
    QImage image(inputPath);
    if (image.isNull()) {
        qWarning("Failed to load image");
        return;
    }

    // Resize the image to 240x240
    QImage resizedImage = image.scaled(240, 240, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // Create a new image with the same dimensions, but in 16-bit 565 RGB format

    // resizedImage.convertToFormat(QImage::Format_RGB16);

    // Save the image as a BMP file
    if (!resizedImage.save(outputPath, "bmp")) {
        qWarning("Failed to save image");
    } else {
        qDebug() << "Image saved successfully";
    }
}

void convertPngTo565RGBBMP(const QString &inputPath, const QString &outputPath) {
    QImage image(inputPath);
    if (image.isNull()) {
        qWarning("Failed to load image");
        return;
    }
    image.scaled(240, 240, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    image.convertToFormat(QImage::Format_RGB16);
    QImage destBackground(image.size(), QImage::Format_RGB16);
    destBackground.fill("#FFFFFF");

    QPainter p(&destBackground);
    p.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    p.drawImage(0, 0, image);
    QImage result = QPixmap::fromImage(destBackground).toImage();

    if (!image.save(outputPath, "bmp")) {
        qWarning("Failed to save image");
    } else {
        qDebug() << "Image saved successfully";
    }
}

QByteArray imageFileToByteArray(const QString &filePath, QString format) {
    // Load the image from the file
    QImage image(filePath);
    if (image.isNull()) {
        qWarning() << "Failed to load image";
        return QByteArray();
    }

    // Convert the image to a byte array
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, format.toStdString().c_str()); // You can specify the format here (e.g., "BMP", "PNG", "JPEG")

    return byteArray;
}

QString getImageFormat(const QUrl &imagePath)
{
    QImageReader reader(imagePath.toLocalFile());
    QString format = reader.format();
    if (format.isEmpty()) {
        qDebug() << "Failed to detect the image format";
        return QString();
    }

    return format;
}

bool saveByteArrayToFile(const QString &filePath, const QByteArray &data) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing:" << file.errorString();
        return false;
    }

    if (file.write(data) == -1) {
        qWarning() << "Failed to write data to file:" << file.errorString();
        file.close();
        return false;
    }

    file.close();
    return true;
}

void convertImage()
{
    QString inputPath = "C:/Users/ASUS/Pictures/Saved Pictures/twitter.png";
    QString outputPath = "C:/Users/ASUS/Pictures/Saved Pictures/twitter-convert.bmp";


    QString format = getImageFormat(QUrl::fromLocalFile(inputPath));

    qDebug() << format;

    convertTo565RGBBMP(inputPath, outputPath);

    QByteArray byteArray = imageFileToByteArray(outputPath, format);
    // Optionally, save the byte array to a file to verify the output

    // Print the byte array size
    qDebug() << "Byte array size:" << byteArray.size();

    // Create a QByteArray
    QByteArray header;

    // Create a QDataStream and associate it with the byteArray
    QDataStream stream(&header, QIODevice::WriteOnly);

    // Set the byte order for the stream (big-endian or little-endian)
    stream.setByteOrder(QDataStream::LittleEndian); // or QDataStream::BigEndian

    if (format == "bmp") {
        // Define the unsigned 16-bit integer value
        quint16 value = 0x0048;

        // Write the unsigned 16-bit integer to the QByteArray
        stream << value;
    } else if (format == "jpeg" || format == "jpg") {
        // Define the unsigned 16-bit integer value
        quint16 value = 0x0046;

        // Write the unsigned 16-bit integer to the QByteArray
        stream << value;
    } else if (format == "png") {
        // Define the unsigned 16-bit integer value
        quint16 value = 0x0047;

        // Write the unsigned 16-bit integer to the QByteArray
        stream << value;
    } else
        return;


    // Debug output to see the resulting QByteArray
    qDebug() << "QByteArray:" << header.toHex();

    QByteArray screenResource;
    screenResource.append(header);
    screenResource.append(byteArray);

    QString textFilePath = "C:/Users/ASUS/Pictures/Saved Pictures/image-00-jpg";
    if (saveByteArrayToFile(textFilePath, screenResource)) {
        qDebug() << "File saved successfully!";
    } else {
        qDebug() << "Failed to save file.";
    }
}

QByteArray saveImageToByteArray(const QImage &image, const QString &format) {
    // Check if the requested format is supported
    if (!QImageWriter::supportedImageFormats().contains(format.toLower().toUtf8())) {
        qWarning() << "Format" << format << "is not supported.";
        return QByteArray();
    }

    QByteArray byteArray;
    QBuffer buffer(&byteArray);

    // Open the buffer in write-only mode
    buffer.open(QIODevice::WriteOnly);

    // Set up the QImageWriter to write into the buffer in the specified format
    QImageWriter writer(&buffer, format.toUtf8());

    // Write the image to the buffer
    if (!writer.write(image)) {
        qWarning() << "Failed to save image to QByteArray:" << writer.errorString();
        return QByteArray();
    }

    // Return the QByteArray containing the image data
    qDebug() << "Image saved successfully to QByteArray. Size:" << byteArray.size();
    return byteArray;
}

void PrintExtensionBlockHexToDebug(const ExtensionBlock *extBlock) {
    if (extBlock == NULL) {
        qDebug() << "ExtensionBlock is NULL.";
        return;
    }

    // Use a stringstream to accumulate the output
    std::stringstream ss;

    ss << "Extension Function: 0x" << std::hex << std::uppercase << extBlock->Function << std::endl;
    ss << "Byte Count: " << extBlock->ByteCount << std::endl;

    ss << "Hex Data: ";
    for (int i = 0; i < extBlock->ByteCount; ++i) {
        ss << "0x" << std::hex << std::uppercase << (int)extBlock->Bytes[i] << " ";
    }
    ss << std::endl;

    // Convert the stringstream to a string and output via qDebug
    qDebug() << QString::fromStdString(ss.str());
}

// Function to clone a GIF file, including the looping extension
void printInfoOfGif(const char* fileName) {
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
    // qDebug <<"Version: %s\n", gif->SVersion);
    qDebug() <<"Screen size: %dx%d\n"<< gif->SWidth << gif->SHeight;
    qDebug() <<"Color resolution: %d\n" << gif->SColorResolution;
    qDebug() <<"Background color index: %d\n" << gif->SBackGroundColor;
    qDebug() <<"Aspect ratio: %d\n" << gif->AspectByte;
    qDebug() <<"Image count: %d\n" << gif->ImageCount;

    if (gif->SColorMap != NULL) {
        //print the color map
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
    // Print information about each image in the GIF file
    for (int i = 0; i < gif->ImageCount; i++) {
        SavedImage *image = &gif->SavedImages[i];
        qDebug() <<"Image %d:\n" << i + 1;
        qDebug() <<"  Image position: left: " << image->ImageDesc.Left << " top: " << image->ImageDesc.Top;
        qDebug() <<"  Image size: width: " << image->ImageDesc.Width << " height: " << image->ImageDesc.Height;
        qDebug() <<"  Interlaced: " << image->ImageDesc.Interlace;

        // if (image->ImageDesc.ColorMap != NULL) {
        //     qDebug() <<"  Color map size: " << image->ImageDesc.ColorMap->ColorCount;
        //     qDebug() <<"  Color map bits per pixel: " << image->ImageDesc.ColorMap->BitsPerPixel;
        //     qDebug() <<"  Color map colors: ";
        //     for (int j = 0; j < image->ImageDesc.ColorMap->ColorCount; j++) {
        //         GifColorType color = image->ImageDesc.ColorMap->Colors[j];
        //         qDebug() <<"    Color j: " << j << " r: " << color.Red << " g: " << color.Green << " b: " << color.Blue;
        //     }
        // }

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

    // Close the GIF file
    if (DGifCloseFile(gif, &error) == GIF_ERROR) {
        qDebug() << "Error closing GIF file: %s\n" << GifErrorString(error);
        exit(1);
    }
    qDebug() << "read done!";
}

// Function to add a Graphics Control Extension to control delay or transparency
bool AddGraphicsControlExtension(GifFileType *gifFile, int imageIndex, int delayTimeCentiseconds) {
    if (gifFile == nullptr || imageIndex < 0 || imageIndex >= gifFile->ImageCount) return false;

    GraphicsControlBlock gcb;
    gcb.DisposalMode = DISPOSAL_UNSPECIFIED;
    gcb.UserInputFlag = false;
    gcb.DelayTime = delayTimeCentiseconds; // Delay time in 100ths of a second
    gcb.TransparentColor = NO_TRANSPARENT_COLOR;

    // Add the Graphics Control Extension (GCE) for this frame
    if (EGifGCBToSavedExtension(&gcb, gifFile, imageIndex) == GIF_ERROR) {
        qDebug() << Q_FUNC_INFO << " failed!";
        return false;
    }

    return true;
}

bool convertImageByFrame(const QImage &qImage, GifFileType *GifFile) {
    // Check if the image is valid
    if (qImage.isNull()) {
        return false;
    }

    int Width = qImage.width();
    int Height = qImage.height();
    int ColorMapSize = 256;

    // Allocate r, g, b buffers
    GifByteType *RedBuffer = (GifByteType *)malloc(Width * Height);
    GifByteType *GreenBuffer = (GifByteType *)malloc(Width * Height);
    GifByteType *BlueBuffer = (GifByteType *)malloc(Width * Height);

    // Initialize the buffers
    memset(RedBuffer, 0, Width * Height);
    memset(GreenBuffer, 0, Width * Height);
    memset(BlueBuffer, 0, Width * Height);

    // Loop over each pixel in the QImage and copy it to the Gif's RasterBits
    for (int y = 0; y < Height; ++y) {
        for (int x = 0; x < Width; ++x) {
            QColor pixelColor = qImage.pixelColor(x, y);
            int colorIndex = y * Width + x;
            RedBuffer[colorIndex] = pixelColor.red();
            GreenBuffer[colorIndex] = pixelColor.green();
            BlueBuffer[colorIndex] = pixelColor.blue();
        }
    }

    // Create a color map object
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

void creatingGifFileFromQImage2(const char* srcFileName, const char* destFileName) {
    QImageReader reader(QString::fromLocal8Bit(srcFileName));
    QImage image = reader.read();
    image = image.convertToFormat(QImage::Format_Indexed8);
    image = image.scaled(QSize(240, 240), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    if (image.isNull()) {
        qDebug() << "Failed to read image";
        return;
    }

    int Width = image.width();
    int Height = image.height();

    int ColorMapSize = 256;
    GifByteType *RedBuffer = (GifByteType *)malloc(Width * Height);
    GifByteType *GreenBuffer = (GifByteType *)malloc(Width * Height);
    GifByteType *BlueBuffer = (GifByteType *)malloc(Width * Height);

    memset(RedBuffer, 0, Width * Height);
    memset(GreenBuffer, 0, Width * Height);
    memset(BlueBuffer, 0, Width * Height);

    for (int y = 0; y < Height; ++y) {
        for (int x = 0; x < Width; ++x) {
            QColor pixelColor = image.pixelColor(x, y);
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
	}

    if (GifQuantizeBuffer(Width, Height, &ColorMapSize, RedBuffer,
	                      GreenBuffer, BlueBuffer, OutputBuffer,
	                      OutputColorMap->Colors) == GIF_ERROR) {
        qDebug() << "Failed to quantize image";
		return;
	}
    free((char *)RedBuffer);
	free((char *)GreenBuffer);
	free((char *)BlueBuffer);

    // Create a GIF file from the QImage
    GifFileType *GifFile = NULL;
    if ((GifFile = EGifOpenFileName(destFileName, false, NULL)) == NULL) {
        qDebug() << "Failed to create GIF file";
        return;
    }

    if (EGifPutScreenDesc(GifFile, Width, Height, 8, 0,
	                      OutputColorMap) == GIF_ERROR ||
	    EGifPutImageDesc(GifFile, 0, 0, Width, Height, false, NULL) ==
	        GIF_ERROR) {
        qDebug() << "Failed to write screen descriptor or image descriptor";
        return;
	}

    GifByteType *Ptr = OutputBuffer;

    for (int i = 0; i < Height; i++) {
        if (EGifPutLine(GifFile, Ptr, Width) == GIF_ERROR) {
            qDebug() << "Failed to write line";
            return;
        }
        Ptr += Width;
    }
    
    if (EGifCloseFile(GifFile, NULL) == GIF_ERROR) {
        qDebug() << "Failed to close GIF file";
        return;
    }

    qDebug() << "GIF file created successfully";
}

void creatingGifFileFromQImage3(const char *srcFileName, const char *destFileName) {
    QImageReader reader(QString::fromLocal8Bit(srcFileName));

    GifFileType *GifFile = NULL;
    if ((GifFile = EGifOpenFileName(destFileName, false, NULL)) == NULL) {
        qDebug() << "Failed to create GIF file";
        return;
    }

    if (EGifPutScreenDesc(GifFile, 240, 240, 8, 0, NULL) == GIF_ERROR) {
        qDebug() << "Failed to write screen descriptor";
        return;
    }

    GifFile->SavedImages = (SavedImage *)malloc(sizeof(SavedImage) * reader.imageCount());

    for (int i = 0; i < reader.imageCount(); ++i) {
        QImage image = reader.read();
        if (image.isNull()) {
            qDebug() << "Failed to read image";
            return;
        }
        image = image.convertToFormat(QImage::Format_Indexed8);
        image = image.scaled(QSize(240, 240), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        if (i == 0) {
            // Add first extension block for looping
            ExtensionBlock *loopExtBlock = (ExtensionBlock *)malloc(sizeof(ExtensionBlock) * 3);

            // Set NetLoop 2.0 to block 1
            loopExtBlock[0].ByteCount = 11;
            loopExtBlock[0].Bytes = (GifByteType *)malloc(11);
            loopExtBlock[0].Function = APPLICATION_EXT_FUNC_CODE;
            loopExtBlock[0].Bytes[0] = 0x4E;
            loopExtBlock[0].Bytes[1] = 0x45;
            loopExtBlock[0].Bytes[2] = 0x54;
            loopExtBlock[0].Bytes[3] = 0x53;
            loopExtBlock[0].Bytes[4] = 0x43;
            loopExtBlock[0].Bytes[5] = 0x41;
            loopExtBlock[0].Bytes[6] = 0x50;
            loopExtBlock[0].Bytes[7] = 0x45;
            loopExtBlock[0].Bytes[8] = 0x32;
            loopExtBlock[0].Bytes[9] = 0x2E;
            loopExtBlock[0].Bytes[10] = 0x30;

            // Set the loop count to 0 (infinite)
            loopExtBlock[1].ByteCount = 3;
            loopExtBlock[1].Bytes = (GifByteType *)malloc(3);
            loopExtBlock[1].Function = CONTINUE_EXT_FUNC_CODE;
            loopExtBlock[1].Bytes[0] = 0x01;
            loopExtBlock[1].Bytes[1] = 0x00;
            loopExtBlock[1].Bytes[2] = 0x00;

            // Set Graphics block
            loopExtBlock[2].ByteCount = 4;
            loopExtBlock[2].Bytes = (GifByteType *)malloc(4);

            GraphicsControlBlock gcb;
            gcb.DisposalMode = 1;
            gcb.DelayTime = reader.nextImageDelay()/10;
            gcb.TransparentColor = 0;
            gcb.TransparentColor = -1;
            EGifGCBToExtension(&gcb, (GifByteType*)loopExtBlock[2].Bytes);
            loopExtBlock[2].Function = GRAPHICS_EXT_FUNC_CODE;

            if (EGifPutExtensionLeader(GifFile, APPLICATION_EXT_FUNC_CODE) == GIF_ERROR) {
                qDebug() << "EGifPutExtensionLeader failed!";
            }

            if (EGifPutExtensionBlock(GifFile, 11, (GifByteType*)loopExtBlock[0].Bytes) == GIF_ERROR) {
                qDebug() << "EGifPutExtensionBlock failed!";
            }

            if (EGifPutExtensionBlock(GifFile, 3, (GifByteType*)loopExtBlock[1].Bytes) == GIF_ERROR) {
                qDebug() << "EGifPutExtensionBlock failed!";
            }

            if (EGifPutExtensionBlock(GifFile, 4, (GifByteType*)loopExtBlock[2].Bytes) == GIF_ERROR) {
                qDebug() << "EGifPutExtensionBlock failed!";
            }

            if (EGifPutExtensionTrailer(GifFile) == GIF_ERROR) {
                qDebug() << "EGifPutExtensionTrailer failed!";
            }

        } else {
            GraphicsControlBlock gcb;
            gcb.DisposalMode = 1;
            gcb.DelayTime = reader.nextImageDelay()/10;
            gcb.TransparentColor = 0;
            gcb.TransparentColor = -1;
            GifByteType *GifExtension = (GifByteType*)malloc(4);
            EGifGCBToExtension(&gcb, GifExtension);
            if (EGifPutExtension(GifFile, GRAPHICS_EXT_FUNC_CODE, 4, (void*)GifExtension) == GIF_ERROR) {
                qDebug() << "EGifPutExtension failed!";
            }
        }

        if (convertImageByFrame(image, GifFile) == false) {
            qDebug() << "Failed to convert image";
            return;
        }

        reader.jumpToNextImage();
    }

    if (EGifCloseFile(GifFile, NULL) == GIF_ERROR) {
        qDebug() << "Failed to close GIF file";
        return;
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    // const char *srcFileName = "C:/Users/ASUS/Pictures/Saved Pictures/gif-image.gif";
    // const char *destFileName = "C:/Users/ASUS/Pictures/Saved Pictures/clone.gif";

    // cloneGifFile(srcFileName, destFileName);

    // std::this_thread::sleep_for(std::chrono::seconds(15));
    const char* srcFileName = "C:/Users/ASUS/Pictures/Saved Pictures/gif-image.gif";
    const char* destFileName = "C:/Users/ASUS/Pictures/Saved Pictures/gif-image-test.gif";
    // creatingGifFileFromQImage2(srcFileName ,
    //                           destFileName);
    // printInfoOfGif("C:/Users/ASUS/Pictures/Saved Pictures/gif-image-test.gif");
    creatingGifFileFromQImage3(srcFileName, destFileName);

    return a.exec();
}
