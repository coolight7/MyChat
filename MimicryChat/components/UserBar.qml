import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import Qt5Compat.GraphicalEffects

import UserInfo 1.0


Rectangle {
    id: userBar
    width: 200
    height:40
    color:  "#00000000"

    Text {
        height: 40
        anchors.right: userIconRect.left
        anchors.rightMargin: 10
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        clip: true

        text: UserInfo.userName
        font.bold: true
        font.pointSize: 12
        color: "#7b7995"
    }


    Rectangle {
        id:userIconRect
        anchors.right: parent.right
        width:  40
        height: 40
        color:  "#00000000"
        radius: 20
        border.color: "#66ccff"
        border.width: 3
        clip: true

        ImgMask {
            anchors.fill: parent
            iRadius:20
            iSource: Image {
                anchors.fill: parent
                source: "../src/image/" + UserInfo.img
                visible: false
            }
        }
    }

}
