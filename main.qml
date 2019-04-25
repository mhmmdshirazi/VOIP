import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Timer {
        interval: 16
        running: true
        repeat: true
        onTriggered: {

        }
    }

    Button {
        id: start
        x: 223
        y: 208
        text: qsTr("Start Read")
        onClicked: {
            audio.startAudioRead()
        }
    }

    ProgressBar {
        id: progressBar
        x: 173
        y: 292
        value: 0.5
    }

    Button {
        id: stop
        x: 223
        y: 335
        text: qsTr("Start Play back")
        onClicked: {
            audio.stopAndPlay()
        }
    }


}
