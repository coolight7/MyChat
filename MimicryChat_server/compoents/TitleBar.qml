import QtQuick 2.0
import QtQuick.Window 2.3
import QtQuick.Controls 2.5

Rectangle {
    id:titleBar
    width: parent.width
    height: 40
    color:"#00000000"
    anchors.left: parent.left

    Text {
        anchors.fill: parent
        text: "MinicryChat-server"
        font.pointSize: 15
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        clip: true
        color:"#787790"
    }

    Button {
        id:hideBtn
        anchors.right: closeBtn.left
        anchors.rightMargin: 10
        width: 40
        height: 40
        background: Rectangle {
            anchors.fill: parent
            color:"#00000000"

            Text {
                anchors.fill: parent
                text: "—"
                font.pointSize: 13
                font.bold: true
                color:"#787790"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        onClicked: {

        }
    }

    Button {
        id:closeBtn
        anchors.right: parent.right
        width:  40
        height: 40
        background: Rectangle {
            anchors.fill: parent
            color:"#00000000"
            Text {
                anchors.fill: parent
                text: "X"
                color:"#787790"
                font.pointSize: 15
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        onClicked: {
            Qt.quit();
        }
    }

}
