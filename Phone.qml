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

    Button {
        id: start
        x: 138
        y: 178
        text: qsTr("Start Read")
        onClicked: {
            phone.startAudioRead()
        }
    }

    ProgressBar {
        id: progressBar
        x: 88
        y: 277
        value: 0.5
    }

    Button {
        id: stop
        x: 134
        y: 323
        text: qsTr("Start Play back")
        onClicked: {
            phone.stopAndPlay()
        }
    }

    TextField {
        id: phoneNumber
        x: 88
        y: 395
        placeholderText: "Phone Number"
        //text: qsTr("Enter Phone Number")
        clip: false
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }

    RoundButton {
        id: call
        x: 306
        y: 395
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
