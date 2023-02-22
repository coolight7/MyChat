import QtQuick 2.0
import QtQuick.Controls 2.5

import NowChatListModel 1.0
import UserInfo 1.0

Rectangle {
    property real account_NORMAL    : 200;      //账号状态正常
    property real account_SEALED    : 201;      //封禁（不可登录，发言等所有操作）
    property real account_NOMSG     : 202;      //禁言（可登录，可接收信息，但不可发言）

    function flushUserState() {
        if(UserInfo.state === account_NORMAL) {
            topTipRect.visible = false;
        } else {
            topTipRect.visible = true;
            if(UserInfo.state === account_NOMSG) {
                topTipText.text = "您已被禁言";
            } else {
                topTipText.text = "您已被封号";
            }
        }
    }

    id:chatPostRect
    color:"#00000000"
    radius: 20
    border.color: "#66ccff"
    border.width: 1

    Rectangle {
        id:topTipRect
        anchors.fill: parent
        color:"#fff"
        z:2
        border.color: "#66ccff"
        border.width: 1
        radius: 20
        clip: true
        visible: (UserInfo.state !== account_NORMAL)
        Text{
            id:topTipText
            anchors.fill: parent
            text: (UserInfo.state === account_NOMSG)? "您已被禁言":"您已被封号"
            color: "#7b7995"
            font.bold: true
            font.pointSize: 15
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:   Text.AlignVCenter
        }
    }

    Rectangle {
        id:btnList
        width:parent.width
        height: 25
        color: "#00000000"

        Button {
            id:postmsgBtn
            width: 70
            height: parent.height
            anchors.right: parent.right
            Rectangle {
                anchors.fill: parent
                radius: 10
                color: "#66ccff"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: "发送"
                    color: "#fff"
                    font.pointSize: 12
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            onClicked: {
                if(UserInfo.state === account_NORMAL) {
                    if(edit.text === "") {
                        return;
                    }
                    NowChatListModel.send_TCP_text_click(edit.text);
                    edit.text = "";
                }
            }
        }

    }

    Rectangle {
        id:editRect
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
        width: chatPostRect.width - 20
        height: chatPostRect.height - btnList.height - 5
        clip: true

        Flickable {
           id: flick
           anchors.fill: parent
           contentWidth: edit.paintedWidth
           contentHeight: edit.paintedHeight
           clip: true
           function ensureVisible(r)
           {
               if (contentX >= r.x)
                   contentX = r.x;
               else if (contentX+width <= r.x+r.width)
                   contentX = r.x+r.width-width;
               if (contentY >= r.y)
                   contentY = r.y;
               else if (contentY+height <= r.y+r.height)
                   contentY = r.y+r.height-height;
           }
           TextEdit {
               id:edit
               width: flick.width
               height: flick.height
               font.pointSize: 12
               color: "#787790"
               wrapMode:TextEdit.Wrap
               focus: true
               onCursorRectangleChanged:flick.ensureVisible(cursorRectangle)
               Keys.onReturnPressed: {
                   postmsgBtn.clicked();
               }
           }
        }
    }
}
