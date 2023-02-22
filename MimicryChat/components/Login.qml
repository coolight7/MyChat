import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import LoginObj 1.0

//登录/注册
Rectangle {
    //显示类型，true未登录，false未注册
    property bool showType: true
    property bool isConn: false

    function showSignIn() {
        showType = true;
    }

    function showSignUp () {
        showType = false;
    }

    function connSucc() {
        isConn = true;
    }
    function connErr() {
        isConn = false;
    }

    width:  300
    height: 400
    color:"#00000000"

    Rectangle {
        id:tipstr
        color:"#00000000"
        width:parent.width
        height: 80
        anchors.top: parent.top
        anchors.topMargin: 10

        Text {
            width: parent.width
            height:30
            anchors.top: parent.top
            text:"My Chat"
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
    }


    Rectangle {
        id:connRect
        width:  parent.width
        height: 25
        radius: 10
        anchors.top: tipstr.bottom
        anchors.topMargin: 20

        Text {
            id:portTipText
            anchors.left: parent.left
            anchors.top: parent.top
            width: 150
            height: parent.height
            text:"房间号：127.0.0.1:"
            font.bold: true
            font.pointSize: 12
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            clip: true
            color:"#a3b4ce"
        }

        TextInput {
            id:inputPort
            text: LoginObj.port
            width: 50
            height: parent.height
            anchors.left: portTipText.right
            horizontalAlignment: Text.AlignLeft

            font.pointSize: 15
            color: "#787790"
        }

        Button {
            id: connentBtn
            width:  100
            height: parent.height

            anchors.top: parent.top
            anchors.left: inputPort.right
            enabled: !isConn
            background: Rectangle {
                radius: 10
                color: "#66ccff"
                border.color: "#fff"
                border.width: 3
                Text {
                    anchors.fill: parent
                    text: isConn? "已连接" : "连接"
                    color: "#fff"
                    font.bold: true
                    font.pointSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            onClicked:  {
                if(inputPort.text <= 0) {
                    mainWin.tip("房间号不正确");
                    return;
                }
                LoginObj.port = inputPort.text;
                LoginObj.clientConn_click();
            }
        }
    }


    Rectangle {
        id:shiftRect
        anchors.top: connRect.bottom
        anchors.topMargin: 50
        width: parent.width
        height: 40
        color:"#00000000"

        Rectangle {
            anchors.top: parent.top
            anchors.left:parent.left
            width: parent.width / 2
            height: parent.height
            color:"#00000000"
            Text {
                id: toSignInBtn
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("登录")
                color: (showType) ?  "#78778f" : "#a3b4ce"
                font.pointSize: 15
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        showSignIn();
                    }
                }
            }
        }

        Rectangle {
            anchors.top: parent.top
            anchors.right:parent.right
            width: parent.width / 2
            height: parent.height
            color:"#00000000"
            Text {
                id: toSignUpBtn
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("注册")
                color: (showType) ? "#a3b4ce" : "#78778f"
                font.pointSize: 15
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        showSignUp();
                    }
                }
            }
        }

    }


    //输入用户名
    Rectangle {
        id:inputUserNameRect
        width: parent.width
        height: 25
        anchors.top: shiftRect.bottom
        anchors.topMargin: 10
        radius: 10

        Text {
            text:"用户名："
            font.pointSize: 12
            font.bold: true
            color: "#a3b4ce"
            width: parent.width - 100
            height: parent.height
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextInput {
            id:inputUserName
            text: ""
            width: 100
            height: parent.height
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight

            font.pointSize: 15
            color: "#787790"
        }
    }

    //输入密码
    Rectangle {
        id:inputPasswdRect
        width: parent.width
        height: 25
        visible: showType
        anchors.top: inputUserNameRect.bottom
        anchors.topMargin: 10
        radius: 10

        Text {
            text:"密码："
            font.pointSize: 12
            font.bold: true
            color: "#a3b4ce"
            width: parent.width - 50
            height: parent.height
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextInput {
            id: inputPasswd
            text: ""
            width: 50
            height: parent.height
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight

            font.pointSize: 15
            color: "#787790"
            Keys.onReturnPressed: {
                signInBtn.clicked();
            }
        }
    }

    Button {
        id: signInBtn
        width:parent.width
        height: 40
        visible: showType

        enabled: isConn
        anchors.top: inputPasswdRect.bottom
        anchors.topMargin: 10

        background: Rectangle {
            radius: 10
            color: "#66ccff"
            border.color: "#fff"
            border.width: 3
            Text {
                anchors.fill: parent
                text:"登录"
                color: "#fff"
                font.bold: true
                font.pointSize: 15
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        onClicked:  {
            if(inputUserName.text.length < 6) {
                mainWin.tip("用户名长度需要大于等于 6 个字符");
                return;
            }
            if(inputPasswd.text.length < 6) {
                mainWin.tip("用户名长度需要大于等于 6 个字符");
                return;
            }
            LoginObj.signIn_click(inputUserName.text, inputPasswd.text);
        }
    }

    //输入密码
    Rectangle {
        id:inputPasswd1Rect
        width: parent.width
        height: 25
        visible: !showType
        anchors.top: inputUserNameRect.bottom
        anchors.topMargin: 10
        radius: 10

        Text {
            text:"密码："
            font.pointSize: 12
            font.bold: true
            color: "#a3b4ce"
            width: parent.width - 50
            height: parent.height
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextInput {
            id: inputPasswd1
            text: ""
            width: 50
            height: parent.height
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight

            font.pointSize: 15
            color: "#787790"
            Keys.onReturnPressed: {
                signUpBtn.clicked();
            }
        }
    }

    //输入密码
    Rectangle {
        id:inputPasswd2Rect
        width: parent.width
        height: 25
        visible: !showType
        anchors.top: inputPasswd1Rect.bottom
        anchors.topMargin: 10
        radius: 10

        Text {
            text:"重复一次密码："
            font.pointSize: 12
            font.bold: true
            color: "#a3b4ce"
            width: parent.width - 50
            height: parent.height
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        TextInput {
            id: inputPasswd2
            text: ""
            width: 50
            height: parent.height
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight

            font.pointSize: 15
            color: "#787790"

            Keys.onReturnPressed: {
                signUpBtn.clicked();
            }
        }
    }

    //注册
    Button {
        id: signUpBtn
        width:parent.width
        height: 40
        visible: !showType

        anchors.top: inputPasswd2Rect.bottom
        anchors.topMargin: 10

        enabled: isConn

        background: Rectangle {
            radius: 10
            color: "#66ccff"
            border.color: "#fff"
            border.width: 3
            Text {
                anchors.fill: parent
                text:"注册"
                color: "#fff"
                font.bold: true
                font.pointSize: 15
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        onClicked:  {
            if(inputUserName.text.length < 6) {
                mainWin.tip("用户名长度需要大于等于 6 个字符");
                return;
            }
            if(inputPasswd1.text.length < 6 || inputPasswd2.text.length < 6) {
                mainWin.tip("密码长度需要大于等于 6 个字符");
                return;
            }
            if(inputPasswd1.text != inputPasswd2.text){
                mainWin.tip("两次输入的密码不相同");
                return;
            }
            LoginObj.signUp_click(inputUserName.text, inputPasswd1.text);
        }
    }
}
