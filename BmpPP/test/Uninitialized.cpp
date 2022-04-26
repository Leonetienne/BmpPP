#include <BmpPP/Bmp.h>
#include <stdexcept>
#include "Catch2.h"

using namespace Leonetienne::BmpPP;
using namespace Leonetienne::Eule;

// Tests that get information or modifying on an uninitialized image results in a runtime error
TEST_CASE(__FILE__"/RuntimeErrorOnUninitialized", "[Uninitialized]")
{
    // Create uninitialized image
    BMP bmp;

    REQUIRE_THROWS_AS(
        bmp.GetPixel({50, 60})
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.SetPixel({50, 60}, 1,2,3,4)
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.data()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.GetDimensions()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.GetColormode()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.GetNumChannels()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.GetPixelbufferSize()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.GetPixelbuffer()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.MirrorHorizontally()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.MirrorVertically()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.MirrorVertically()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.SwapChannels(0, 1)
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.FillChannel(0, 0xFF)
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.Write("foo.bmp")
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.Rotate180deg()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.Rotate90degClockwise()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.Rotate90degCounterclockwise()
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.Crop({0,0}, {5,5})
        , std::runtime_error
    );

    REQUIRE_THROWS_AS(
        bmp.ConvertColormode(Colormode::RGB)
        , std::runtime_error
    );
    return;
}

// Tests that an uninitialized image reports to be uninitialized
TEST_CASE(__FILE__"/UninitializedImageIsUninitialized", "[Uninitialized]")
{
    BMP bmp;
    REQUIRE_FALSE(bmp.IsInitialized());

    return;
}

// Tests that an image constructed via dimensions is initialized
TEST_CASE(__FILE__"/ConstructedByDimensionsIsInitialized", "[Uninitialized]")
{
    BMP bmp(Vector2i(800, 600));
    REQUIRE(bmp.IsInitialized());

    return;
}
