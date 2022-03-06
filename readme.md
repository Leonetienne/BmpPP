# BmpPP
A simple, easy to use BMP image interface for C++!

Disclaimer!!:
> This is in no way, shape or form complete or compatible with every possible bmp!
> It does exactly what I need it to do, and that is to convert most bmp images to pixel buffers, convert between rgb/rgba/bw pixel buffers and write it all back to a bmp image.
> I am just publishing this in case someone wants to do said things and does not care about incompatibilities with some bmps.
 
## Basic Usage
*Assuming:
```c++
using namespace Leonetienne::BmpPP;
using namespace Eule;
```

##### Read image
```c++
BMP bmp("cute.bmp");

// or
BMP bmp;
bmp.Read("cute.bmp");
```

##### Write image
```c++
bmp.Write("cute.bmp");
```

##### Create a new image
```c++
// RGBA image
BMP bmp(Vector2i(800, 600));

// RGBA image
BMP bmp(Vector2i(800, 600), Colormode::RGBA);

// RGB image
BMP bmp(Vector2i(800, 600), Colormode::RGB);
```

##### Edit pixel data
```c++
// Set pixel grayscale value
bmp.SetPixel(Vector2i(60, 50), 128);

// Set pixel rgb value
bmp.SetPixel(Vector2i(60, 50), 255, 128, 128);

// Set pixel rgba value
bmp.SetPixel(Vector2i(60, 50), 255, 128, 128, 64);
```

##### Get pixel data
```c++
// Assuming image is RGBA
std::uint8_t* pixel = bmp.GetPixel(Vector2i(60, 50));

std::uint8_t* r = pixel[0];
std::uint8_t* g = pixel[1];
std::uint8_t* b = pixel[2];
std::uint8_t* a = pixel[3];
```

##### Convert between RGB and RGBA
```c++
// This is RGBA
BMP bmp(Vector2i(800, 600), Colormode::RGBA);

// Now it is RGB
bmp.ConvertTo(Colormode::RGB);

// And vica versa...
```

##### Mirror images
```c++
// Mirror horizontally
BMP mirroredImage_hor = image.MirrorHorizontally();

// Mirror vertically
BMP mirroredImage_ver = image.MirrorVertically();
```

##### Rotate images
```c++
// Rotate by 90 degrees, clockwise
BMP rotatedImage = image.Rotate90degClockwise();

// Rotate by 90 degrees, counterclockwise
BMP rotatedImage = image.Rotate90degCounterclockwise();

// Rotate by 180 degrees
BMP rotatedImage = image.Rotate180deg();
```

##### Crop images
```c++
// Extract the region topleft={25, 60}, size={150, 200}
BMP cropped = bmp.Crop(Vector2i(25, 60), Vector2i(150, 200));
```

##### Fill channels
```c++
// Want to set the entire ALPHA channel to 255?
bmp.FillChannel(3, 255);

// Obviously: red->0, green->1, blue->2, alpha->3
```

##### Swapping channels
```c++
// Convert BGR to RGB, by swapping the red and blue channels.
bmp.SwapChannels(0, 2);
```

##### Feed in existing pixel buffer
```c++
// OK, this is a bit more complex, but here's how to do it

// This is assumed to be an RGBA pixel buffer, formatted like:
// RGBARGBARGBARGBARGBARGBARGBA, with pixels in the same row lying next to each other in memory.
std::vector<std::uint8_t> yourPixelbuffer;

// Create a BMP instance with your resolution, and color mode
BMP bmp(Vector2i(img_height, img_width), Colormode::RGBA);

// Quick safety check, that the pixel buffer sizes do indeed match
if (yourPixelbuffer.size() != bmp.GetPixelbufferSize())
    throw "Something is definitely wrong!!!";

// All good. Let's copy the bytes over
std::copy(
    yourPixelbuffer.cbegin(),
    yourPixelbuffer.cend(),
    bmp.data()
);

// Done.
```

# LICENSE
```
BSD 2-Clause License

Copyright (c) 2022, Leon Etienne
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```

