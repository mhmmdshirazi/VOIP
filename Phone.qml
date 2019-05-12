import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
Item {
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
            callingCounterTimer.running = true
            callingCounterTimer.restart()
        }
        Timer {
            id: callingCounterTimer
            interval: 50
            repeat: true
            running: false
            property int callCounter: 0
            onTriggered: {
                phone.requestCall(phoneNumber.text)
                callCounter = callCounter +1
                console.log(phone.getCallState());
                if (callCounter > 500 || phone.getCallState() != 0) {
                    callCounter = 0
                    running = false
                }
            }
        }
    }



}





/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
