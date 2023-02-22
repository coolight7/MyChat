import QtQuick 2.0
import QtQuick.Controls 2.5
import InitSocketObj 1.0

Rectangle {

    width: 250
    height: 200

    color:"#00000000"

    Rectangle {
        id:tipstr
        color:"#00000000"
        width:parent.width
        height: 120
        anchors.top: parent.top
        anchors.topMargin: 10

        Text {
            width: parent.width
            height:30
            anchors.top: parent.top
            text:"My Chat Server"
            font.pointSize: 17
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            clip: true
            color:"#787790"
        }
        Text {
            width: parent.width
            height:30
            anchors.top: parent.top
            anchors.topMargin: 40
            text:"coolight"
            font.pointSize: 15
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            clip: true
            color:"#a3b4ce"
        }
        Text {
            width: parent.width
            height:30
            anchors.top: parent.top
            anchors.topMargin: 80
            text:"请输入端口号，然后创建聊天服务"
            font.pointSize: 12
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            clip: true
            color:"#a3b4ce"
        }
    }


    //输入房间名
    Rectangle {
        id:inputNameRect
        width: parent.width
        height: 25
        anchors.top: tipstr.bottom
        anchors.topMargin: 10
        radius: 10

        Text {
            text:"房间名："
            font.pointSize: 12
            font.bold: true
            color: "#a3b4ce"
            width: parent.width - 100
            height: parent.height
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextInput {
            id:inputName
            text: InitSocketObj.name
            width: 100
            height: parent.height
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight

            font.pointSize: 15
            color: "#787790"
        }
    }

    //输入端口号
    Rectangle {
        id:inputPointRect
        width: parent.width
        height: 25
        anchors.top: inputNameRect.bottom
        anchors.topMargin: 10
        radius: 10

        Text {
            text:"房间号："
            font.pointSize: 12
            font.bold: true
            color: "#a3b4ce"
            width: parent.width - 50
            height: parent.height
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextInput {
            id: inputPort
            text: InitSocketObj.rid
            width: 50
            height: parent.height
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight

            font.pointSize: 15
            color: "#787790"
        }
    }


    Button {
        id: createBtn
        width:parent.width
        height: 40

        anchors.top: inputPointRect.bottom
        anchors.topMargin: 10

        background: Rectangle {
            radius: 10
            color: "#66ccff"
            border.color: "#fff"
            border.width: 3
            Text {
                anchors.fill: parent
                text:"创建"
                color: "#fff"
                font.bold: true
                font.pointSize: 15
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        onClicked:  {
            if(InitSocketObj.name.length <= 0) {
                mainWin.tip("房间名不能为空");
                return;
            }else if(InitSocketObj.rid <= 1024 || InitSocketObj.rid >= 60000) {
                mainWin.tip("房间号建议在[1025, 59999]");
                return;
            }
            InitSocketObj.name = inputName.text;
            InitSocketObj.rid = inputPort.text;
            InitSocketObj.create();
        }
    }

}
