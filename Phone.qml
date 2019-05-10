import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
Item {

    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange

    Timer {
        interval: 16
        running: true
        repeat: true
        onTriggered: {

        }
    }

    TextField {
        id: phoneNumber
//        focusChanged: {
//            InputMethod.hide()
//        }

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height * 0.2
        placeholderText: "Phone Number"
        //text: qsTr("Enter Phone Number")
        clip: false
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }

    RoundButton {
        id: call
        anchors.verticalCenter: phoneNumber.verticalCenter
        anchors.left: phoneNumber.right
        anchors.leftMargin: 50
        text: "Call"
        onClicked: {
            phone.requestCall(phoneNumber.text)
        }
    }



}





/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
