#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <QObject>
#include <QString>

class ImageController : public QObject
{
    Q_OBJECT
        // QML chỉ cần đọc thuộc tính này để hiển thị ảnh lên màn hình
        Q_PROPERTY(QString uiViewUrl READ uiViewUrl NOTIFY uiViewUrlChanged)

public:
    explicit ImageController(QObject* parent = nullptr);

    Q_INVOKABLE void openImage(const QString& fileUrl);
    Q_INVOKABLE void rotateImage(int angle);
    Q_INVOKABLE void imageProc(int Proc_option);
    Q_INVOKABLE void imageReset();
    
    Q_INVOKABLE void saveImage();
    Q_INVOKABLE void deleteImage();

    QString uiViewUrl() const;

signals:
    void uiViewUrlChanged();

private:
    QString m_uiViewUrl;  // Dạng "file:///..." phục vụ QML hiển thị
    QString m_originalPath;    // Đường dẫn file gốc trên ổ cứng (C:/.../anh_goc.jpg)
    QString m_tempPreviewPath = "./temp_preview.jpg"; // Đường dẫn file tạm (C:/.../temp_preview.jpg)

    void updateUiUrl();
};

#endif // IMAGECONTROLLER_H