#include <BmpPP/Bmp.h>
#include <stdexcept>
#include "Catch2.h"

using namespace Leonetienne::BmpPP;
using namespace Leonetienne::Eule;

// Tests converting between color modes works
TEST_CASE(__FILE__"/Converting_between_color_modes_works", "[Conversion]")
{
    SECTION("RGB to RGB") {
        // Read an RGB image
        BMP bmp("base_kyokucho.bmp");

        // Convert it to RGB
        bmp.ConvertColormode(Colormode::RGB);

        // Read reference image
        const BMP reference("base_kyokucho.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("RGB to RGBA") {
        // Read an RGB image
        BMP bmp("base_kyokucho.bmp");

        // Convert it to RGBA
        bmp.ConvertColormode(Colormode::RGBA);

        // Read reference image
        const BMP reference("basea_kyokucho.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("RGBA to RGB") {
        // Read an RGBA image
        BMP bmp("basea_kyokucho.bmp");

        // Convert it to RGB
        bmp.ConvertColormode(Colormode::RGB);

        // Read reference image
        const BMP reference("base_kyokucho.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("RGBA to RGBA") {
        // Read an RGBA image
        BMP bmp("basea_kyokucho.bmp");

        // Convert it to RGBA
        bmp.ConvertColormode(Colormode::RGBA);

        // Read reference image
        const BMP reference("basea_kyokucho.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    return;
}
