import QtQuick 2.0
import QtQuick.Controls 2.5


Rectangle {
    width: 700
    height: 380

    color:"#00000000"

    function addRoom(in_port, in_name, in_img) {
        roomlist.addRoom(in_port, in_name, in_img);
    }

    //使聊天记录滑动到底部
    function chatView_scrollToBottom() {
        chatview.scrollToBottom();
    }

    function chatPost_flushUserState() {
        chatPost.flushUserState();
    }


    //房间列表
    RoomList {
        id:roomlist
        width:  200
        height: parent.height
    }

    //聊天窗
    Rectangle {
        width: parent.width - roomlist.width - 20
        height: parent.height
        anchors.left: roomlist.right
        anchors.leftMargin: 10
        color:"#fff"
        radius: 20

        //消息显示
        ChatView {
            id:chatview
            anchors.top: parent.top
            anchors.left: parent.left
            width:parent.width
            height:parent.height - 120
        }

        //发送框
        ChatPost {
            id:chatPost
            width:parent.width
            height:100
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }
    }

}
