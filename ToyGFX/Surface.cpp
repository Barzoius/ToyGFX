//#include "Surface.h"
//
//
//Surface::Surface(unsigned int width, unsigned int height, unsigned int channels)
//    :
//    mWidth(width),
//    mHeight(height),
//    mChannels(channels)
//{}
//
//Surface::Surface(unsigned int width, unsigned int height, std::unique_ptr<Color[]> pBuffer) noexcept
//    :
//    mWidth(width),
//    mHeight(height),
//    pBuffer(std::move(pBuffer))
//{}
//
//Surface Surface::FromFile(const std::string& filePath)
//{
//    int width, height, channels;
//    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
//
//    std::unique_ptr<Color[]> pBuffer = nullptr;
//    pBuffer = std::make_unique<Color[]>(width * height * channels);
//
//    for (int i = 0; i < height; i++)
//    {
//        for (int j = 0; j < width; j++)
//        {
//            int dataIndex = (i * width + j) * channels;
//            int pbufferIndex = i * width + j;
//
//            if (channels == 3) // RGB
//            {
//                pBuffer[pbufferIndex] = Color(
//                    255,                // A
//                    data[dataIndex],     // R
//                    data[dataIndex + 1], // G
//                    data[dataIndex + 2]  // B
//                );
//            }
//            else if (channels == 4) // RGBA
//            {
//                pBuffer[pbufferIndex] = Color(
//                    data[dataIndex + 3], // A
//                    data[dataIndex],     // R
//                    data[dataIndex + 1], // G
//                    data[dataIndex + 2]  // B
//                );
//            }
//        }
//    }
//
//    return Surface(width, height, std::move(pBuffer));
//}
//
//
//void Surface::Save(const std::string& filePath, FORMAT_TYPE type) const
//{
//    if (type == JPG)
//    {
//        stbi_write_jpg(filePath.c_str(), mWidth, mHeight, mChannels, pBuffer.get(), mWidth * mChannels);
//    }
//    else if (type == PNG)
//    {
//        stbi_write_png(filePath.c_str(), mWidth, mHeight, mChannels, pBuffer.get(), 100);
//    }
//    else
//    {
//        stbi_write_bmp(filePath.c_str(), mWidth, mHeight, mChannels, pBuffer.get());
//    }
//}