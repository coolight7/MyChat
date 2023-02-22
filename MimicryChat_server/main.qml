import QtQuick
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import "./compoents" as Com

import SocketListModel 1.0
import UserListObj 1.0
import ChatFilterListModel 1.0

Window {
    id:mainWin
    width: 700
    height: 500
    visible: true
    title: qsTr("MimicryChat-server")

    property bool isCreate: false

    //提示消息
    function tip(in_str, in_time) {
        tipbar.tip(in_str, in_time);
    }

    //增加日志
    function addLog(in_content) {
        logListView.addLog(in_content);
    }

    function createSuccess() {
        isCreate = true;
    }
    function createError() {
        isCreate = false;
    }
    function chatListScrollToEnd() {
        logListView.chatListScrollToEnd();
    }

    Rectangle {
        anchors.fill: parent
        color: "#dde8fc"
        radius: 20
    }

    Com.TipBar {
        id:tipbar
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        width:parent.width
        height: 40
    }

    Com.InitSocket {
        id:initSocket
        visible: !isCreate
        anchors.top: tipbar.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id:contentRect

        width: parent.width - 20
        height:parent.height - 120
        anchors.top: tipbar.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        color:  "#00000000"

        //日志页面
        Com.LogListView {
            id:logListView
            visible: (isCreate && (footerBar.selectType === 0))
            anchors.fill: parent
        }


        //用户页面
        Rectangle {
            color:  "#00000000"
            anchors.fill: parent
            visible: (isCreate && (footerBar.selectType === 1))

            //用户列表
            Com.UserList {
                id:userList
                anchors.top: parent.top
                anchors.left: parent.left
                width:  200
                height: parent.height
            }

            //用户管理页面
            Com.UserControl {
                id:userControl
                width: parent.width - userList.width - 30
                height:parent.height
                anchors.top: parent.top
                anchors.left: userList.right
                anchors.leftMargin: 10
            }
        }

        //设置页面
        Rectangle {
            color:  "#00000000"
            anchors.fill: parent
            visible: (isCreate && (footerBar.selectType === 2))

            //用户列表
            Com.SettingList {
                id:settingList
                anchors.top: parent.top
                anchors.left: parent.left
                width:  200
                height: parent.height
            }

            //用户管理页面
            Com.SettingControl {
                id:settingControl
                width: parent.width - userList.width - 30
                height:parent.height
                anchors.top: parent.top
                anchors.left: settingList.right
                anchors.leftMargin: 10
            }
        }
    }


    Com.FooterBar {
        id:footerBar
        visible: isCreate
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        width:parent.width
        height: 40
    }

    onClosing:{
        console.log("saveUserList");
        UserListObj.saveUserList();
        console.log("saveChatList");
        SocketListModel.saveChatList();
        console.log("send_close_server");
        SocketListModel.send_close_server_click();
        console.log("saveChatFilter");
        ChatFilterListModel.saveSetting();
        Qt.quit();
    }

}
