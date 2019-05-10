import QtQuick 2.4

Item {
    width: 400
    height: 400

    Rectangle {
        id: rectangle
        color: "#191919"
        clip: true
        anchors.fill: parent

        Rectangle {
            id: rectangle1
            x: -36
            y: -79
            width: 100
            height: 200
            color: "#333333"
            rotation: 45
        }
    }
}

/*##^## Designer {
    D{i:1;anchors_height:200;anchors_width:200;anchors_x:221;anchors_y:161}
}
 ##^##*/
