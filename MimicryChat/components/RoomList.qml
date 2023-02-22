import QtQuick 2.0
import QtQuick.Controls 2.5

import RoomListModel 1.0

Rectangle {

    color:"#00000000"


    ListView {
        id:roomListView
        x:parent.x + 10
        y:parent.y + 10
        width:parent.width - 20
        height: parent.height
        clip: true

        model: RoomListModel

        spacing: 10

        delegate: Rectangle {
            x:(roomListView.currentIndex == index) ? (parent.x + 10) : (parent.x)
            y:index * 50

            width: (roomListView.currentIndex == index) ? parent.width - 10: parent.width
            height: 40
            radius: 10
            color: (roomListView.currentIndex == index) ? "#fff" :"#00000000"

            ImgMask {
                anchors.left: parent.left
                width:parent.height
                height:parent.height

                iRadius:10
                iSource: Image {
                    visible: false
                    source: "../src/image/" + rimg
                }
            }

            Rectangle {
                anchors.left: parent.left
                anchors.leftMargin: parent.height + 10
                width:  parent.width - parent.height - 20
                height: parent.height
                color:"#00000000"

                Text {
                    y:0
                    width: parent.width
                    height: parent.height / 2

                    text: rname
                    font.bold: true
                    font.pointSize: 13
                    color:"#75738e"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    y:      parent.height / 2
                    width:  parent.width
                    height: parent.height / 2

                    text: rid
                    font.pointSize: 10
                    color: "#aabbd4"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
            }

            MouseArea {
                anchors.fill: parent;
                //点击时切换房间
                onClicked:{
                    roomListView.currentIndex = index;
                }
            }
        }
    }

}
