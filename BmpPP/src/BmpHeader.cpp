#include "BmpPP/BmpHeader.h"

namespace Leonetienne::BmpPP {

    std::vector<std::uint8_t> BmpHeader::ToBytes() const {

        std::vector<std::uint8_t> data;

        InsertBytes(data, fileHeader.signature);
        InsertBytes(data, fileHeader.filesize);
        InsertBytes(data, fileHeader.reserved0);
        InsertBytes(data, fileHeader.reserved1);
        InsertBytes(data, fileHeader.addressPixelBuffer);

        InsertBytes(data, dibHeader.dibHeaderSize);
        InsertBytes(data, dibHeader.imageWidth);
        InsertBytes(data, dibHeader.imageHeight);
        InsertBytes(data, dibHeader.numColorPlanes);
        InsertBytes(data, dibHeader.numBitsPerPixel);
        InsertBytes(data, dibHeader.compressionUsed);
        InsertBytes(data, dibHeader.pixelArraySize);
        InsertBytes(data, dibHeader.printResolutionHorizontal);
        InsertBytes(data, dibHeader.printResolutionVertical);
        InsertBytes(data, dibHeader.numColorsInPalette);
        InsertBytes(data, dibHeader.numImportantColors);

        return data;
    }

}
