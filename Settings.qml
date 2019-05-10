import QtQuick 2.0
import QtQuick.Controls 2.5
Item {
    id: element

    TextField {
        id: myPhoneNumber
        x: 88
        y: 89
        inputMethodHints: Qt.ImhFormattedNumbersOnly
        placeholderText: qsTr("New phone Number?")
        clip: false
    }

    RoundButton {
        id: savePhoneNumber
        x: 306
        y: 89
        text: "Save"
        onClicked: {
            phone.savePhoneNumber(myPhoneNumber.text)
            currentPhoneNumber.text = qsTr("Your current phone number is: %1").arg(myPhoneNumber.text)
        }
    }

    Text {
        color:"#F0F0F0"
        id: currentPhoneNumber
        property int phoneNumber: phone.loadPhoneNumber()
        text: qsTr("Your current phone number is: %1").arg(phoneNumber)
        anchors.top: myPhoneNumber.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

/*##^## Designer {
    D{i:0;autoSize:true}
}
 ##^##*/
