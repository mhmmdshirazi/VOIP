import QtQuick 2.0
import QtQuick.Controls 2.5
Item {
    id: element
    TextField {
        id: myPhoneNumber
        x: 88
        y: 89
        inputMethodHints: Qt.ImhFormattedNumbersOnly
        placeholderText: "Your Phone Number"
        clip: false
    }

    RoundButton {
        id: savePhoneNumber
        x: 306
        y: 89
        text: "Save"
    }

    Text {
        text: "Your phone Number is: "
        anchors.top: myPhoneNumber.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

/*##^## Designer {
    D{i:0;autoSize:true}
}
 ##^##*/
