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

    private:
        //! Will return the corresponding pixel size (in bytes) of a colormode. Like, 3 for RGB and 4 for RGBA.
        static int ColormodeToPixelSize(const Colormode& colormode);

        Eule::Vector2i size;
        Colormode colormode;
        std::vector<std::uint8_t> pixelBuffer;
    };

}

#endif //BMPPP_BMP_H
