#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QObject>

//class FileManager : public QObject
//{
//    Q_OBJECT
//public:
//    explicit FileManager(QObject* parent = nullptr);
//    // Nhận vào "file:///..." từ QML và trả về "C:/..." cho C++
//    Q_INVOKABLE static QString toLocalPath(const QString& fileUrl);
//
//    // Kiểm tra file có thực sự tồn tại trên ổ cứng không
//    Q_INVOKABLE static bool isFileValid(const QString& localPath);
//
//    Q_INVOKABLE static bool saveAndOverwrite(const QString& tempPath, const QString& originalPath);
//};
class FileManager
{
public:
    explicit FileManager(QObject* parent = nullptr);
    // Nhận vào "file:///..." từ QML và trả về "C:/..." cho C++
    static QString toLocalPath(const QString& fileUrl);

    // Kiểm tra file có thực sự tồn tại trên ổ cứng không
    static bool isFileValid(const QString& localPath);

    static bool saveAndOverwrite(const QString& tempPath, const QString& originalPath);
};
#endif // FILEMANAGER_H