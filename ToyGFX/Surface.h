#pragma once


//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//
//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <string>
#include <memory>

class Surface
{
public:
    class Color
    {
    public:

        constexpr Color() noexcept : dword() {}

        constexpr Color(const Color& col) noexcept : dword(col.dword) {}

        constexpr Color(unsigned int dw) noexcept : dword(dw) {}

        constexpr Color(unsigned char a, unsigned char r, unsigned char g, unsigned char b) noexcept
            :
            dword((a << 24u) | (r << 16u) | (g << 8u) | b) {}

        constexpr Color(unsigned char r, unsigned char g, unsigned char b) noexcept
            :
            dword((r << 16u) | (g << 8u) | b) {}

        constexpr Color(Color col, unsigned char a) noexcept : Color((a << 24u) | col.dword) {}

        Color& operator =(Color color) noexcept
        {
            dword = color.dword;
            return *this;
        }

        constexpr unsigned char GetA() const noexcept
        {
            return dword >> 24u;
        }

        constexpr unsigned char GetR() const noexcept
        {
            return (dword >> 16u) & 0xFFu;
        }

        constexpr unsigned char GetG() const noexcept
        {
            return (dword >> 8u) & 0xFFu;
        }

        constexpr unsigned char GetB() const noexcept
        {
            return dword & 0xFFu;
        }

        void SetA(unsigned char a) noexcept
        {
            dword = (dword & 0xFFFFFFu) | (a << 24u);
        }

        void SetR(unsigned char r) noexcept
        {
            dword = (dword & 0xFF00FFFFu) | (r << 16u);
        }

        void SetG(unsigned char g) noexcept
        {
            dword = (dword & 0xFFFF00FFu) | (g << 8u);
        }

        void SetB(unsigned char b) noexcept
        {
            dword = (dword & 0xFFFFFF00u) | b;
        }

    public:
        unsigned int dword;
    };

public:
    enum FORMAT_TYPE
    {
        JPG,
        PNG,
        BMP
    };

public:
    Surface(unsigned int width, unsigned int height, unsigned int channels);
    ~Surface();
    
    static Surface FromFile(const std::string& filePath);

    void Save(const std::string& filename, FORMAT_TYPE type = BMP) const;

    void PutPixel(unsigned int x, unsigned int y, Color c) noexcept;
    Color GetPixel(unsigned int x, unsigned int y) const noexcept;

    unsigned int GetWidth() const noexcept;
    unsigned int GetHeight() const noexcept;


    const char* createWitheNoise() const noexcept;
    const char* createPinkNoise() const noexcept;

private:
    Surface(unsigned int width, unsigned int height, std::unique_ptr<Color[]> pBuffer) noexcept;

private:

    unsigned int mWidth;
    unsigned int mHeight;
    unsigned int mChannels;

    std::unique_ptr<Color[]> pBuffer;
};