#include <Bmp.h>
#include <stdexcept>
#include "Catch2.h"

using namespace Leonetienne::BmpPP;
using namespace Eule;

// Tests that rotating works
TEST_CASE(__FILE__"/Mirroring_produces_the_correct_results", "[Rotate]")
{
    SECTION("90deg clockwise") {
        // Read an image
        BMP bmp("base_mateya.bmp");

        // Rotate it
        bmp = bmp.Rotate90degClockwise();

        // Read reference image
        const BMP reference("base_mateya_rot_90deg.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("90deg counterclockwise") {
        // Read an image
        BMP bmp("base_mateya.bmp");

        // Rotate it
        bmp = bmp.Rotate90degCounterclockwise();

        // Read reference image
        const BMP reference("base_mateya_rot_270deg.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("180deg") {
        // Read an image
        BMP bmp("base_mateya.bmp");

        // Rotate it
        bmp = bmp.Rotate180deg();

        // Read reference image
        const BMP reference("base_mateya_rot_180deg.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    return;
}
