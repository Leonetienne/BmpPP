#include <BMP.h>
#include <iostream>
#include <BmpHeader.h>

using namespace Leonetienne::BmpPP;

int main() {


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
