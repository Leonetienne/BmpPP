#include "BmpPP/BmpWriter.h"
#include "BmpPP/BmpHeader.h"
#include "BmpPP/Bmp.h"
#include <fstream>

namespace Leonetienne::BmpPP {

    bool BmpWriter::Write(const BMP &image, const std::string& filename) {
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
        bmpHeader.dibHeader.imageWidth = image.size.x;
        bmpHeader.dibHeader.imageHeight = image.size.y;
        bmpHeader.dibHeader.numBitsPerPixel = image.GetNumChannels() * 8;
        // The size of the pixel array is not known yet (because rows require to be padded)


        // Pack pixel values
        std::vector<std::uint8_t> packedPixels;
        packedPixels.reserve(image.pixelBuffer.size());

        // How many channels do we have?
        const std::size_t numChannels = image.GetNumChannels();

        // Calculate how many padding bytes to add per row
        const std::size_t paddingBytesPerRow = (4 - ((image.size.x * numChannels) % 4)) % 4;

        // Iterate over all pixel rows
        for (std::int64_t y = image.size.y-1; y >= 0; y--) {
            const std::size_t rowIndex = y * image.size.x * numChannels;

            for (std::size_t x = 0; x < image.size.x; x++) {
                const std::size_t pixelIndex = rowIndex + x * numChannels;

                // Write actual pixel values to row
                switch (image.colormode) {
                    case Colormode::RGBA:
                        // Write B byte
                        packedPixels.insert(
                                packedPixels.cend(),
                                image.pixelBuffer[pixelIndex + 2]
                        );
                        // Write G byte
                        packedPixels.insert(
                                packedPixels.cend(),
                                image.pixelBuffer[pixelIndex + 1]
                        );
                        // Write R byte
                        packedPixels.insert(
                                packedPixels.cend(),
                                image.pixelBuffer[pixelIndex + 0]
                        );
                        // Write A byte
                        packedPixels.insert(
                                packedPixels.cend(),
                                image.pixelBuffer[pixelIndex + 3]
                        );
                        break;

                    case Colormode::RGB:
                        // Write B byte
                        packedPixels.insert(
                                packedPixels.cend(),
                                image.pixelBuffer[pixelIndex + 2]
                        );
                        // Write G byte
                        packedPixels.insert(
                                packedPixels.cend(),
                                image.pixelBuffer[pixelIndex + 1]
                        );
                        // Write R byte
                        packedPixels.insert(
                                packedPixels.cend(),
                                image.pixelBuffer[pixelIndex + 0]
                        );
                        break;
                }

            }

            // Add row padding
            // Since we have to pad to a multiple of 4, the padding will never be more than four bytes
            for (std::size_t i = 0; i < paddingBytesPerRow; i++)
                packedPixels.insert(packedPixels.cend(), 0x0);
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

}
