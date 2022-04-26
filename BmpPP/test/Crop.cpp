#include <BmpPP/Bmp.h>
#include <stdexcept>
#include "Catch2.h"

using namespace Leonetienne::BmpPP;
using namespace Leonetienne::Eule;

// Tests that cropping produces the correct result
TEST_CASE(__FILE__"/HappyPath", "[Cropping]")
{
    SECTION("RGB") {
        // Read an image
        BMP bmp("base_hachi.bmp");

        // Crop it
        bmp = bmp.Crop(
            Vector2i(95, 83),
            Vector2i(149, 239)
        );

        // Read reference image
        const BMP reference("base_hachi_cropped.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("RGBA") {
        // Read an image
        BMP bmp("basea_hachi.bmp");

        // Crop it
        bmp = bmp.Crop(
            Vector2i(95, 83),
            Vector2i(149, 239)
        );

        // Read reference image
        const BMP reference("basea_hachi_cropped.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    return;
}

// Tests that cropping with extreme points works (like, 0,0, widht, height)
TEST_CASE(__FILE__"/ExtremePoints", "[Cropping]")
{
    SECTION("Crop includes {0,0}") {
        // Read an image
        BMP bmp("base_hachi.bmp");

        // Crop it
        bmp = bmp.Crop(
            Vector2i(0, 0),
            Vector2i(252, 337)
        );

        // Read reference image
        const BMP reference("base_hachi_cropped_extreme_topleft.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("Crop includes {width, height}") {
        // Read an image
        BMP bmp("base_hachi.bmp");

        // Crop it
        bmp = bmp.Crop(
            Vector2i(96, 54),
            bmp.GetDimensions() - Vector2i(96, 54) // As far-right as we can get
        );

        // Read reference image
        const BMP reference("base_hachi_cropped_extreme_bottomright.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("Crop includes {0, 0, width, height}") {
        // Read an image
        BMP bmp("base_hachi.bmp");

        // Crop it (without taking away anything, lol)
        BMP cropped = bmp.Crop(
            Vector2i(0, 0),
            bmp.GetDimensions() // As far-right as we can get
        );

        // Assert that the cropped image remains the same (as we cropped from 0,0 to width,height)
        REQUIRE(bmp == cropped);
    }

    return;
}
