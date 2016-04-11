import QtQuick 2.5
import Qt.labs.controls 1.0
import QtQuick.Layouts 1.3


ApplicationWindow {
    id: app
    visible: true
    width: 640
    height: 480
    title: qsTr("Yet Another NonoGrams")

    property int gridColls: 2
    property int gridCellWidth: app.width/gridColls

    property int gridRows: 4
    property int gridCellHeight: app.height/gridRows

    FontLoader {
        id: mandarinFont;
        source: "qrc:/MandarinC.ttf"
    }


    Timer {
        interval: 100; running: true;
        onTriggered:{
            //crosswords.source = "http://www.nonograms.ru/nonograms/size/small";
            //nonogramField.loadFromNonogramsOrg("http://www.nonograms.ru/nonograms/i/6940");
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

        ToolBar{
            height:app.height
            width: 120

            ColumnLayout{
                width: parent.width
                ToolButton{
                    text:"Small"
                    font.family: mandarinFont.name
                    font.pointSize: 20
                    onClicked: {
                        gridRows = 4;
                        crosswords.source = "http://www.nonograms.ru/nonograms/size/small";
                        drwr.close()
                    }
                }
                ToolButton{
                    text:"Medium"
                    font.family: mandarinFont.name
                    font.pointSize: 20
                    onClicked:{
                        gridRows = 3;
                        crosswords.source = "http://www.nonograms.ru/nonograms/size/medium";
                        drwr.close()
                    }
                }
                ToolButton{
                    text:"Large"
                    font.family: mandarinFont.name
                    font.pointSize: 20
                    onClicked: {
                        gridRows = 2;
                        crosswords.source = "http://www.nonograms.ru/nonograms/size/large";
                        drwr.close()
                    }
                }
            }
        }
    }

    Image{
        asynchronous: true
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source:"qrc:/lotos.jpg"
    }


    StackView{
        id: stack
        initialItem: cosswordsView
        anchors.fill: parent
    }

    GridView {
        id:cosswordsView
        model:crosswords
        height: parent.height
        width: parent.width

        cellWidth:  gridCellWidth
        cellHeight: gridCellHeight

        delegate:
            Item{
            width: gridCellWidth
            height: gridCellHeight
            Rectangle{
                anchors.centerIn: parent
                implicitWidth:content.width+40
                implicitHeight: content.height+40
                color:"#d7bb8b"
                Row {
                    id: content
                    anchors.centerIn: parent
                    spacing: 6
                    Image {
                        source:icon
                        asynchronous: true
                    }
                    Grid {
                        columns: 2
                        spacing: 2
                        Text {
                            text: qsTr("Date")
                        }

                        Text {
                            text:  date;
                        }

                        Text {
                            text: qsTr("Name:")
                        }

                        Text {
                            text: name
                        }

                        Text {
                            text: qsTr("Author")
                        }
                        Text{
                            text: author
                        }

                        Text {
                            text: qsTr("Size:")
                        }

                        Text {
                            text: size
                        }
                    }
                }
            }
        }

        ScrollIndicator.vertical: ScrollIndicator {
        }
        ScrollIndicator.horizontal: ScrollIndicator {
        }

    }

    Flickable{
        id: crossFlick
        height: parent.height
        width: parent.width
        contentWidth:nonogramField.width
        contentHeight:nonogramField.height
        ScrollIndicator.vertical: ScrollIndicator {
        }
        ScrollIndicator.horizontal: ScrollIndicator {
        }

        Item{
            implicitWidth: Math.max(nonogramField.width, app.width)
            implicitHeight: Math.max(nonogramField.height, app.height)

            Nonogram {
                id: nonogramField
                anchors.centerIn: parent
                ceilSize: 25
                fontSize: 18
                visible: true
            }
        }
    }
}
