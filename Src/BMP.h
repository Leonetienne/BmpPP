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

    private:
        //! Will return the corresponding pixel size (in bytes) of a colormode. Like, 3 for RGB and 4 for RGBA.
        static int ColormodeToPixelSize(const Colormode& colormode);

        Eule::Vector2i size;
        std::vector<std::uint8_t> pixelBuffer;
    };

}

#endif //BMPPP_BMP_H
