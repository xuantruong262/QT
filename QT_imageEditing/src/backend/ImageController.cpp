#include "ImageController.h"
#include "ImageProcessor.h"
#include "FileManager.h"
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QDateTime>
#include <QUrl>
#include <QFile>
ImageController::ImageController(QObject* parent)
    : QObject(parent), m_uiViewUrl(""), m_originalPath("") {}

QString ImageController::uiViewUrl() const {
    return m_uiViewUrl;
}

void ImageController::openImage(const QString& fileUrl) {
    // 1. Nhờ FileManager dịch sang đường dẫn C++ thuần
    QString localPath = FileManager::toLocalPath(fileUrl);

    // 2. Kiểm tra xem file có thật không, nếu lỗi thì dừng luôn
    if (!FileManager::isFileValid(localPath)) {
        qDebug() << "Lỗi: File ảnh không hợp lệ!";
        return;
    }

    // 3. Lưu trạng thái vào 2 biến riêng biệt phục vụ 2 mục đích
    m_uiViewUrl = fileUrl;   // Cho QML
    m_originalPath = localPath; // Cho OpenCV sau này
    QFile::remove(m_tempPreviewPath);
    QFile::copy(m_originalPath, m_tempPreviewPath);
    qDebug() << "Đã nạp ảnh thành công!";
    emit uiViewUrlChanged(); // Kích hoạt UI cập nhật lại ảnh mới
}

void ImageController::rotateImage(int angle) {
    if (m_originalPath.isEmpty()) return;

    // Đọc từ file tạm hiện tại -> Xoay -> Ghi đè lại vào file tạm
    bool success;
    success = ImageProcessor::rotateImage(m_tempPreviewPath, m_tempPreviewPath, angle);
    
    if (success) {
        updateUiUrl(); // Phát tín hiệu bắt QML nạp lại ảnh tạm thời
        qDebug() << "Đã xoay ảnh xem trước " << angle << " độ (Chưa lưu vào file gốc)";
    }
}
void ImageController::imageProc(int Proc_option){
    if (m_originalPath.isEmpty()) return;

    // Đọc từ file tạm hiện tại -> Xoay -> Ghi đè lại vào file tạm
    bool success;
    success = ImageProcessor::procImage(m_tempPreviewPath, m_tempPreviewPath, Proc_option);
    //success = ImageProcessor::BlurImage(m_tempPreviewPath, m_tempPreviewPath);

    if (success) {
        updateUiUrl(); // Phát tín hiệu bắt QML nạp lại ảnh tạm thời
    }
}

void ImageController::imageReset() {
    QFile::remove(m_tempPreviewPath);
    m_tempPreviewPath = "./temp_preview.jpg";
    QFile::copy(m_originalPath,m_tempPreviewPath);
    updateUiUrl();
}










void ImageController::saveImage() {
    if (m_originalPath.isEmpty()) return;

    // Tiến hành ghi đè bản tạm vào bản gốc
    if (FileManager::saveAndOverwrite(m_tempPreviewPath, m_originalPath)) {
        qDebug() << "Thành công: Đã ghi đè chỉnh sửa vào file gốc tại:" << m_originalPath;
    }
    else {
        qDebug() << "Lỗi: Không thể lưu file!";
    }
}
void ImageController::deleteImage() {
    m_uiViewUrl = "";
    m_originalPath = "";
    emit uiViewUrlChanged();
}

void ImageController::updateUiUrl() {
    // Biến đổi đường dẫn file tạm thành định dạng URL "file:///"
    // Thêm ?t=... để phá bộ nhớ đệm cache của thẻ Image trong QML
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    m_uiViewUrl = QUrl::fromLocalFile(m_tempPreviewPath).toString() + "?t=" + QString::number(timestamp);
    emit uiViewUrlChanged();
}