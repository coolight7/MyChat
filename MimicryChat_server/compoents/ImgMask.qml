import QtQuick 2.0
import Qt5Compat.GraphicalEffects
import QtQuick.Controls 2.5


Rectangle {
    property alias iSource: mask.source
    property alias iRadius: maskSrc.radius
    color:"#00000000"

    Rectangle{
        id: maskSrc
        anchors.fill: parent
        radius: 10
        visible: false
    }

    OpacityMask {
        id:mask
        anchors.fill: parent
        maskSource: maskSrc
    }

}

