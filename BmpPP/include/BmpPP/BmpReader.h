#ifndef BMPPP_BMPREADER_H
#define BMPPP_BMPREADER_H

#include <string>
#include <fstream>

namespace Leonetienne::BmpPP {

    class BMP;

    class BmpReader {
    public:
        static bool Read(BMP& image, const std::string& filename);

    private:
        // Will read sizeof(T) bytes of is into buffer
        template <typename T>
        static std::ifstream& ReadBytes(std::ifstream& is, T& buffer) {
            const std::size_t sizeofT = sizeof(T);
            buffer = 0x0;
            std::uint8_t buf;

            for (std::size_t i = 0; i < sizeofT; i++)
            {
                is.read((char*)&buf, 1);
                T bbuf = buf << (i * 8);
                buffer |= bbuf;
            }

            return is;
        }
    };

}

#endif //BMPP_BMPREADER_H
