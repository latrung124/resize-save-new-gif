/*
* GifConverterImpl.h
* Author: trung.la
* Date: 2024-12-20
*/

#ifndef GIFCONVERTERIMPL_H
#define GIFCONVERTERIMPL_H

#include "IGifConverter.h"

#define NETSCAPE_LOOP_EXTENSION 0xFF
#define NETSCAPE_LOOP_SUB_BLOCK_SIZE 3

#include "Gif89aReader.h"

class QImage;

struct GifFileType;
struct ExtensionBlock;

class GifConverterImpl : public IGifConverter
{
public:
    GifConverterImpl() = default;
    ~GifConverterImpl() = default;

    bool readGifFile(const char* fileName) override;
    bool createGifFileFromQImage(const char* srcFileName, const char* destFileName) override;

private:
    bool AddGraphicsControlExtension(GifFileType *gifFile, int imageIndex, int delayTimeCentiseconds);
    void printInfoOfGif(const char* fileName);
    void PrintExtensionBlockHexToDebug(const ExtensionBlock *extBlock);
    bool convertImageByFrame(const QImage &qImage, GifFileType *GifFile);

    Gif89aReader m_gifReader;
};

#endif // GIFCONVERTERIMPL_H
