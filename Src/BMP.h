#ifndef BMPPP_BMP_H
#define BMPPP_BMP_H

#include <Eule/Vector2.h>
#include <Eule/Rect.h>
#include <vector>
#include <cstdint>
#include "Colormodes.h"

namespace Leonetienne::BmpPP {

    class BmpWriter;
    class BmpReader;

    class BMP {
    public:
        //! Will create an uninitialized image
        BMP();

        //! Will create an image with the entire pixel buffer set to 0
        explicit BMP(const Eule::Vector2i& size, const Colormode& colormode = Colormode::RGBA);

        //! Will create a image and read it from a bmp file
        explicit BMP(const std::string& filename);

        //! Will return a pointer to the first byte of a pixel at a given position
        [[nodiscard]] std::uint8_t* GetPixel(const Eule::Vector2i& position);

        //! Will return a pointer to the first byte of a pixel at a given position
        [[nodiscard]] const std::uint8_t* GetPixel(const Eule::Vector2i& position) const;

        //! Will set the color of a pixel at a given position
        void SetPixel(const Eule::Vector2i& position, const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a = 0xFF);

        //! Will basically reconstruct this image, to fit a new resolution
        void ReInitialize(const Eule::Vector2i& size);

        //! Will basically reconstruct this image, to fit a new resolution and new format
        void ReInitialize(const Eule::Vector2i& size, const Colormode& colormode);

        //! Will return a pointer to the raw pixel data
        [[nodiscard]] std::uint8_t* data();

        //! Will return a pointer to the raw pixel data
        [[nodiscard]] const std::uint8_t* data() const;

        //! Will return the dimensions of the image
        [[nodiscard]] const Eule::Vector2i& GetDimensions() const;

        //! Will return the color mode of the image
        [[nodiscard]] const Colormode& GetColormode() const;

        //! Will return the amount of channels used
        [[nodiscard]] std::size_t GetNumChannels() const;

        //! Will return the size of the raw pixel buffer, in bytes
        [[nodiscard]] std::size_t GetPixelbufferSize() const;

        //! Will return whether this image is initialized or not
        [[nodiscard]] bool IsInitialized() const;

        //! Will write the bmp image to a file.
        //! Returns false, if unable to open the file
        bool Write(const std::string& filename) const;

        //! Will read a bmp image from a file.
        //! Returns false, if unable to open, or parse, file
        bool Read(const std::string& filename);

        //! Will compare two images for being exactly identical regarding resolution, bit depth, and pixel values.
        bool operator==(const BMP& other) const;

        //! Will compare two images for not being exactly identical regarding resolution, bit depth, and pixel values.
        bool operator!=(const BMP& other) const;

        //! Will mirror the image horizontally, and return it as a new image
        BMP MirrorHorizontally() const;

        //! Will mirror the image vertically, and return it as a new image
        BMP MirrorVertically() const;

        //! Will rotate the image by 90deg, clockwise, and return it as a new image
        BMP Rotate90degClockwise() const;

        //! Will rotate the image by 90deg, counterclockwise, and return it as a new image
        BMP Rotate90degCounterclockwise() const;

        //! Will rotate the image by 180deg, and return it as a new image
        BMP Rotate180deg() const;

        //! Will convert the images colormode
        void ConvertColormode(const Colormode& colormode);

        //! Will swap two channels. Useful for, for example, easy BGR to RGB conversion.
        void SwapChannels(const std::size_t& channel1, const std::size_t& channel2);

        //! Will copy the specified rectangle-area, and return it as a new image
        BMP Crop(const Eule::Rect& area) const;

        //! Will fill a specific channel with a value
        void FillChannel(const std::size_t& channel, const std::uint8_t value);

    private:
        Eule::Vector2i size;
        Colormode colormode;
        std::vector<std::uint8_t> pixelBuffer;
        bool isInitialized = false;

        friend class BmpWriter;
        friend class BmpReader;
    };

}

#endif //BMPPP_BMP_H
