#include <Bmp.h>
#include "Catch2.h"
#include <tuple>
#include <Eule/Math.h>

using namespace Leonetienne::BmpPP;
using namespace Eule;

#define IMSIZE Vector2i(800, 600)

// Tests that FillChannel works correctly
TEST_CASE(__FILE__"/WillWriteTheCorrectData", "[FillChannel]")
{
    SECTION("RGB image, fill red") {
        // Read a red reference image
        BMP reference("base_red.bmp");

        // Now create a new image
        BMP bmp(IMSIZE, Colormode::RGB);

        // Fill its red channel with 255
        bmp.FillChannel(0, 0xFF);

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }
    SECTION("RGB image, fill green") {
        // Read a green reference image
        BMP reference("base_green.bmp");

        // Now create a new image
        BMP bmp(IMSIZE, Colormode::RGB);

        // Fill its green channel with 255
        bmp.FillChannel(1, 0xFF);

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }
    SECTION("RGB image, fill blue") {
        // Read a blue reference image
        BMP reference("base_blue.bmp");

        // Now create a new image
        BMP bmp(IMSIZE, Colormode::RGB);

        // Fill its blue channel with 255
        bmp.FillChannel(2, 0xFF);

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("RGBA image, fill red") {
        // Read a red reference image
        BMP reference("basea_red.bmp");

        // Now create a new image
        BMP bmp(IMSIZE, Colormode::RGBA);

        // Fill its red channel with 255
        bmp.FillChannel(0, 0xFF);

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }
    SECTION("RGBA image, fill green") {
        // Read a green reference image
        BMP reference("basea_green.bmp");

        // Now create a new image
        BMP bmp(IMSIZE, Colormode::RGBA);

        // Fill its green channel with 255
        bmp.FillChannel(1, 0xFF);

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }
    SECTION("RGBA image, fill blue") {
        // Read a blue reference image
        BMP reference("basea_blue.bmp");

        // Now create a new image
        BMP bmp(IMSIZE, Colormode::RGBA);

        // Fill its blue channel with 255
        bmp.FillChannel(2, 0xFF);

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }
    SECTION("RGBA image, fill alpha") {
        // Read any reference image with alpha=255
        BMP reference("basea_blue.bmp");

        // Now create a new image
        BMP bmp(IMSIZE, Colormode::RGBA);

        // Fill its blue, and alpha channel with 255
        bmp.FillChannel(2, 0xFF);
        bmp.FillChannel(3, 0xFF);

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }
    return;
}
