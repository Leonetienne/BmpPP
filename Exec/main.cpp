#include <BMP.h>
#include <iostream>
#include <BmpHeader.h>
#include <Eule/Math.h>

using namespace Leonetienne::BmpPP;
using namespace Eule;

int main() {

/*

    BMP bmp({800, 600}, Colormode::RGB);

    for (int x = 0; x < 800; x++)
    for (int y = 0; y < 600; y++) {

        bmp.SetPixel({x, y},
            (std::uint8_t)(       ((double)x / 800.0) * 255.0),
            (std::uint8_t)((1.0 - ((double)x / 800.0)) * 255.0),
            (std::uint8_t)((1.0 - ((double)y / 800.0)) * 255.0),
            255
        );
    }

    bmp.Write("write.bmp");

*/
    BMP bmp("basea_hachi.bmp");

    BMP cropped = bmp.Crop(Vector2i(95, 83), Vector2i(95 + 149, 83 + 239));

    if(!cropped.Write("basea_hachi_cropped.bmp"))
        std::cerr << "What the hell" << std::endl;

    /*

    BMP bmp;

    if (!bmp.Read("test.bmp"))
        std::cerr << "Failed to read" << std::endl;

    std::cout << (bmp.GetColormode() == Colormode::RGB) << std::endl;

    if (!bmp.Write("testwrite.bmp"))
       std::cerr << "What the hell" << std::endl;

*/

    return 0;
}
