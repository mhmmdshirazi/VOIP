import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
Window {
    visible: true
    width: 375
    height: 667
    title: qsTr("phone over ip")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        Phone {

        }
        Settings {

        }
    }

}







/*##^## Designer {
    D{i:0;height:667;width:375}
}
 ##^##*/
