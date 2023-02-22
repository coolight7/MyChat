import QtQuick 2.0
import QtQuick.Controls 2.5


Rectangle {

    //0:日志， 1：用户列表， 2：设置
    property real selectType: 1

    //底部按钮列表
    id: footerBar
    color:  "#00000000"

    Rectangle {
        width:  40
        height: 40
        id: select_logRect

        radius: 10
        color:        (selectType === 0) ? "#66ccff" : "#00000000"
        border.color: (selectType === 0) ? "#fff" : "#b2c1d9"
        border.width: 3
        anchors.left: parent.left
        anchors.leftMargin: (parent.width - 40 * 3) / 4

        //显示/隐藏提示文本
        Button {
            id:select_logBtn
            width:  36
            height: 36
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - this.width) / 2
            anchors.top: parent.top
            anchors.topMargin: (parent.height - this.height) / 2


            contentItem: Image {
                source: (selectType === 0) ? "../src/icon/bug_light.svg" : "../src/icon/bug_dark.svg";
            }

            background: Rectangle {
                color:"#00000000"
            }

            onClicked: {
                selectType = 0;
            }
        }
    }

    Rectangle {
        width:  40
        height: 40
        id: select_userListRect

        radius: 10
        color:        (selectType === 1) ? "#66ccff" : "#00000000"
        border.color: (selectType === 1) ? "#fff" : "#b2c1d9"
        border.width: 3
        anchors.horizontalCenter: parent.horizontalCenter

        //显示/隐藏提示文本
        Button {
            id:select_userListBtn
            width:  36
            height: 36
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - this.width) / 2
            anchors.top: parent.top
            anchors.topMargin: (parent.height - this.height) / 2


            contentItem: Image {
                source: (selectType === 1) ? "../src/icon/user_light.svg" : "../src/icon/user_dark.svg";
            }

            background: Rectangle {
                color:"#00000000"
            }

            onClicked: {
                selectType = 1;
            }
        }
    }

    Rectangle {
        width:  40
        height: 40
        id: select_settingRect

        radius: 10
        color: (selectType === 2) ? "#66ccff" : "#00000000"
        border.color: (selectType === 2) ? "#fff" : "#b2c1d9"
        border.width: 3
        anchors.right: parent.right
        anchors.rightMargin: (parent.width - 40 * 3) / 4

        //显示/隐藏提示文本
        Button {
            id:select_settingBtn
            width:  36
            height: 36
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - this.width) / 2
            anchors.top: parent.top
            anchors.topMargin: (parent.height - this.height) / 2


            contentItem: Image {
                source: (selectType === 2) ? "../src/icon/settings_light.svg" : "../src/icon/settings_dark.svg";
            }

            background: Rectangle {
                color:"#00000000"
            }

            onClicked: {
                selectType = 2;
            }
        }
    }

}
