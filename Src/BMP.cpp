#include "BMP.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "BmpHeader.h"

namespace Leonetienne::BmpPP {

    BMP::BMP(const Eule::Vector2i &size, const Colormode& colormode)
        :
        size { size },
        colormode { colormode }
    {

        pixelBuffer.clear();
        pixelBuffer.resize(size.x * size.y * GetNumColorChannels());

        return;
    }

    bool BMP::Write(const std::string &filename) const {

        // Create the bmp header
        BmpHeader bmpHeader;

        // Populate file header
        bmpHeader.fileHeader.addressPixelBuffer =
                BmpHeader::FileHeader::NBYTES +
                BmpHeader::DibHeader::NBYTES
                + 2; // We have to put two padding-bytes behind the headers.
                     // The pixel data must start at an address that is a multiple of 4.

        // The size of the bmp file is not yet known...

        // Populate dib header
        bmpHeader.dibHeader.imageWidth = size.x;
        bmpHeader.dibHeader.imageHeight = size.y;
        bmpHeader.dibHeader.numBitsPerPixel = GetNumColorChannels() * 8;
        // The size of the pixel array is not known yet (because rows require to be padded)


        // Pack pixel values
        std::vector<std::uint8_t> packedPixels;
        packedPixels.reserve(pixelBuffer.size());

        // How many channels do we have?
        const std::size_t numChannels = GetNumColorChannels();

        // Calculate how many padding bytes to add per row
        std::size_t paddingBytesPerRow = (4 - ((size.x * numChannels) % 4)) % 4;

        // Iterate over all pixel rows
        for (std::size_t y = 0; y < size.y; y++) {
            const std::size_t rowIndex = y * size.x * numChannels;

            for (std::size_t x = 0; x < size.x; x++) {
                    const std::size_t pixelIndex = rowIndex + x * numChannels;

                    // Write actual pixel values to row
                    switch (colormode) {
                        case Colormode::RGBA:
                            // Write B byte
                            packedPixels.insert(
                                packedPixels.cend(),
                                pixelBuffer[pixelIndex + 2]
                            );
                            // Write G byte
                            packedPixels.insert(
                                packedPixels.cend(),
                                pixelBuffer[pixelIndex + 1]
                            );
                            // Write R byte
                            packedPixels.insert(
                                packedPixels.cend(),
                                pixelBuffer[pixelIndex + 0]
                            );
                            // Write A byte
                            packedPixels.insert(
                                packedPixels.cend(),
                                pixelBuffer[pixelIndex + 3]
                            );
                            break;

                        case Colormode::RGB:
                            // Write B byte
                            packedPixels.insert(
                                    packedPixels.cend(),
                                    pixelBuffer[pixelIndex + 2]
                            );
                            // Write G byte
                            packedPixels.insert(
                                    packedPixels.cend(),
                                    pixelBuffer[pixelIndex + 1]
                            );
                            // Write R byte
                            packedPixels.insert(
                                    packedPixels.cend(),
                                    pixelBuffer[pixelIndex + 0]
                            );
                            break;
                    }

                    // Add row padding
                    // Since we have to pad to a multiple of 4, the padding will never be more than four bytes
                    for (std::size_t i = 0; i < paddingBytesPerRow; i++)
                        packedPixels.insert(packedPixels.cend(), 0x0);
            }
        }

        // Now we can finally set the fileSize field in the file header,
        // and the pixelArraySize in the dib header
        bmpHeader.fileHeader.filesize =
                bmpHeader.fileHeader.addressPixelBuffer +
                packedPixels.size();

        bmpHeader.dibHeader.pixelArraySize = packedPixels.size();

        // Write to file
        std::ofstream ofs(filename, std::ofstream::binary);
        if (!ofs.good())
            return false;


        // Write the header
        const std::vector<std::uint8_t> headerBytes = bmpHeader.ToBytes();
        ofs.write((const char*)headerBytes.data(), headerBytes.size());

        // Write two padding bytes
        ofs.write("\0\0", 2);

        // Write the pixel data
        ofs.write((const char*)packedPixels.data(), packedPixels.size());

        ofs.close();

        return true;
    }

    std::uint8_t *BMP::GetPixel(const Eule::Vector2i &position) {
        const std::size_t pixelIndex =
                (position.y * size.x + position.x) * GetNumColorChannels();

        if (pixelIndex >= pixelBuffer.size())
            throw std::runtime_error("Pixel index out of range!");

        return pixelBuffer.data() + pixelIndex;
    }

    const std::uint8_t *BMP::GetPixel(const Eule::Vector2i &position) const {
        const std::size_t pixelIndex =
                (position.y * size.x + position.x) * GetNumColorChannels();

        if (pixelIndex >= pixelBuffer.size())
            throw std::runtime_error("Pixel index out of range!");

        return pixelBuffer.data() + pixelIndex;
    }

    void BMP::SetPixel(const Eule::Vector2i &position,
                  const std::uint8_t r,
                  const std::uint8_t g,
                  const std::uint8_t b,
                  const std::uint8_t a) {

        std::uint8_t* pixel = GetPixel(position);

        switch (colormode) {
            case Colormode::RGBA:
                pixel[0] = r;
                pixel[1] = g;
                pixel[2] = b;
                pixel[3] = a;
                break;

            case Colormode::RGB:
                pixel[0] = r;
                pixel[1] = g;
                pixel[2] = b;
                break;
        }

        return;
    }

    std::uint8_t *BMP::data() {
        return pixelBuffer.data();
    }

    const std::uint8_t *BMP::data() const {
        return pixelBuffer.data();
    }

    const Eule::Vector2i &BMP::GetDimensions() const {
        return size;
    }

    const Colormode &BMP::GetColormode() const {
        return colormode;
    }

    std::size_t BMP::GetNumColorChannels() const {
        switch (colormode) {
            case Colormode::RGB:
                return 3;

            case Colormode::RGBA:
                return 4;
        }

        // Unreachable
        return -1;
    }

    std::size_t BMP::GetPixelbufferSize() const {
        return pixelBuffer.size();
    }

}
