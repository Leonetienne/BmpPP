#include "BMP.h"
#include <stdexcept>
#include "BmpWriter.h"
#include "BmpReader.h"

#define CHECK_IF_INITIALIZED if (!isInitialized) throw std::runtime_error("Image not initialized!");

namespace Leonetienne::BmpPP {

    BMP::BMP() {
        // Do nothing
        return;
    }


    BMP::BMP(const std::string &filename) {
        if(!Read(filename))
            throw std::runtime_error("Unable to read bmp image!");

        return;
    }

    BMP::BMP(const Eule::Vector2i &size, const Colormode& colormode)
        :
        size { size },
        colormode { colormode }
    {
        ReInitialize(size, colormode);

        return;
    }

    void BMP::ReInitialize(const Eule::Vector2i &size) {
        isInitialized = true;

        // Carry over new attributes
        this->size = size;

        // Re-initialize the pixelbuffer
        pixelBuffer.clear();
        pixelBuffer.resize(size.x * size.y * GetNumColorChannels());

        return;
    }

    void BMP::ReInitialize(const Eule::Vector2i &size, const Colormode &colormode) {
        isInitialized = true;

        // Carry over new attributes
        this->size = size;
        this->colormode = colormode;

        // Re-initialize the pixelbuffer
        pixelBuffer.clear();
        pixelBuffer.resize(size.x * size.y * GetNumColorChannels());

        return;
    }

    bool BMP::Write(const std::string &filename) const {
        CHECK_IF_INITIALIZED

        return BmpWriter::Write(*this, filename);
    }

    bool BMP::Read(const std::string &filename) {
        return BmpReader::Read(*this, filename);
    }

    std::uint8_t *BMP::GetPixel(const Eule::Vector2i &position) {
        CHECK_IF_INITIALIZED

        const std::size_t pixelIndex =
                (position.y * size.x + position.x) * GetNumColorChannels();

        if (pixelIndex >= pixelBuffer.size())
            throw std::runtime_error("Pixel index out of range!");

        return pixelBuffer.data() + pixelIndex;
    }

    const std::uint8_t *BMP::GetPixel(const Eule::Vector2i &position) const {
        CHECK_IF_INITIALIZED

        const std::size_t pixelIndex =
                (position.y * size.x + position.x) * GetNumColorChannels();

        if (pixelIndex >= pixelBuffer.size())
            throw std::runtime_error("Pixel index out of range!");

        return pixelBuffer.data() + pixelIndex;
    }

    void BMP::SetPixel(const Eule::Vector2i &position,
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

    const Eule::Vector2i &BMP::GetDimensions() const {
        CHECK_IF_INITIALIZED

        return size;
    }

    const Colormode &BMP::GetColormode() const {
        CHECK_IF_INITIALIZED

        return colormode;
    }

    std::size_t BMP::GetNumColorChannels() const {
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

}

#undef CHECK_IF_INITIALIZED
