#include <Bmp.h>
#include "Catch2.h"
#include <tuple>
#include <Eule/Math.h>

using namespace Leonetienne::BmpPP;
using namespace Eule;

#define IMSIZE Vector2i(800, 600)

namespace {
    inline std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>
            ColorGradient(const Vector2i& pos)
    {
        std::uint8_t r, g, b, a;

        // This assumes IMSIZE.x >= IMSIZE.y

        r = ((float)pos.x / (float)IMSIZE.x) * 255.0f;
        g = (1.0f - (float)pos.x / (float)IMSIZE.x) * 255.0f;
        b = (1.0f - (float)pos.y / (float)IMSIZE.x) * 255.0f;
        a = Math::Clamp(((float)pos.y / (float)IMSIZE.x) * 2 * 255.0f, 0.0, 255.0);

        return std::make_tuple(r, g, b, a);
    }
}

// Tests that reading an image works at all, without throwing an exception or crashing the program
TEST_CASE(__FILE__"/ReadingDoesntCrash", "[Read]")
{
    SECTION("RGB image with BITMAPV5HEADER") {
        // Read RGB gradient image
        BMP bmp("base_gradient.bmp");
    }

    SECTION("RGBA image with BITMAPV5HEADER") {
        // Read RGBA gradient image
        BMP bmp("basea_gradient.bmp");
    }

    return;
}

// Tests that an image is initialized after being read
TEST_CASE(__FILE__"/InitializedAfterReading", "[Read]")
{
    // Read RGB gradient image
    BMP bmp("base_gradient.bmp");

    REQUIRE(bmp.IsInitialized());

    return;
}

// Tests that images read the correct metadata (bit depth and resolution)
TEST_CASE(__FILE__"/MetadataIsCorrect", "[Read]")
{
    // Read RGB gradient image
    SECTION("RGB image with BITMAPV5HEADER") {
        // Read RGB gradient image
        BMP bmp("base_gradient.bmp");

        REQUIRE(bmp.GetDimensions() == IMSIZE);
        REQUIRE(bmp.GetColormode() == Colormode::RGB);
    }

    SECTION("RGBA image with BITMAPV5HEADER") {
        // Read RGBA gradient image
        BMP bmp("basea_gradient.bmp");

        REQUIRE(bmp.GetDimensions() == IMSIZE);
        REQUIRE(bmp.GetColormode() == Colormode::RGBA);
    }

    return;
}

// Tests that reading an image works, by comparing the resulting pixel
// values with the algorithm that created them
TEST_CASE(__FILE__"/CompareRGB", "[Read]")
{
    // Read RGB gradient image
    BMP bmp("base_gradient.bmp");

    // Compare each pixel to the algorithm that has once created it
    for (std::size_t x = 0; x < bmp.GetDimensions().x; x++)
    for (std::size_t y = 0; y < bmp.GetDimensions().y; y++) {

        const auto expected_pixel_values = ColorGradient(Vector2i(x, y));
        const uint8_t* pxBase = bmp.GetPixel(Vector2i(x, y));
        const auto actual_pixel_values =
                std::make_tuple(
                        *(pxBase + 0),
                        *(pxBase + 1),
                        *(pxBase + 2),
                        std::get<3>(expected_pixel_values) // Since our image doesn't contain an ALPHA channel, let's copy it from the expected value
                );

        REQUIRE(actual_pixel_values == expected_pixel_values);
    }

    return;
}

// Tests that reading an image works, by comparing the resulting pixel
// values with the algorithm that created them
TEST_CASE(__FILE__"/CompareRGBA", "[Read]")
{
    // Read RGBA gradient image
    BMP bmp("basea_gradient.bmp");

    // Compare each pixel to the algorithm that has once created it
    for (std::size_t x = 0; x < bmp.GetDimensions().x; x++)
        for (std::size_t y = 0; y < bmp.GetDimensions().y; y++) {

            const auto expected_pixel_values = ColorGradient(Vector2i(x, y));
            const uint8_t* pxBase = bmp.GetPixel(Vector2i(x, y));
            const auto actual_pixel_values =
                    std::make_tuple(
                            *(pxBase + 0),
                            *(pxBase + 1),
                            *(pxBase + 2),
                            *(pxBase + 3)
                    );

            REQUIRE(actual_pixel_values == expected_pixel_values);
        }

    return;
}
#undef IMSIZE
