#include <BmpHeader.h>
#include "Catch2.h"

using namespace Leonetienne::BmpPP;

// Tests that the reported header sizes are correct
TEST_CASE(__FILE__"/DoHeaderSizesMatch", "[Header]")
{
    BmpHeader header;

    SECTION("DibHeader size") {
        REQUIRE(header.dibHeader.dibHeaderSize == header.dibHeader.NBYTES);
        REQUIRE(header.dibHeader.dibHeaderSize == 40);
    }

    SECTION("FileHeader size") {
        REQUIRE(header.fileHeader.NBYTES == 14);
    }

    SECTION("RenderedHeader size") {
        const std::vector<std::uint8_t> headerBytes = header.ToBytes();

        REQUIRE(headerBytes.size() == header.fileHeader.NBYTES + header.dibHeader.NBYTES);
    }

    return;
}
