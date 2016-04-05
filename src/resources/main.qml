import QtQuick 2.5
import Qt.labs.controls 1.0
import QtQuick.Layouts 1.3


ApplicationWindow {
    id: app
    visible: true
    width: 640
    height: 480
    title: qsTr("Yet Another NonoGrams")

    FontLoader {
        id: mandarinFont;
        source: "qrc:/MandarinC.ttf"
    }


    Timer {
        interval: 100; running: true;
        onTriggered:{
            nonogramField.loadFromNonogramsOrg("http://www.nonograms.ru/nonograms/i/6940");
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "Open"
                font.family: mandarinFont.name
                font.pointSize: 20
                onClicked: drwr.open()
            }
        }

        Text{
            anchors.centerIn: parent
            font.family: mandarinFont.name
            font.pointSize: 20
            text:"Yet Another NonoGrams"
        }
    }

    Drawer{
        id: drwr
        edge: Qt.LeftEdge

        Rectangle{
            height:app.height
            width: 120

            ColumnLayout{
                width: parent.width
                Button{
                    Layout.fillWidth: true
                    text:"Small"
                    font.family: mandarinFont.name
                    font.pointSize: 20
                    onClicked: drwr.close()
                }
                Button{
                    Layout.fillWidth: true
                    text:"Medium"
                    font.family: mandarinFont.name
                    font.pointSize: 20
                    onClicked: drwr.close()
                }
                Button{
                    Layout.fillWidth: true
                    text:"Large"
                    font.family: mandarinFont.name
                    font.pointSize: 20
                    onClicked: drwr.close()
                }
            }
        }
    }

    Nonogram {
        id: nonogramField
        ceilSize: 25
        fontSize: 18
        visible: true
        anchors.fill: parent
        width: parent.width;
        height: parent.height

    }
}
