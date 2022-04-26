#include "BmpPP/Bmp.h"
#include <stdexcept>
#include <algorithm>
#include "BmpPP/BmpWriter.h"
#include "BmpPP/BmpReader.h"

#define CHECK_IF_INITIALIZED if (!isInitialized) throw std::runtime_error("Image not initialized!");

namespace Leonetienne::BmpPP {

    using namespace Eule;

    BMP::BMP() {
        // Do nothing
        return;
    }

    BMP::BMP(const std::string &filename) {
        if(!Read(filename))
            throw std::runtime_error("Unable to read bmp image!");

        return;
    }

    BMP::BMP(const Vector2i &size, const Colormode& colormode)
        :
        size { size },
        colormode { colormode }
    {
        ReInitialize(size, colormode);

        return;
    }

    void BMP::ReInitialize(const Vector2i &size) {
        isInitialized = true;

        // Carry over new attributes
        this->size = size;

        // Re-initialize the pixelbuffer
        pixelBuffer.clear();
        pixelBuffer.resize(size.x * size.y * GetNumChannels());

        // If we're initializing with an alpha channel, set it to 255
        if (colormode == Colormode::RGBA)
            FillChannel(3, 255);

        return;
    }

    void BMP::ReInitialize(const Vector2i &size, const Colormode &colormode) {
        isInitialized = true;

        // Carry over new attributes
        this->size = size;
        this->colormode = colormode;

        // Re-initialize the pixelbuffer
        pixelBuffer.clear();
        pixelBuffer.resize(size.x * size.y * GetNumChannels());

        // If we're initializing with an alpha channel, set it to 255
        if (colormode == Colormode::RGBA)
            FillChannel(3, 255);

        return;
    }

    bool BMP::Write(const std::string &filename) const {
        CHECK_IF_INITIALIZED

        return BmpWriter::Write(*this, filename);
    }

    bool BMP::Read(const std::string &filename) {
        return BmpReader::Read(*this, filename);
    }

    std::uint8_t *BMP::GetPixel(const Vector2i &position) {
        CHECK_IF_INITIALIZED

        const std::size_t pixelIndex =
                (position.y * size.x + position.x) * GetNumChannels();

        if (pixelIndex >= pixelBuffer.size())
            throw std::runtime_error("Pixel index out of range!");

        return pixelBuffer.data() + pixelIndex;
    }

    const std::uint8_t *BMP::GetPixel(const Vector2i &position) const {
        CHECK_IF_INITIALIZED

        const std::size_t pixelIndex =
                (position.y * size.x + position.x) * GetNumChannels();

        if (pixelIndex >= pixelBuffer.size())
            throw std::runtime_error("Pixel index out of range!");

        return pixelBuffer.data() + pixelIndex;
    }

    void BMP::SetPixel(const Vector2i &position,
                       const std::uint8_t v)
    {
        CHECK_IF_INITIALIZED

        std::uint8_t* pixel = GetPixel(position);

        pixel[0] = v;
        pixel[1] = v;
        pixel[2] = v;

        return;
    }

    void BMP::SetPixel(const Vector2i &position,
                       const std::uint8_t r,
                       const std::uint8_t g,
                       const std::uint8_t b)
    {
        CHECK_IF_INITIALIZED

        std::uint8_t* pixel = GetPixel(position);

        pixel[0] = r;
        pixel[1] = g;
        pixel[2] = b;

        return;
    }

    void BMP::SetPixel(const Vector2i &position,
                  const std::uint8_t r,
                  const std::uint8_t g,
                  const std::uint8_t b,
                  const std::uint8_t a)
    {
        CHECK_IF_INITIALIZED

        std::uint8_t* pixel = GetPixel(position);

        switch (colormode) {
            case Colormode::RGBA:
                pixel[0] = r;
                pixel[1] = g;
                pixel[2] = b;
                pixel[3] = a;
                break;

            case Colormode::RGB:
                pixel[0] = r;
                pixel[1] = g;
                pixel[2] = b;
                break;
        }

        return;
    }

    std::uint8_t *BMP::data() {
        CHECK_IF_INITIALIZED

        return pixelBuffer.data();
    }

    const std::uint8_t *BMP::data() const {
        CHECK_IF_INITIALIZED

        return pixelBuffer.data();
    }

    const Vector2i &BMP::GetDimensions() const {
        CHECK_IF_INITIALIZED

        return size;
    }

    const Colormode &BMP::GetColormode() const {
        CHECK_IF_INITIALIZED

        return colormode;
    }

    std::size_t BMP::GetNumChannels() const {
        CHECK_IF_INITIALIZED

        switch (colormode) {
            case Colormode::RGB:
                return 3;

            case Colormode::RGBA:
                return 4;
        }

        // Unreachable
        return -1;
    }

    std::size_t BMP::GetPixelbufferSize() const {
        CHECK_IF_INITIALIZED

        return pixelBuffer.size();
    }

    bool BMP::IsInitialized() const {
        return isInitialized;
    }

