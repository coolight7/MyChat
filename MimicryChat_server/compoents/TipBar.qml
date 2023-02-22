import QtQuick 2.0
import QtQuick.Controls 2.5

//------提示栏--------
Rectangle {
    id:tipbarRect

    property bool isShow: false
    property var tipList: [""]

    function tip(in_str, in_time) {
        if(typeof(in_time) == 'undefined') {
            in_time = 3000;
        }
        tipList.push(in_str);
        showTipText(in_time);
    }

    //显示提示信息
    //in_time：显示时间,单位ms
    //  如果 in_time <= 0，则显示并且不会自动关闭
    //  如果 in_time > 0，则显示in_time时间后自动关闭
    function showTipText(in_time) {
        tipText.text = tipList[tipList.length - 1];
        isShow = true;
        if(in_time > 0) {
            timer.interval = in_time;
            timer.restart();
//            mainWin.setTimeout(function() {
//                closeTipText();
//            }, in_time);
        }
    }

    //隐藏提示信息
    function closeTipText() {
        isShow = false;
    }

    color:  "#00000000"
    width:  500
    height: 40
    anchors.left: parent.left
    anchors.leftMargin: 20

    Timer {
        id:timer
        interval: 3000
        onTriggered: {
            closeTipText();
        }
    }


    Rectangle {
        width:  40
        height: 40
        id: tipBtnRect

        radius: 10
        color: isShow ? "#66ccff" : "#00000000"
        border.color: isShow ? "#fff" : "#b2c1d9"
        border.width: 3

        //显示/隐藏提示文本
        Button {
            id:tipBtn
            width:  36
            height: 36
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - this.width) / 2
            anchors.top: parent.top
            anchors.topMargin: (parent.height - this.height) / 2


            contentItem: Image {
                source: isShow ? "../src/icon/bell_light.svg" : "../src/icon/bell_dark.svg";
            }

            background: Rectangle {
                color:"#00000000"
            }

            onClicked: {
                if(isShow) {
                    closeTipText();
                } else {
                    showTipText(-1);
                }
            }
        }
    }


    //提示文本内容
    Text {
        id:      tipText
        width:   parent.width
        height:  40
        visible: isShow
        text:    tipList[tipList.length - 1]
        font.pointSize: 15
        font.bold:true

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        clip: true

        color:"#a3b4ce"


        anchors.left: parent.left
    }
}
