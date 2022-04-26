#include <BmpPP/Bmp.h>
#include <stdexcept>
#include "Catch2.h"

using namespace Leonetienne::BmpPP;
using namespace Leonetienne::Eule;

// Tests the mirror horizontal function against reference images
TEST_CASE(__FILE__"/Mirroring produces the correct results", "[Mirroring][MirrorHorizontally]")
{
    SECTION("RGB") {
        // Read a gradient image
        BMP bmp("base_fuwadera2.bmp");

        // Mirror it
        bmp = bmp.MirrorHorizontally();

        // Read reference image
        const BMP reference("base_fuwadera2_mirror_hor.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("RGBA") {
        // Read a gradient image
        BMP bmp("basea_fuwadera2.bmp");

        // Mirror it
        bmp = bmp.MirrorHorizontally();

        // Read reference image
        const BMP reference("basea_fuwadera2_mirror_hor.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }
    return;
}
