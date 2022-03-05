#include <Bmp.h>
#include "Catch2.h"

using namespace Leonetienne::BmpPP;

// Tests that re-initializing images produces the correct getter values
TEST_CASE(__FILE__"/ReInitialize", "[ReInitialize]")
{
    // Create image
    BMP bmp({800, 600}, Colormode::RGBA);

    SECTION("Check that the initial values are OK") {
        REQUIRE(bmp.GetDimensions().x == 800);
        REQUIRE(bmp.GetDimensions().y == 600);
        REQUIRE(bmp.GetNumColorChannels() == 4);
        REQUIRE(bmp.GetColormode() == Colormode::RGBA);
        REQUIRE(bmp.GetPixelbufferSize() == 800*600*4);
    }

    // Now re-initialize the image
    bmp.ReInitialize({1920, 1080}, Colormode::RGB);

    SECTION("Check that getters now return the updated values") {
        REQUIRE(bmp.GetDimensions().x == 1920);
        REQUIRE(bmp.GetDimensions().y == 1080);
        REQUIRE(bmp.GetNumColorChannels() == 3);
        REQUIRE(bmp.GetColormode() == Colormode::RGB);
        REQUIRE(bmp.GetPixelbufferSize() == 1920*1080*3);
    }

    return;
}
