#ifndef BMPPP_BMP_H
#define BMPPP_BMP_H

#include <Eule/Vector2.h>
#include <vector>
#include <cstdint>
#include "Colormodes.h"

namespace Leonetienne::BmpPP {

    class BMP {
    public:
        explicit BMP(const Eule::Vector2i& size, const Colormode& colormode = Colormode::RGBA);

        //! Will write the bmp image to a file.
        bool Write(const std::string& filename) const;

        //! Will return a pointer to the first byte of a pixel at a given position
        std::uint8_t* GetPixel(const Eule::Vector2i& position);

        //! Will return a pointer to the first byte of a pixel at a given position
        const std::uint8_t* GetPixel(const Eule::Vector2i& position) const;

        //! Will set the color of a pixel at a given position
        void SetPixel(const Eule::Vector2i& position, const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a = 0xFF);

        //! Will return a pointer to the raw pixel data
        std::uint8_t* data();

        //! Will return a pointer to the raw pixel data
        const std::uint8_t* data() const;

        //! Will return the dimensions of the image
        const Eule::Vector2i& GetDimensions() const;

        //! Will return the color mode of the image
        const Colormode& GetColormode() const;

        //! Will return the amount of color channels used
        std::size_t GetNumColorChannels() const;

        //! Will return the size of the raw pixel buffer, in bytes
        std::size_t GetPixelbufferSize() const;

    private:
        Eule::Vector2i size;
        Colormode colormode;
        std::vector<std::uint8_t> pixelBuffer;
    };

}

#endif //BMPPP_BMP_H
