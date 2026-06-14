import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls
import "pages" // Bản Qt6 tự động nhận, nhưng viết thế này cho chắc chắn kết nối tới thư mục pages

ApplicationWindow {
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: "Image Editor Pro"
    color: "#1e1e1e"

    // --------------------------------------------------------
    // 1. KHAI BÁO CỬA SỔ SETTING (Mặc định ẩn)
    // --------------------------------------------------------
    EditorPage{
        id: toolWindow
        visible: false // Khi nào bấm nút trên taskbar mới hiện
    }

    ImageProc {
        id: procWindow
        visible: false // Khi nào bấm nút trên taskbar mới hiện
    }

    // --------------------------------------------------------
    // 2. BỐ CỤC GIAO DIỆN CHÍNH (Taskbar + Image)
    // --------------------------------------------------------
    Column {
        anchors.fill: parent

        // --- THANH TASKBAR ---
        Rectangle {
            id: taskbar
            width: parent.width
            height: 50
            color: "#2d2d2d"

            Row {
                //anchors.centerY: parent.centerY
                //anchors.left: parent.left
                anchors.leftMargin: 15
                spacing: 10

                Button {
                    text: "Mở Ảnh"
                    onClicked: {
                        // Tạm thời gọi cứng url để test, sau này bạn thay bằng FileDialog nhé
                        console.log("QML: Đang gửi file tới Backend: ")
                        onClicked: fileDialog.open()
                    }
                }

                Button {
                    text: "Xóa Ảnh"
                    onClicked: {
                        backendController.deleteImage()
                    }
                }

                // NÚT BẤM QUAN TRỌNG: Kích hoạt mở cửa sổ phụ
                Button {
                    text: "Công Cụ Xoay ⚙️"
                    highlighted: toolWindow.visible // Sáng lên nếu cửa sổ đang mở
                    onClicked: {
                        // Đảo trạng thái ẩn/hiện của cửa sổ SettingsPage
                        toolWindow.visible = !toolWindow.visible 
                    }
                }
                Button {
                    text: "ImagePro"
                    highlighted: procWindow.visible // Sáng lên nếu cửa sổ đang mở
                    onClicked: {
                        // Đảo trạng thái ẩn/hiện của cửa sổ SettingsPage
                        procWindow.visible = !procWindow.visible 
                    }
                }
                Button {
                    text: "Save"
                    enabled: backendController.uiViewUrl !== ""
                    onClicked: {
                        backendController.saveImage()
                    }
                }
            }
        }

        // --- KHU VỰC HIỂN THỊ ẢNH CHÍNH ---
        Item {
            width: parent.width
            height: parent.height - taskbar.height

            Image {
                id: mainImageViewer
                anchors.centerIn: parent
                width: parent.width * 0.9
                height: parent.height * 0.9
                fillMode: Image.PreserveAspectFit
                
                // Trực tiếp ăn theo data đã được FileManager làm sạch từ C++
                source: backendController.uiViewUrl
                
                // Nếu không có ảnh thì hiện chữ thông báo
                visible: backendController.uiViewUrl !== ""
            }

            Text {
                text: "Chưa có ảnh nào được chọn. Hãy bấm 'Mở Ảnh'"
                color: "#666666"
                font.pointSize: 14
                anchors.centerIn: parent
                visible: backendController.uiViewUrl === ""
            }
        }
    }
        // ===== Hộp thoại chọn file =====
    FileDialog {
        id: fileDialog
        title: qsTr("Chọn một ảnh")
        nameFilters: [
            "Image files (*.png *.jpg *.jpeg *.bmp *.gif *.webp)",
            "All files (*)"
        ]
        onAccepted: {
            console.log("QML: Đang gửi file tới Backend: " + fileDialog.selectedFile)
            backendController.openImage(fileDialog.selectedFile)
        }
    }
    // Tự động đóng cửa sổ phụ nếu người dùng tắt cửa sổ chính
    onClosing: {
        toolWindow.close()
    }
}
