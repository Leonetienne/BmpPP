#include <Bmp.h>
#include <stdexcept>
#include "Catch2.h"

using namespace Leonetienne::BmpPP;
using namespace Eule;

// Tests that swapping channels works
TEST_CASE(__FILE__"/SwappingChannelsWorks", "[SwapChannels]")
{
    SECTION("R2G") {
        // Read an image
        BMP bmp("base_fuwadera.bmp");

        // Swap channels
        bmp.SwapChannels(0, 1);

        // Read reference image
        const BMP reference("base_fuwadera_channelswap_rg.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("R2B") {
        // Read an image
        BMP bmp("base_fuwadera.bmp");

        // Swap channels
        bmp.SwapChannels(0, 2);

        // Read reference image
        const BMP reference("base_fuwadera_channelswap_rb.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    SECTION("G2B") {
        // Read an image
        BMP bmp("base_fuwadera.bmp");

        // Swap channels
        bmp.SwapChannels(1, 2);

        // Read reference image
        const BMP reference("base_fuwadera_channelswap_gb.bmp");

        // Assert that they are equal
        REQUIRE(bmp == reference);
    }

    return;
}

// Tests that swapping selecting a color channel that's out of range produces a runtime error
TEST_CASE(__FILE__"/RuntimeError_on_channel_out_of_range", "[SwapChannels]")
{
    SECTION("RGB_OUT_OF_RANGE") {
        BMP bmp(Vector2i(800, 600), Colormode::RGB);

        REQUIRE_THROWS_AS(
            bmp.SwapChannels(0, 3)
            , std::runtime_error
        );
    }

    SECTION("RGBA_OK") {
        BMP bmp(Vector2i(800, 600), Colormode::RGBA);

        bmp.SwapChannels(0, 3);
    }

    SECTION("RGBA_OUT_OF_RANGE") {
        BMP bmp(Vector2i(800, 600), Colormode::RGBA);

        REQUIRE_THROWS_AS(
                bmp.SwapChannels(0, 4)
        , std::runtime_error
        );
    }
    return;
}
