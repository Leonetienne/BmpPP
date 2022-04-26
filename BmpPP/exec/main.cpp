#include <BmpPP/Bmp.h>
#include <iostream>
#include <BmpPP/BmpHeader.h>
#include <Eule/Math.h>

using namespace Leonetienne::BmpPP;
using namespace Leonetienne::Eule;

int main() {

    // Draw gradient
    BMP bmp(Vector2i(800, 600), Colormode::RGB);

    for (std::size_t x = 0; x < bmp.GetDimensions().x; x++)
    for (std::size_t y = 0; y < bmp.GetDimensions().y; y++)
        bmp.SetPixel(Vector2i(x, y), (float)x / (float)bmp.GetDimensions().x * 255.0f);

    bmp.Write("gradient.bmp");

    return 0;
}
