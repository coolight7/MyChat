import QtQuick 2.0
import QtQuick.Controls 2.5

import UserListObj 1.0
import UserLoginListModel 1.0

Rectangle {
    property real selectUserListType: 2
    property real cacheSelectIndex:0

    function selectLoginList() {
        if(selectUserListType == 1)
            return;
        let i = cacheSelectIndex;
        cacheSelectIndex = userListView.currentIndex;
        selectUserListType = 1;
        let size = UserLoginListModel.getListSize();
        if(size <= 0)
            return;
        if(i >= 0 && i < size) {
            userListView.currentIndex = i;
            UserLoginListModel.setUserControl(i);
        } else {
            userListView.currentIndex = 0;
            UserLoginListModel.setUserControl(0);
        }
    }

    function selectAllList() {
        if(selectUserListType == 2)
            return;
        let i = cacheSelectIndex;
        cacheSelectIndex = userListView.currentIndex;
        selectUserListType = 2;
        let size = UserListObj.getListSize();
        if(size <= 0)
            return;
        if(i >= 0 && i < size) {
            userListView.currentIndex = i;
            UserListObj.setUserControl(i);
        } else {
            userListView.currentIndex = 0;
            UserListObj.setUserControl(0);
        }
    }

    color:"#00000000"

    Rectangle {
        id:selectBtnRect
        color:"#00000000"
        width: parent.width
        height: 40
        anchors.top: parent.top
        anchors.left: parent.left

        //正常状态按钮
        Button {
            id: selectAllBtn
            width:  70
            height: parent.height

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: ((parent.width - 70 * 2) / 3)
            background: Rectangle {
                radius: 10
                color: (selectUserListType === 2)? "#66ccff":"#7b7995"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: "全部"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment:   Text.AlignVCenter
                }
            }
            onClicked:  {
                selectAllList();
            }
        }

        //正常状态按钮
        Button {
            id: selectLoginBtn
            width:  70
            height: parent.height

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: ((parent.width - 70 * 2) / 3)
            background: Rectangle {
                radius: 10
                color: (selectUserListType === 1)? "#66ccff":"#7b7995"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: "在线"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment:   Text.AlignVCenter
                }
            }
            onClicked:  {
                selectLoginList();
            }
        }
    }


    ListView {
        id:             userListView
        anchors.left: parent.left
        anchors.top: selectBtnRect.bottom
        anchors.topMargin: 10
        width: parent.width
        height: parent.height - selectBtnRect.height - 10
        clip:           true

        model: (selectUserListType == 1)? UserLoginListModel : UserListObj

        spacing: 10

        delegate: Rectangle {
            anchors.left: parent.left
            anchors.leftMargin: (userListView.currentIndex === index) ? 10:0
            y:index * 50

            width: (userListView.currentIndex === index) ? (parent.width - 10): (parent.width)
            height: 40
            radius: 10
            color: (userListView.currentIndex === index) ? "#fff" :"#00000000"

            ImgMask {
                x: parent.x
                width:parent.height
                height:parent.height

                iRadius:10
                iSource: Image {
                    visible: false
                    source: "../src/image/" + img
                }
            }

            Rectangle {
                x:      parent.x + parent.height + 20
                width:  parent.width - parent.height - 30
                height: parent.height
                color:"#00000000"

                Text {
                    y:0
                    width:  parent.width
                    height: parent.height / 2

                    text: userName
                    font.bold: true
                    font.pointSize: 15
                    color:"#75738e"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment:   Text.AlignVCenter
                }

                Text {
                    y:      parent.height / 2
                    width:  parent.width
                    height: parent.height / 2

                    text: uid
                    font.pointSize: 12
                    color: "#aabbd4"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment:   Text.AlignVCenter
                }
            }

            MouseArea {
                anchors.fill: parent;
                //点击时切换用户
                onClicked:{
                    userListView.currentIndex = index;
                    if(selectUserListType == 1) {
                        UserLoginListModel.setUserControl(index);
                    } else {
                        UserListObj.setUserControl(index);
                    }
                }
            }
        }
    }

}
