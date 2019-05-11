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
    function incommingCall(callerID) {
        calling.running = true
        callerIdInd.text = qsTr("Incoming Call From: %1").arg(callerID)
        answer.visible = true
        reject.visible = true
        console.log("calllllll")
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

    Button {
        id: answer
        height: 36
        width: 130
        anchors.left: parent.left
        anchors.leftMargin:30
        anchors.top: callingBar.bottom
        visible: false
        text: qsTr("Answer")
        background: Rectangle{
            color: answer.down ? "#A0FFA0" : "#00EE00"
            border.color: answer.down ? "#000000" : "#00EE00"
        }
    }

    Button {
        id: reject
        width: 130
        height: 36
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.top: callingBar.bottom
        visible: false
        text: qsTr("Reject")
        background: Rectangle{
            color: reject.down ? "#FFA0A0" : "#FF0000"
            border.color: reject.down ? "#000000" : "#FF0000"
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
        Text {
            id: callerIdInd
            visible: false
            anchors.fill: parent
            anchors.horizontalCenter: parent.horizontalCenter
            z:10
            color: "#a0a0a0"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            font.pixelSize: 14
        }
        Timer {
            id: calling
            repeat: true
            running: false
            interval: 10
            onTriggered: {
                parent.visible = true
                callingBar.value = callingBar.value + 0.01
                callerIdInd.visible = true
                answer.visible = true
                reject.visible = true
                if(callingBar.value >= 1) {
                    calling.running = 0
                    callingBar.value = 0
                    callerIdInd.visible = false
                    parent.visible = false
                    answer.visible = false
                    reject.visible = false
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
