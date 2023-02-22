import QtQuick
import QtQuick.Window 2.3
import QtQuick.Controls 2.5

import "./components" as Com

import RoomListModel 1.0

Window {
    id:mainWin
    width: 700
    height: 500
    visible: true
    title: qsTr("MimicryChat")

    //
    function tip(in_str, in_time) {
        tipbar.tip(in_str, in_time);
    }

    function connectSuccess() {
        loginRect.connSucc();
    }
    function connectError() {
        loginRect.connErr();
    }

    function loginSuccess() {
        loginRect.visible = false;
        contentRect.visible = true;
    }

    function chatView_scrollToBottom() {
        contentRect.chatView_scrollToBottom();
    }

    function chatPost_flushUserState() {
        contentRect.chatPost_flushUserState();
    }

    Rectangle {
        anchors.fill: parent
        color: "#dde8fc"
        radius: 20
    }


    //-----提示栏-----
    Com.TipBar {
        id:tipbar
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        width:500
    }
    //-----用户栏-------
    Com.UserBar {
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        width:200
    }

    Com.Login {
        id:loginRect
        visible: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top:    tipbar.bottom
        anchors.topMargin: 10
    }

    Com.Content {
        id:contentRect
        visible: false
        anchors.left:   parent.left
        anchors.top:    tipbar.bottom
        anchors.topMargin: 10
    }

    onClosing:{
        RoomListModel.send_close_client_click();
        Qt.quit();
    }

}
