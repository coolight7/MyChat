import QtQuick 2.0
import QtQuick.Controls 2.5

import UserControlObj 1.0

Rectangle {
    property real account_NORMAL    : 200;      //账号状态正常
    property real account_SEALED    : 201;      //封禁（不可登录，发言等所有操作）
    property real account_NOMSG     : 202;      //禁言（可登录，可接收信息，但不可发言）


    color: "#fff"
    radius: 20
    border.color: "#66ccff"
    border.width: 1

    Rectangle {
        anchors.fill: parent
        color:"#fff"
        z:2
        radius: 20
        clip: true
        visible: (UserControlObj.uid < 0)
        Text{
            anchors.fill: parent
            text:"请选择用户"
            color: "#7b7995"
            font.bold: true
            font.pointSize: 15
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:   Text.AlignVCenter
        }
    }

    Rectangle {
        id:userIconRect
        width:  80
        height: 80
        z:1
        color:  "#00000000"
        radius: 20
        border.color: "#66ccff"
        border.width: 3
        clip: true
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        ImgMask {
            anchors.fill: parent
            iRadius:20
            iSource: Image {
                anchors.fill: parent
                source: "../src/image/" + UserControlObj.img
                visible: false
            }
        }
    }


    Text {
        id:userNameText
        height: 40
        width: parent.width
        anchors.top: userIconRect.bottom
        anchors.topMargin: 10
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:   Text.AlignVCenter
        clip: true

        text: UserControlObj.userName
        font.bold: true
        font.pointSize: 15
        color: "#7b7995"
    }

    //用户状态管理按钮
    Rectangle {
        id:stateControlRect
        width:parent.width
        height: 40
        color:"#00000000"
        anchors.top: userNameText.bottom
        anchors.topMargin: 20
        anchors.left: parent.left

        //禁言按钮
        Button {
            id: nomsgBtn
            width:  70
            height: parent.height

            anchors.top: parent.top
            anchors.right: normalBtn.left
            anchors.rightMargin: 70
            enabled: (UserControlObj.state !== account_NOMSG)
            background: Rectangle {
                radius: 10
                color:(UserControlObj.state === account_NOMSG)? "#7b7995":"#66ccff"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: (UserControlObj.state === account_NOMSG)? "已禁言" : "禁言"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment:   Text.AlignVCenter
                }
            }
            onClicked:  {
                UserControlObj.setNomsgAccount();
            }
        }

        //正常状态按钮
        Button {
            id: normalBtn
            width:  70
            height: parent.height

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            enabled: (UserControlObj.state !== account_NORMAL)
            background: Rectangle {
                radius: 10
                color: (UserControlObj.state === account_NORMAL)? "#7b7995":"#66ccff"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: "正常"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment:   Text.AlignVCenter
                }
            }
            onClicked:  {
                UserControlObj.setNormalAccount();
            }
        }


        Button {
            id: sealedBtn
            width:  70
            height: parent.height

            anchors.top: parent.top
            anchors.left: normalBtn.right
            anchors.leftMargin: 70
            enabled: (UserControlObj.state !== account_SEALED)
            background: Rectangle {
                radius: 10
                color: (UserControlObj.state === account_SEALED)? "#7b7995":"#66ccff"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: (UserControlObj.state === account_SEALED)? "已封禁":"封禁"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment:   Text.AlignVCenter
                }
            }
            onClicked:  {
                UserControlObj.setSealedAccount();
            }
        }
    }
    //发送提示信息
    Rectangle {
        id:postClientTipRect
        width:  parent.width - 100
        height: 40
        radius: 10
        anchors.top: stateControlRect.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 50
        color:"#00000000"
        border.color: "#66ccff"
        border.width: 1
        visible: UserControlObj.isLogin

        TextInput {
            id:inputTip

            width: parent.width - 80
            height: parent.height
            anchors.left: parent.left
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter

            font.pointSize: 15
            color: "#787790"

            Keys.onReturnPressed: {
                postClientTipBtn.clicked();
            }
        }

        Button {
            id: postClientTipBtn
            width:  70
            height: parent.height - 4

            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.right: parent.right
            anchors.rightMargin: 2

            background: Rectangle {
                radius: 10
                color: "#66ccff"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: "发送"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            onClicked:  {
                if(inputTip.text === "") {
                    return;
                }
                UserControlObj.send_client_tip(inputTip.text);
                inputTip.text = "";
            }
        }
    }
}
