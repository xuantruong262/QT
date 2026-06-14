#include "FileManager.h"
#include <QUrl>
#include <QFileInfo>

//FileManager::FileManager(QObject* parent) : QObject(parent) {
//    // Constructor trống
//}

QString FileManager::toLocalPath(const QString& fileUrl) {
    return QUrl(fileUrl).toLocalFile();
}

bool FileManager::isFileValid(const QString& localPath) {
    QFileInfo checkFile(localPath);
    return (checkFile.exists() && checkFile.isFile());
}

bool FileManager::saveAndOverwrite(const QString& tempPath, const QString& originalPath) {
    if (!QFile::exists(tempPath)) return false;

    // Nếu file gốc đã tồn tại, phải xóa đi thì mới ghi đè file mới vào được
    if (QFile::exists(originalPath)) {
        if (!QFile::remove(originalPath)) {
            qDebug() << "FileManager Lỗi: Không thể xóa file gốc để chuẩn bị ghi đè.";
            return false;
        }
    }

    // Copy file tạm thành file gốc
    return QFile::copy(tempPath, originalPath);
}