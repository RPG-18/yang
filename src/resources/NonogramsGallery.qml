import QtQuick 2.0
import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0

ListView {
    id:view

    property int itemHeight: 160
    property int maxIconHeight: 150
    property int labelFontPixelSize: 18
    signal openNonogram(url itemUrl)

    model:crosswords

    delegate:
        Item{
        width:  app.width
        height: view.itemHeight

        RowLayout {
            id: content
            spacing: 6
            anchors.fill: parent

            Item{
                Layout.minimumWidth: 50
                Layout.maximumWidth: 50
            }

            Image {
                source:icon
                Layout.maximumHeight: view.maxIconHeight
                fillMode: Image.PreserveAspectFit
                asynchronous: true
            }

            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignVCenter
                columns: 4

                Text {
                    text: qsTr("Date")
                    font.family: mandarinFont.name
                    font.pixelSize: view.labelFontPixelSize
                }

                Text {
                    text:  date;
                    font.family: mandarinFont.name
                    font.pixelSize: view.labelFontPixelSize
                }

                Text {
                    text: qsTr("Name")
                    font.family: mandarinFont.name
                    font.pixelSize: view.labelFontPixelSize
                }

                Text {
                    text: name
                    font.pixelSize: view.labelFontPixelSize
                }

                Text {
                    text: qsTr("Author")
                    font.family: mandarinFont.name
                    font.pixelSize: view.labelFontPixelSize
                }
                Text{
                    text: author
                    font.pixelSize: view.labelFontPixelSize
                }

                Text {
                    text: qsTr("Size")
                    font.family: mandarinFont.name
                    font.pixelSize: view.labelFontPixelSize
                }

                Text {
                    text: size
                    font.family: mandarinFont.name
                    font.pixelSize: view.labelFontPixelSize
                }
            }

            Button{
                text:"Go"

                onClicked:{
                    openNonogram(url);
                }
            }
        }
    }

    ScrollIndicator.vertical: ScrollIndicator {
    }
    ScrollIndicator.horizontal: ScrollIndicator {
    }
}
