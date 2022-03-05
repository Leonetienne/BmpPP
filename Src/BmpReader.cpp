#include "BmpReader.h"
#include "Colormodes.h"
#include "BMP.h"
#include <fstream>
#include <cstdint>

#ifdef _BMPLIB_DEBUG_OUTPUT_
#include <iostream>
#endif

namespace Leonetienne::BmpPP {

    bool BmpReader::Read(BMP &image, const std::string &filename) {
        // Open file
        std::ifstream ifs(filename, std::ifstream::binary);
        if (!ifs.good())
            return false;

        // When reading the image, we don't care about most of the header.
        // All we want is the images resolution, bits-per-pixel, and the pixelbuffer address...
        // This is because we do not support ALL of bmp, but just the most common formats...

        // Fetch bmp signature
        std::uint16_t signature;
        ReadBytes(ifs, signature);

        // Does the signature match?
        if (signature != 0x4D42) {
            #ifdef _BMPLIB_DEBUG_OUTPUT_
            std::cerr << "Bmp signature doesn't match" << std::endl;
            #endif
            ifs.close();
            return false;
        }

        // Skip eight useless bytes (filesize + reserved0 + reserved1)
        ifs.ignore(8);

        // Read the address of the pixel buffer
        std::uint32_t pixelBufferAddress;
        ReadBytes(ifs, pixelBufferAddress);

        // Read the size of the dib header
        std::uint32_t dibHeaderSize;
        ReadBytes(ifs, dibHeaderSize);

        std::uint32_t width;
        std::uint32_t height;
        std::uint16_t bitsPerPixel;

        // Check if what kind of dib header we're dealing with
        // These are the two we're supporting (to read, at least).
        if (dibHeaderSize == 12) {
            // BITMAPCOREHEADER it is

            // Read the width and the height (both 2-byte ints)
            std::uint16_t width_2byte;
            std::uint16_t height_2byte;

            ifs >> width_2byte;
            ifs >> height_2byte;
            ReadBytes(ifs, width_2byte);
            ReadBytes(ifs, height_2byte);

            width = width_2byte;
            height = height_2byte;

            // Read the bits per pixel
            ReadBytes(ifs, bitsPerPixel);
        }
        else if (dibHeaderSize == 40) {
            // BITMAPINFOHEADER it is

            // Read the width and height (both 4-byte signed ints)
            std::int32_t width_4byte_signed;
            std::int32_t height_4byte_signed;

            ReadBytes(ifs, width_4byte_signed);
            ReadBytes(ifs, height_4byte_signed);

            width = width_4byte_signed;
            height = height_4byte_signed;

            // Skip two useless bytes
            ifs.ignore(2);

            // Read the bits per pixel value
            ReadBytes(ifs, bitsPerPixel);
        }
        else if (dibHeaderSize == 124) {
            // BITMAPV5HEADER it is

            // Read the width and height
            ReadBytes(ifs, width);
            ReadBytes(ifs, height);

            // Skip two useless bytes
            ifs.ignore(2);

            // Read the bits per pixel value
            ReadBytes(ifs, bitsPerPixel);
        }
        else {
            #ifdef _BMPLIB_DEBUG_OUTPUT_
            std::cerr << "Unsupported dib header found. Dib header size: " << dibHeaderSize << " bytes." << std::endl;
            #endif
            ifs.close();
            return false;
        }

        // Convert bits per pixel to color mode
        Colormode colormode;
        switch (bitsPerPixel) {
            case 32:
                colormode = Colormode::RGBA;
                break;

            case 24:
                colormode = Colormode::RGB;
                break;

            default:
                #ifdef _BMPLIB_DEBUG_OUTPUT_
                std::cerr << "Unsupported pixel format found (bits per pixel). Bits per pixel: " << bitsPerPixel << std::endl;
                #endif
                ifs.close();
                return false;
        }

        // Now read the pixel array
        // Pre-calculate the channel count
        const std::size_t numChannels = bitsPerPixel / 8;

        // Calculate how much padding there should be between each row
        const std::size_t paddingBytesPerRow = (4 - ((width * numChannels) % 4)) % 4;

        // Calculate how long bytes we should care about per row (so, excluding padding)
        const std::size_t rowWidth = width * numChannels;

        // Create the pixel buffer
        std::vector<std::uint8_t> pixelArray;
        pixelArray.resize(width * height * numChannels);

        // Set the reading-head to the address of the pixel array
        ifs.seekg(pixelBufferAddress);

        // Iterate over all rows, and skip padding after each row
        for (std::int64_t y = height-1; y >= 0; y--) {
            const std::size_t rowIndex = y * width * numChannels;

            for (std::size_t x = 0; x < width; x++) {
                const std::size_t pixelIndex = rowIndex + x * numChannels;

                switch (colormode) {
                    case Colormode::RGBA: {
                        std::uint8_t r, g, b, a;
                        ReadBytes(ifs, b);
                        ReadBytes(ifs, g);
                        ReadBytes(ifs, r);
                        ReadBytes(ifs, a);

                        pixelArray[pixelIndex + 0] = r;
                        pixelArray[pixelIndex + 1] = g;
                        pixelArray[pixelIndex + 2] = b;
                        pixelArray[pixelIndex + 3] = a;
                    }
                    break;

                    case Colormode::RGB: {
                        std::uint8_t r, g, b;
                        ReadBytes(ifs, b);
                        ReadBytes(ifs, g);
                        ReadBytes(ifs, r);

                        pixelArray[pixelIndex + 0] = r;
                        pixelArray[pixelIndex + 1] = g;
                        pixelArray[pixelIndex + 2] = b;
                    }
                    break;
                }
            }

            if (paddingBytesPerRow > 0)
                ifs.ignore(paddingBytesPerRow);
        }

        // We are done with the file
        ifs.close();

        // Now construct our image
        image.ReInitialize(Eule::Vector2i(width, height), colormode);

        // We're a friend-class, so we're going to MOVE (not copy) the pixels over manually. Much faster.
        image.pixelBuffer.swap(pixelArray);

        // Done.
        return true;
    }
}
