//qml/pages/ImageProcessing.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: imgProcWindow
    title: "Image Procesing"
    width: 280
    height: 180
    
    // Gợi ý: Dùng Qt.NonModal để vừa bấm xoay, vừa nhìn thấy ảnh thay đổi ở cửa sổ chính
    modality: Qt.NonModal 
    
    // Nền tối cho chuyên nghiệp
    color: "#252525" 

    Column {
        anchors.leftMargin: 1
        //anchors.centerIn: parent
        spacing: 5

        //Text {
        //    text: "Xử lý ảnh"
        //    color: "white"
        //    font.bold: true
        //    font.pointSize: 13
        //    anchors.horizontalCenter: parent.horizontalCenter
        //}

        Row {
            spacing: 2 
            Button {
                text: "Blur"
                onClicked: {
                    // Gọi thẳng sang bộ điều khiển C++ đã làm ở bước trước
                    backendController.imageProc(0)
                }
            }

            Button {
                text: "ConvGray"
                onClicked: {
                    backendController.imageProc(1)
                }
            }

            Button {
                text: "Canny"
                onClicked: {
                    backendController.imageProc(2)
                }
            }
        }
        Row{
            //anchors.centerX: parent.centerX
            Button {
                anchors.leftMargin: 40
                text: "Reset"
                width: 100
                height: 30
                onClicked: {
                    backendController.imageReset()
                }
            }
        }
        
        //Text {
        //    text: "Trạng thái: Đang kết nối OpenCV..."
        //    color: "#888888"
        //    font.pointSize: 9
        //    anchors.horizontalCenter: parent.horizontalCenter
        //}
    }
}