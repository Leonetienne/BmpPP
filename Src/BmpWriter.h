#ifndef TEST_BMPWRITER_H
#define TEST_BMPWRITER_H

#include <string>

namespace Leonetienne::BmpPP {

    class BMP;

    class BmpWriter {
    public:
        static bool Write(const BMP& image, const std::string& filename);
    };

}

#endif //TEST_BMPWRITER_H