    const std::vector<std::uint8_t> &BMP::GetPixelbuffer() const {
        CHECK_IF_INITIALIZED
        return pixelBuffer;
    }

    bool BMP::operator==(const BMP &other) const {
        // Check initialization status
        if (isInitialized != other.isInitialized)
            return false;

        // Check metadata
        if (colormode != other.colormode)
            return false;

        if (size != other.size)
            return false;

        // Check pixel values
        if (pixelBuffer != other.pixelBuffer)
            return false;

        return true;
    }

    bool BMP::operator!=(const BMP &other) const {
        return !operator==(other);
    }

    void BMP::FillChannel(const size_t &channel, const std::uint8_t value) {
        CHECK_IF_INITIALIZED

        if (GetNumChannels() <= channel)
            throw std::runtime_error("Channel index out of range!");

        const std::size_t numChannels = GetNumChannels();

        for (std::size_t i = 0; i < pixelBuffer.size(); i += numChannels)
            pixelBuffer[i + channel] = value;

        return;
    }

    void BMP::SwapChannels(const size_t &channel1, const size_t &channel2) {
        CHECK_IF_INITIALIZED

        if ((GetNumChannels() <= channel1) || (GetNumChannels() <= channel2))
            throw std::runtime_error("Channel index out of range!");

        const std::size_t numChannels = GetNumChannels();

        for (std::size_t i = 0; i < pixelBuffer.size(); i += numChannels)
            std::swap(pixelBuffer[i + channel1], pixelBuffer[i + channel2]);

        return;
    }

    BMP BMP::MirrorHorizontally() const {
        CHECK_IF_INITIALIZED

        // Create a new image matching this's metadata
        BMP bmp(size, colormode);

        // Now copy over the pixels, mirroring it horizontally
        const std::size_t numChannels = GetNumChannels();
        for (std::size_t y = 0; y < size.y; y++) {
            const std::size_t rowIndex = y * size.x * numChannels;

            for (std::size_t x = 0; x < size.x; x++) {
                const std::size_t pixelIndex = rowIndex + x * numChannels;
                const std::size_t flippedPixelIndex = rowIndex + (size.x - 1 - x) * numChannels;

                // Copy over the whole pixel
                std::copy(
                  pixelBuffer.cbegin() + flippedPixelIndex,
                  pixelBuffer.cbegin() + flippedPixelIndex + numChannels,
                  bmp.pixelBuffer.begin() + pixelIndex
                );
            }

        }

        // return it
        return bmp;
    }

    BMP BMP::MirrorVertically() const {
        CHECK_IF_INITIALIZED

        // Create a new image matching this's metadata
        BMP bmp(size, colormode);

        const std::size_t numChannels = GetNumChannels();
        const std::size_t rowLength = size.x * numChannels;

        // Now iterate over all rows, and copy them over, mirroring it vertically
        for (std::size_t y = 0; y < size.y; y++) {
            const std::size_t rowIndex = y * rowLength;
            const std::size_t flippedRowIndex = (size.y - 1 - y) * rowLength;

            // Copy over the whole row
            std::copy(
                pixelBuffer.cbegin() + flippedRowIndex,
                pixelBuffer.cbegin() + flippedRowIndex + rowLength,
                bmp.pixelBuffer.begin() + rowIndex
            );

        }

        // return it
        return bmp;
    }

    BMP BMP::Rotate90degClockwise() const {
        CHECK_IF_INITIALIZED

        // Create a new image matching this ones metadata, but with width and height flipped
        BMP bmp(Vector2i(size.y, size.x), colormode);

        // Now copy over the pixels, rotating it by 90 deg
        const std::size_t numChannels = GetNumChannels();
        for (std::size_t y = 0; y < size.y; y++) {
            for (std::size_t x = 0; x < size.x; x++) {
                const std::size_t pixelIndex = (y * size.x + x) * numChannels;
                const std::size_t rotatedPixelIndex = (x * size.y + (size.y - 1 - y)) * numChannels;

                // Copy over the whole pixel
                std::copy(
                    pixelBuffer.cbegin() + pixelIndex,
                    pixelBuffer.cbegin() + pixelIndex + numChannels,
                    bmp.pixelBuffer.begin() + rotatedPixelIndex
                );
            }
        }

        // return it
        return bmp;
    }

    BMP BMP::Rotate90degCounterclockwise() const {
        CHECK_IF_INITIALIZED

        // Create a new image matching this ones metadata, but with width and height flipped
        BMP bmp(Vector2i(size.y, size.x), colormode);

        // Now copy over the pixels, rotating it by -90 deg
        const std::size_t numChannels = GetNumChannels();
        for (std::size_t y = 0; y < size.y; y++) {
            for (std::size_t x = 0; x < size.x; x++) {
                const std::size_t pixelIndex = (y * size.x + x) * numChannels;
                const std::size_t rotatedPixelIndex = ((size.x - 1 - x) * size.y + y) * numChannels;

                // Copy over the whole pixel
                std::copy(
                    pixelBuffer.cbegin() + pixelIndex,
                    pixelBuffer.cbegin() + pixelIndex + numChannels,
                    bmp.pixelBuffer.begin() + rotatedPixelIndex
                );
            }
        }

        // return it
        return bmp;
    }

