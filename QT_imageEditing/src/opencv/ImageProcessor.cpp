// opencv/ImageProcessor.cpp
#include "ImageProcessor.h"
#include <opencv2/opencv.hpp> // Bắt buộc phải cấu hình OpenCV trong CMake/QMake
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <QDebug>
using namespace cv;
bool ImageProcessor::rotateImage(const QString& inputPath, const QString& outputPath, int angle) {
    // 1. Đọc ảnh từ đường dẫn cục bộ (OpenCV dùng chuỗi std::string)
    cv::Mat src = cv::imread(inputPath.toStdString());
    if (src.empty()) {
        qDebug() << "OpenCV Lỗi: Không thể đọc ảnh từ" << inputPath;
        return false;
    }

    cv::Mat dst;
    // 2. Chọn góc xoay dựa trên tham số truyền vào
    if (angle == 90 || angle == -270) {
        cv::rotate(src, dst, cv::ROTATE_90_CLOCKWISE);
    }
    else if (angle == -90 || angle == 270) {
        cv::rotate(src, dst, cv::ROTATE_90_COUNTERCLOCKWISE);
    }
    else if (angle == 180 || angle == -180) {
        cv::rotate(src, dst, cv::ROTATE_180);
    }
    else {
        dst = src.clone(); // Giữ nguyên nếu góc không hợp lệ
    }

    // 3. Ghi kết quả ra file đầu ra (ở đây sẽ là file tạm)
    bool success = cv::imwrite(outputPath.toStdString(), dst);
    if (!success) {
        qDebug() << "OpenCV Lỗi: Không thể ghi ảnh ra" << outputPath;
    }
    return success;
}

bool ImageProcessor::procImage(const QString& inputPath, const QString& outputPath, int Proc_option) {
    cv::Mat imgGray, imgblur, dst;
    cv::Mat src = cv::imread(inputPath.toStdString());
    if (src.empty()) {
        qDebug() << "OpenCV Lỗi: Không thể đọc ảnh từ" << inputPath;
        return false;
    }
    //cv::cvtColor(src, imgGray, COLOR_BGR2GRAY);
    if (Proc_option == ProcOption_Blur) {
        cv::GaussianBlur(src, dst, Size(3,3), 0);
    }
    else if (Proc_option == ProcOption_RGB2Gray) {
        cvtColor(src, dst, COLOR_BGR2GRAY);
    }
    else if (Proc_option == ProcOption_Canny) {
        Canny(src, dst, 35, 65);
    }

    bool success = cv::imwrite(outputPath.toStdString(), dst);
    if (!success) {
        qDebug() << "OpenCV Lỗi: Không thể ghi ảnh ra" << outputPath;
    }
    return success;
}