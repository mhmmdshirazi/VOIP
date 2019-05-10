import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
Window {
    id: window
    visible: true
    width: 375
    height: 667
    title: qsTr("phone over ip")

    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange


    function setTimer() {
        calling.running = true
    }
    TabBar {
        anchors.bottom: parent.bottom
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        id: pageChooser
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Phone")
        }
        TabButton {
            text: qsTr("Settings")
        }
    }

    SwipeView {
        id: swipeView
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottomMargin: 100
        currentIndex: pageChooser.currentIndex
        z: 10
        Phone {
            id:phoneTab
        }
        Settings {

        }
    }

    ProgressBar {
        id: callingBar
        y: 0
        height: 30
        visible: false
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        background: Rectangle {
            implicitHeight: 0
            color: "#191919"
            radius: 3
        }

        contentItem: Item {
            Rectangle {
                width: callingBar.visualPosition * parent.width
                height: parent.height
                radius: 2
                color: "#00FF00"
            }
        }

        Timer {
            id: calling
            repeat: true
            running: false
            interval: 10
            onTriggered: {
                parent.visible = true
                callingBar.value = callingBar.value + 0.01
                if(callingBar.value >= 1) {
                    callingBar.value = 0
                }
            }
        }
    }
    PageBG {
        anchors.fill: parent
        z: -10
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onPressed: {
                console.log("clicked")
                Qt.inputMethod.hide()
            }
        }
    }


//    BackGround {
//        id: backGround
//        anchors.fill: parent
//    }

}















/*##^## Designer {
    D{i:0;height:667;width:375}D{i:7;anchors_width:200;anchors_x:88}
}
 ##^##*/