    BMP BMP::Rotate180deg() const {
        CHECK_IF_INITIALIZED

        // Basically, what we're doing here, is mirroring
        // the image horizontally and vertically at the same time

        // Create a new image matching this's metadata
        BMP bmp(size, colormode);

        // Now copy over the pixels, mirroring it horizontally and vertically
        const std::size_t numChannels = GetNumChannels();
        const std::size_t rowLength = size.x * numChannels;

        for (std::size_t y = 0; y < size.y; y++) {
            const std::size_t rowIndex = y * rowLength;
            const std::size_t flippedRowIndex = (size.y - 1 - y) * rowLength;

            for (std::size_t x = 0; x < size.x; x++) {
                const std::size_t pixelIndex = rowIndex + x * numChannels;
                const std::size_t rotatedPixelIndex = flippedRowIndex + (size.x - 1 - x) * numChannels;

                // Copy over the whole pixel
                std::copy(
                        pixelBuffer.cbegin() + pixelIndex,
                        pixelBuffer.cbegin() + pixelIndex + numChannels,
                        bmp.pixelBuffer.begin() + rotatedPixelIndex
                );
            }

        }

        // return it
        return bmp;
    }

    void BMP::ConvertColormode(const Colormode &colormode) {
        CHECK_IF_INITIALIZED

        // Do we already have the target color mode?
        if (this->colormode == colormode)
            return;

        // So, we actually have to do something. Darn it.
        // Move the old pixel buffer into a a.. well.. buffer. We're gonna need it
        const std::vector<std::uint8_t> oldPixelBuffer = std::move(pixelBuffer);

        // Re-initialize our image with our new color mode
        ReInitialize(size, colormode);

        // What should we convert then?
        switch (colormode) { // this is the PARAMETER!
            // Convert RGBA to RGB.
            // Just drop the alpha channel.
            case Colormode::RGB: {
                // Jump through the old pixel buffer, four bytes at a time
                for (std::size_t i = 0; i < oldPixelBuffer.size(); i += 4) {
                    // Per jump, copy three bytes into the new one. These are r,g,b.
                    std::copy(
                        oldPixelBuffer.cbegin() + i,
                        oldPixelBuffer.cbegin() + i + 3,
                        pixelBuffer.begin() + i - (i/4) // Subtract one byte per pixel, because the new pixelBuffer is RGB, not RGBA.
                    );
                }

                // Done.
            }
            return;

            // Convert RGB to RGBA.
            // Just fill the new alpha channel with 0xFF.
            case Colormode::RGBA: {
                // Jump through the old pixel buffer, three bytes at a time
                for (std::size_t i = 0; i < oldPixelBuffer.size(); i += 3) {
                    // Per jump, copy these three bytes into the new one. These are r,g,b.
                    std::copy(
                            oldPixelBuffer.cbegin() + i,
                            oldPixelBuffer.cbegin() + i + 3,
                            pixelBuffer.begin() + i + (i/3) // Add one byte per pixel, because the new pixelBuffer is RGBA, not RGB.
                    );
                }

                // The alpha channel should already be set to 0xFF, by ReInitialize().

                // Done.
            }
            break;
        }

        return;
    }

    BMP BMP::Crop(const Vector2i &topleft, const Vector2i &cropSize) const {
        CHECK_IF_INITIALIZED

        // Check that the cropping rect is within our pixel coordinates
        if (
            (topleft.x < 0) || (topleft.y < 0) ||
            (topleft.x + cropSize.x > size.x) || (topleft.y + cropSize.y > size.y)
        )
            throw std::runtime_error("Rect coordinates are not contained inside image!");

        // Check that the area of the cropping rect is > 0
        if (cropSize.x * cropSize.y == 0)
            throw std::runtime_error("Cropping area is 0!");

        ///////////////////
        // Enough checks...

        // Create a new image of the rects size, and our color mode
        BMP bmp(cropSize, colormode);

        // Now copy over our pixel data
        const std::size_t numChannels = GetNumChannels();
        const std::size_t sourceRowLength = size.x * numChannels;
        const std::size_t targetRowLength = bmp.GetDimensions().x * numChannels;

        for (std::size_t y = topleft.y; y < topleft.y + cropSize.y; y++) {
            const std::size_t sourceRowIndex = y * sourceRowLength;
            const std::size_t targetRowIndex = (y - topleft.y) * targetRowLength;

            // Now just copy over this entire row(segment)
            std::copy(
                pixelBuffer.cbegin() + sourceRowIndex + topleft.x * numChannels,
                pixelBuffer.cbegin() + sourceRowIndex + (topleft.x * numChannels) + targetRowLength,
                bmp.pixelBuffer.begin() + targetRowIndex
            );
        }

        // Done.
        return bmp;
    }
}

#undef CHECK_IF_INITIALIZED
