import QtQuick 2.0
import QtQuick.Controls 2.5
Item {

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
            audio.startAudioRead()
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
            audio.stopAndPlay()
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
            audio.requestCall(phoneNumber.text)
        }
    }



}
