import QtQuick 2.0
import QtQuick.Controls 2.5

import ChatFilterListModel 1.0
import SettingControlObj 1.0

Rectangle {
    property bool isEdit: false

    function toEditInfo_f() {
        isEdit = true;
    }

    function cancleEditInfo_f() {
        rnameText.text = SettingControlObj.rname;
        isEdit = false;
    }

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
        visible: (SettingControlObj.rid < 0)
        Text{
            anchors.fill: parent
            text:"请选择房间"
            color: "#7b7995"
            font.bold: true
            font.pointSize: 15
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:   Text.AlignVCenter
        }
    }

    //房间封面图
    Rectangle {
        id:rimgRect
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
                source: "../src/image/" + SettingControlObj.rimg
                visible: false
            }
        }
    }

    //房间名
    Rectangle {
        id:rnameTextRect
        height: 40
        color:"#00000000"
        width: parent.width - 100
        anchors.top: rimgRect.bottom
        anchors.topMargin: 10
        radius: 10

        border.color: isEdit? "#66ccff":"#00000000"
        border.width : 1
        anchors.horizontalCenter: parent.horizontalCenter
        TextInput {
            id:rnameText
            width: parent.width - 4
            height: parent.height - 4
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 2
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:   Text.AlignVCenter
            clip: true
            enabled: isEdit

            text: SettingControlObj.rname
            font.bold: true
            font.pointSize: 15
            color: "#7b7995"
        }
    }

    Rectangle {
        id:chatFilterListRect
        color:"#00000000"
        width: parent.width
        height: 150
        anchors.top: rnameTextRect.bottom
        anchors.topMargin: 10
        anchors.left: parent.left

        ListView {
            id: chatFilterList
            width:parent.width - 60
            height: parent.height - 50
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 30
            clip: true

            model: ChatFilterListModel

            spacing: 10

            delegate: Rectangle {
                x: parent.x
                y:  index * 50

                width: chatFilterList.width
                height: 40
                radius: 10
                color: "#00000000"
                border.color: "#66ccff"
                border.width: 1

                Text {
                    width:  parent.width - 40
                    height: parent.height
                    text:   str
                    font.bold: true
                    font.pointSize: 12
                    color:"#75738e"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment:   Text.AlignVCenter
                }

                Button {
                    id: postFilterBtn
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
                            text: "删除"
                            color: "#fff"
                            font.bold: true
                            font.pointSize: 12
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment:  Text.AlignVCenter
                        }
                    }
                    onClicked:  {
                        ChatFilterListModel.remove(index);
                    }
                }
            }
        }

        //添加敏感词
        Rectangle {
            id:postFilterRect
            width:  parent.width - 60
            height: 40
            radius: 10
            anchors.top: chatFilterList.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 30
            color:"#00000000"
            border.color: "#66ccff"
            border.width: 1

            TextInput {
                id:inputFilter

                width: parent.width - 80
                height: parent.height
                anchors.left: parent.left
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter

                font.pointSize: 12
                color: "#787790"

                Keys.onReturnPressed: {
                    postChatFilterBtn.clicked();
                }
            }

            Button {
                id: postChatFilterBtn
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
                        text: "添加"
                        color: "#fff"
                        font.bold: true
                        font.pointSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                onClicked: {
                    if(inputFilter.text === "") {
                        return;
                    }
                    ChatFilterListModel.append(inputFilter.text);
                    inputFilter.text = "";
                    chatFilterList.positionViewAtEnd();
                }
            }
        }
    }

    Rectangle {
        id:btnListRect
        color:"#00000000"
        width: parent.width
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left

        //进入修改按钮
        Button {
            id: editInfoBtn
            width:  100
            height: parent.height
            visible: !isEdit

            anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle {
                radius: 10
                color: "#66ccff"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: "编辑"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            onClicked:  {
                toEditInfo_f();
            }
        }


        //取消修改按钮
        Button {
            id: cancleInfoBtn
            width:  70
            height: parent.height
            visible: isEdit

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - 70 * 2) / 3
            background: Rectangle {
                radius: 10
                color: "#66ccff"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: "取消"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            onClicked:  {
                cancleEditInfo_f();
            }
        }

        //保存修改按钮
        Button {
            id: saveInfoBtn
            width:  70
            height: parent.height
            visible: isEdit

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: (parent.width - 70 * 2) / 3
            background: Rectangle {
                radius: 10
                color: "#66ccff"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: "保存"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            onClicked:  {
                if(rnameText.text === "") {
                    mainWin.tip("房间名不能为空");
                    return;
                }
                SettingControlObj.saveEditInfo(rnameText.text, SettingControlObj.rimg);
                rnameText.text = SettingControlObj.rname;
                isEdit = false;
            }
        }
    }

}
