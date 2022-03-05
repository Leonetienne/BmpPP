#ifndef BMPPP_EXEC_BMPHEADER_H
#define BMPPP_EXEC_BMPHEADER_H

#include <cstdint>
#include <vector>

namespace Leonetienne::BmpPP {

    // This struct represents the actual image file.
    class BmpHeader {
    public:

        //! This header contains information about the file itself.
        struct FileHeader {
            //! Constant value. These two bytes identify a bmp file.
            const std::uint16_t signature = 0x4D42;

            //! The size of the entire file, in bytes.
            std::uint32_t filesize;

            //! Reserved...
            std::uint16_t reserved0;

            //! Reserved...
            std::uint16_t reserved1;

            //! The address where the pixel buffer / pixel array begins.
            std::uint32_t addressPixelBuffer;

            // Since C++ tends to pad structures, we have to explicitly define how many bytes
            // this struct is long. For example, sizeof(FileHeader) (without the size field)
            // returns 16, even though it really should only be 14.
            // This has to be set at the END of the struct, as to not be written to the file itself.
            static constexpr std::uint16_t NBYTES = 14;


        } fileHeader;

        //! This header contains information about the image itself.
        //! We are using the BITMAPINFOHEADER format.
        struct DibHeader {
            //! The size of the dibHeader (since there are multiple to choose from).
            //! This one 40 bytes, fix.
            const std::uint32_t dibHeaderSize = 40;

            //! The width of the image, in pixels.
            std::int32_t imageWidth;

            //! The height of the image, in pixels.
            std::int32_t  imageHeight;

            //! The amount of color planes used. Always 1.
            const std::uint16_t numColorPlanes = 1;

            //! The amount of bits (not bytes!) per pixel.
            std::uint16_t numBitsPerPixel;

            //! We don't use any compression.
            const std::uint32_t compressionUsed = 0;

            //! The size of the pixel array (including row padding)
            std::uint32_t pixelArraySize;

            //! The amount of pixels per meter on the horizontal axis. Kinda useless for our purposes, but required to be in the header.
            const std::int32_t printResolutionHorizontal = 2835;

            //! The amount of pixels per meter on the vertical axis. Kinda useless for our purposes, but required to be in the header.
            const std::int32_t printResolutionVertical = 2835;

            //! We don't have any colors in our color palette
            const std::uint32_t numColorsInPalette = 0;

            //! All colors are important
            const std::uint32_t numImportantColors = 0;

            // This has to be set at the END of the struct, as to not be written to the file itself.
            static constexpr std::uint16_t NBYTES = 40;

        } dibHeader;

        //! Will return bytes representing the header
        //! Just dumping the memory won't work, because the compiler may insert padding in between members
        std::vector<std::uint8_t> ToBytes() const;

    private:
        template <typename  T>
        void InsertBytes(std::vector<std::uint8_t>& vec, const T& value) const {
            vec.insert(
                    vec.cend(),
                    static_cast<const std::uint8_t*>(static_cast<const void*>(&value)),
                    static_cast<const std::uint8_t*>(static_cast<const void*>(&value)) + sizeof(value)
            );
            return;
        };
    };
}

#endif //BMPPP_EXEC_BMPHEADER_H
