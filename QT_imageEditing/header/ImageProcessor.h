// opencv/ImageProcessor.h
#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#define ProcOption_Blur 0
#define ProcOption_RGB2Gray 1
#define ProcOption_Canny 2

#include <QString>

class ImageProcessor
{
public:
    // Thuật toán xoay ảnh sử dụng OpenCV
    static bool rotateImage(const QString& inputPath, const QString& outputPath, int angle);
    static bool procImage(const QString& inputPath, const QString& outputPath, int Proc_option);
};

#endif // IMAGEPROCESSOR_H