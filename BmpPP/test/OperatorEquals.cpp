#include <BmpPP/Bmp.h>
#include <stdexcept>
#include "Catch2.h"

using namespace Leonetienne::BmpPP;
using namespace Leonetienne::Eule;

// Don't have to test operator not equal, because it just returns the opposite of this

// Tests that two RGB images containing almost every possible color are equal, after being copied
TEST_CASE(__FILE__"/CopiedImagesAreEqual", "[OperatorEqual]")
{
    // Read a gradient image
    BMP bmp_a("base_gradient.bmp");

    // Copy it
    BMP bmp_b = bmp_a;

    // Assert that they are equal
    REQUIRE(bmp_a == bmp_b);
    return;
}

// Tests that changing a single pixel channel results in them not being equal anymore
TEST_CASE(__FILE__"/OneDifferingValueMakesUnequal", "[OperatorEqual]")
{
    // Read a gradient image
    BMP bmp_a("base_gradient.bmp");

    // Copy it
    BMP bmp_b = bmp_a;

    // Bop it
    *(bmp_a.GetPixel(bmp_a.GetDimensions() / 2) + 1) = 69;

    // Assert that they are equal
    REQUIRE_FALSE(bmp_a == bmp_b);
    return;
}

// Tests that two images with the exact same pixelbuffer, but differing metadata are not equal
TEST_CASE(__FILE__"/SamePixelbufferButDifferentMetadataUnequal", "[OperatorEqual]")
{
    // Create image a
    BMP bmp_a(Vector2i(800, 600), Colormode::RGB); // 1440000 values of 0

    // Create image b
    BMP bmp_b(Vector2i(600, 600), Colormode::RGBA); // Also 1440000 values of 0
    bmp_b.FillChannel(3, 0); // Make sure the alpha channel actually is zeroed

    // They only differ by their metadata. Not by pixel data. Make sure they are not euqal.
    REQUIRE_FALSE(bmp_a == bmp_b);

    return;
}
