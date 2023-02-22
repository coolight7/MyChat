import QtQuick 2.0
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

import NowChatListModel 1.0
import UserInfo 1.0

Rectangle {
    color: "#00000000"
    radius: 20

    property real msg_TYPE_TEXT : 10001;        //聊天信息类型：普通文本
    property real msg_TYPE_TIP  : 10010;         //聊天信息类型，提示信息

    function scrollToBottom() {
        list.positionViewAtEnd();
    }

    ListView {
        id:list
        y:parent.y + 10

        width:parent.width
        height: parent.height - 20
        clip: true
        model:NowChatListModel

        spacing: 10

        add: Transition {
            NumberAnimation { properties: "y"; from: 100; duration: 100 }
        }

        Component.onCompleted: {
            positionViewAtEnd();
        }

        delegate: Rectangle {

            anchors.left: parent.left
            anchors.leftMargin: 10
            width:  parent.width - 20
            color:"#00000000"

            visible: (cstate === 200)

            //用户头像
            Image {
                visible: (type === msg_TYPE_TEXT)
                anchors.left: (UserInfo.uid === uid) ? textRect.right : parent.left
                anchors.leftMargin: (UserInfo.uid === uid) ? 10 : 0
                width:40
                height: 40
                source: "../src/image/gravatar.png"
            }

            Rectangle {
                visible: (type === msg_TYPE_TEXT)
                id:  textRect
                width: parent.width - 100
                anchors.left: parent.left
                anchors.leftMargin: 50

                color: (UserInfo.uid === uid) ? "#66ccff" : "#00000000"

                //用户名
                Text {
                    anchors.left: parent.left
                    width: parent.width
                    height:20
                    color:"#a3b4ce"
                    text:uid
                    font.pointSize: 10
                    horizontalAlignment: (UserInfo.uid === uid) ? Text.AlignRight : Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Rectangle {
                    anchors.left: parent.left
                    y:parent.y + 20
                    width: parent.width
                    radius: 10

                    color: (UserInfo.uid === uid) ? "#66ccff" : "#00000000"
                    //发送的消息内容
                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        anchors.top: parent.top
                        width: parent.width - 10
                        text:content
                        color:(UserInfo.uid === uid) ? "#fff" : "#75738f"
                        font.pointSize: 15
                        wrapMode:  Text.Wrap
                        horizontalAlignment: (UserInfo.uid === uid) ? Text.AlignRight : Text.AlignLeft
                        Component.onCompleted: {
                            parent.height = this.height;
                            parent.parent.parent.height = this.height + 20;
                        }
                    }
                    MouseArea {
                        id: mouseRegion
                        anchors.fill: parent;
                        acceptedButtons: Qt.LeftButton | Qt.RightButton // 激活右键

                        onClicked: function(mouse) {
                            if (mouse.button === Qt.RightButton && type === msg_TYPE_TEXT) { // 右键菜单
                                contentMenu.open();
                            }
                        }

                        Menu { // 右键菜单
                            id: contentMenu

                            MenuItem {
                                text: "撤回"
                                onTriggered: {
                                    NowChatListModel.send_remove_msg_click(mid);
                                }
                            }
                        }
                    }
                }
            }

            //提示信息
            Rectangle {
                visible: (type === msg_TYPE_TIP)
                width: parent.width - 100
                anchors.left: parent.left
                anchors.leftMargin: 50
                color:"#a3b4ce"
                radius: 10

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.top: parent.top
                    width: parent.width - 10
                    color:"#fff"
                    font.pointSize: 12
                    text:content
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Component.onCompleted: {
                        parent.height = this.height;
                        parent.parent.height = this.height;
                    }
                }
            }
        }
    }
}
