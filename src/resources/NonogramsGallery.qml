import QtQuick 2.0
import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0

ListView {
    id:view

    property int itemHeight: 170
    property int maxIconHeight: 120
    property int labelFontPixelSize: 18
    signal openNonogram(url itemUrl)

    model:crosswords

    delegate:
        Item{
        width:  app.width
        height: view.itemHeight

        Image {
            id: name
            anchors.centerIn: parent
            width: parent.width*0.98
            height: parent.height*0.98
            source: "qrc:/paper.jpg"
            asynchronous: true
        }

        ColumnLayout{
            anchors.fill: parent
            Text {
                Layout.alignment: Qt.AlignCenter
                text: nonogram;
                font.family:  hanZiFont.name
                font.pixelSize: view.labelFontPixelSize
            }

            RowLayout {
                id: content
                spacing: 6
                Layout.fillWidth: true
                Layout.fillHeight: true


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
                    columns: 2

                    Text {
                        text: qsTr("Author")
                        font.family: hanZiFont.name
                        font.pixelSize: view.labelFontPixelSize
                    }
                    Text{
                        text: author
                        font.family:  hanZiFont.name
                        font.pixelSize: view.labelFontPixelSize
                    }

                    Text {
                        text: qsTr("Size")
                        font.family: hanZiFont.name
                        font.pixelSize: view.labelFontPixelSize
                    }

                    Text {
                        text: size
                        font.family: hanZiFont.name
                        font.pixelSize: view.labelFontPixelSize
                    }
                }
            }
        }

        Text {
            anchors{
                right: parent.right
                bottom:parent.bottom
                margins: 20
            }

            text:  date;
            font.family:  hanZiFont.name
            font.pixelSize: view.labelFontPixelSize
        }

        Button{
            text:"Go"

            anchors{
                right: parent.right
                verticalCenter: parent.verticalCenter
                margins: 20
            }

            onClicked:{
                openNonogram(url);
            }
        }
    }

    ScrollIndicator.vertical: ScrollIndicator {
    }
    ScrollIndicator.horizontal: ScrollIndicator {
    }
}
