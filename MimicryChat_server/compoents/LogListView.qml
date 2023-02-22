import QtQuick 2.0
import QtQuick.Controls 2.5

import ChatList 1.0

Rectangle {
    property real selectType: 2

    property real msg_TYPE_TEXT : 10001;         //聊天信息类型：普通文本
    property real msg_TYPE_TIP  : 10010;         //聊天信息类型，提示信息

    function chatListScrollToEnd() {
        chatList.positionViewAtEnd();
    }

    color:"#00000000"

    function addLog(in_content) {
        var myDate = new Date();
        logList.model.append({
                                time:myDate.toLocaleTimeString(),
                                content:in_content
                          });
        logList.positionViewAtEnd();
    }

    function showLog() {
        selectType = 1;
    }
    function showChat() {
        selectType = 2;
    }

    //选择显示
    Rectangle {
        id:selectBtnRect
        color:"#00000000"
        width: parent.width
        height: 40
        anchors.top: parent.top
        anchors.left: parent.left

        //日志按钮
        Button {
            id: selectLogBtn
            width:  70
            height: parent.height

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: ((parent.width - 70 * 2) / 3)
            background: Rectangle {
                radius: 10
                color: (selectType === 1)? "#66ccff":"#7b7995"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: "日志"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment:   Text.AlignVCenter
                }
            }
            onClicked:  {
                showLog();
            }
        }

        //聊天按钮
        Button {
            id: selectChatBtn
            width:  70
            height: parent.height

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: ((parent.width - 70 * 2) / 3)
            background: Rectangle {
                radius: 10
                color: (selectType === 2)? "#66ccff":"#7b7995"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: "聊天"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment:   Text.AlignVCenter
                }
            }
            onClicked:  {
                showChat();
            }
        }
    }

    Rectangle {
        color: "#fff"
        radius: 20
        border.color: "#66ccff"
        border.width: 1
        width: parent.width - 20
        height: parent.height - selectBtnRect.height - 10
        anchors.top: selectBtnRect.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10



        //聊天窗口
        ListView {
            id:chatList
            visible: (selectType == 2)

            width: parent.width - 4
            height: parent.height - 4
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 2

            clip: true
            model:ChatList

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
                    anchors.left: parent.left
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

                    color: "#00000000"

                    //用户名
                    Text {
                        anchors.left: parent.left
                        width: parent.width
                        height:20
                        color:"#a3b4ce"
                        text:uid
                        font.pointSize: 10
                        horizontalAlignment:Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }

                    Rectangle {
                        anchors.left: parent.left
                        y:parent.y + 20
                        width: parent.width
                        radius: 10

                        color:"#00000000"
                        //发送的消息内容
                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            anchors.top: parent.top
                            width: parent.width - 10
                            text:content
                            color:"#75738f"
                            font.pointSize: 15
                            wrapMode:  Text.Wrap
                            horizontalAlignment: Text.AlignLeft
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
                                if (mouse.button === Qt.RightButton && type === msg_TYPE_TEXT) {      // 右键菜单
                                    contentMenu.open();
                                }
                            }

                            Menu { // 右键菜单
                                id: contentMenu

                                MenuItem {
                                    text: "撤回"
                                    onTriggered: {
                                        ChatList.send_remove_msg(mid);
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

        //日志窗口
        ListView {
            id:logList

            visible: (selectType == 1)

            width: parent.width - 4
            height: parent.height - 4
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 2

            clip: true
            model:ListModel{

            }

            spacing: 10

            add: Transition {
                NumberAnimation { properties: "x,y"; from: 100; duration: 300 }
            }

            delegate: Rectangle {
                x:  parent.x + 10
                width:  parent.width - 20
                height:  (contentText.height > 20 ? (contentText.contentHeight):20) + 20
                anchors.left: parent.left
                radius: 10

                Rectangle {
                    width: parent.width
                    x:parent.x

                    color:"#00000000"

                    //时间
                    Text {
                        id:timeText
                        anchors.left: parent.left
                        width: parent.width
                        height:20
                        color:"#a3b4ce"
                        text:time
                        font.pointSize: 10
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }

                    //发送的消息内容
                    Text {
                        id: contentText
                        anchors.top: parent.top
                        anchors.topMargin: 20
                        anchors.left: parent.left
                        width: parent.width
                        height: contentHeight + 10
                        text:content
                        color:"#75738f"
                        font.pointSize: 15
                        wrapMode:  Text.Wrap
                    }
                }
            }
        }
    }
}

