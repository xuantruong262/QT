//qml/pages/EditorPage.qml
import QtQuick
import QtQuick.Controls

Window {
    id: settingsWindow
    title: "Image Tools"
    width: 280
    height: 180
    
    // Gợi ý: Dùng Qt.NonModal để vừa bấm xoay, vừa nhìn thấy ảnh thay đổi ở cửa sổ chính
    modality: Qt.NonModal 
    
    // Nền tối cho chuyên nghiệp
    color: "#252525" 

    Column {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "Rotate"
            color: "white"
            font.bold: true
            font.pointSize: 13
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            spacing: 15
            
            Button {
                text: "Left Rotation ↺"
                onClicked: {
                    // Gọi thẳng sang bộ điều khiển C++ đã làm ở bước trước
                    backendController.rotateImage(-90) 
                }
            }

            Button {
                text: "Right Rotation ↻"
                onClicked: {
                    backendController.rotateImage(90)
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