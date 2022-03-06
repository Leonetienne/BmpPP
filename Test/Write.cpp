#include <Bmp.h>
#include "Catch2.h"
#include <tuple>
#include <Eule/Math.h>

using namespace Leonetienne::BmpPP;
using namespace Leonetienne::Eule;

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

// Tests that writing an image works at all (without crashing the program)
TEST_CASE(__FILE__"/WritingDoesntCrash", "[Write]")
{
    SECTION("RGB image") {
        // Create a new RGB image
        BMP bmp(IMSIZE, Colormode::RGB);

        // Write it to a file
        bmp.Write("test_artifact.bmp");
    }

    SECTION("RGBA image") {
        // Create a new RGB image
        BMP bmp(IMSIZE, Colormode::RGBA);

        // Write it to a file
        bmp.Write("test_artifact.bmp");
    }

    return;
}

// Tests that writing a file will write the correct image data
TEST_CASE(__FILE__"/WillWriteTheCorrectData", "[Write]")
{
    SECTION("RGB image") {
        // Create a new RGB image
        BMP bmp(IMSIZE, Colormode::RGB);

        // Populate it with colors
        for (std::size_t x = 0; x < bmp.GetDimensions().x; x++)
            for (std::size_t y = 0; y < bmp.GetDimensions().y; y++) {
                const auto px = ColorGradient(Vector2i(x, y));

                bmp.SetPixel(
                        Vector2i(x, y),
                        std::get<0>(px),
                        std::get<1>(px),
                        std::get<2>(px)
                );
            }

        // Write it to a file
        bmp.Write("test_artifact_rgb_gradient.bmp");

        // Read it back in (reading function is tested independently)
        BMP readBmp("test_artifact_rgb_gradient.bmp");

        // Compare them
        REQUIRE(bmp == readBmp);
    }

    SECTION("RGBA image") {
        // Create a new RGB image
        BMP bmp(IMSIZE, Colormode::RGBA);

        // Populate it with colors
        for (std::size_t x = 0; x < bmp.GetDimensions().x; x++)
            for (std::size_t y = 0; y < bmp.GetDimensions().y; y++) {
                const auto px = ColorGradient(Vector2i(x, y));

                bmp.SetPixel(
                        Vector2i(x, y),
                        std::get<0>(px),
                        std::get<1>(px),
                        std::get<2>(px),
                        std::get<3>(px)
                );
            }

        // Write it to a file
        bmp.Write("test_artifact_rgba_gradient.bmp");

        // Read it back in (reading function is tested independently)
        BMP readBmp("test_artifact_rgba_gradient.bmp");

        // Compare them
        REQUIRE(bmp == readBmp);
    }

    return;
}
