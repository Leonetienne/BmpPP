#include "BMP.h"
#include <iostream>

namespace Leonetienne::BmpPP {

    BMP::BMP(const Eule::Vector2i &size, const Colormode& colormode)
        :
        size { size }
    {

        pixelBuffer.clear();
        pixelBuffer.resize(size.x * size.y * ColormodeToPixelSize(colormode));

        return;
    }

    int BMP::ColormodeToPixelSize(const Colormode &colormode) {

        switch (colormode) {
            case Colormode::RGB:
                return 3;
            case Colormode::RGBA:
                return 4;

            // Unreachable
        }
    }

}
