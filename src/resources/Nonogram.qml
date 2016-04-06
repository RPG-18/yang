import QtQuick 2.5

Item {
    clip:true
    property int margin: 20
    property int fontSize:  12
    property int ceilSize:  20;
    property int incCeilSize: ceilSize + 1

    property int rows:       0;
    property int rowSize:    0;

    property int column:     0;
    property int columnSize: 0;


    implicitHeight : crossGrid.height+margin*2
    implicitWidth : crossGrid.width+margin*2

    Image{
        asynchronous: true
        /*
        sourceSize.width: parent.width
        sourceSize.height: parent.height
        */

        fillMode: Image.PreserveAspectCrop
        source:"qrc:/wall-paper.jpg"
    }


    function loadFromNonogramsOrg(url) {
        crossword.formNanogramsOrg(url);
    }

    function showOnlyNaturalNumber(val)
    {
        return val > 0 ? val: " ";
    }

    function drawCrossword(){
        var csize = crossword.size;
        if(csize.column() === 0 || csize.rows() === 0){
            return;
        }

        rowSize = crossword.rowSize();
        columnSize = crossword.columnSize();

        rows = csize.rows();
        column = csize.column();

        hRepeater.model = crossword.columnSize()*csize.column();
        rRepeater.model = crossword.rowSize()*csize.rows();


    }

        Grid {
            anchors.centerIn: parent
            id: crossGrid
            columns: 2
            spacing: 2
            rowSpacing: 0
            columnSpacing: 0

            Rectangle{
                id:topLeftItm
                width: rowSize * ceilSize
                height:columnSize * ceilSize
                border.width: 1
                color: "transparent"
            }

            Grid {
                id: cGrid
                rows: columnSize
                columns: column

                Repeater {
                    id: hRepeater
                    model: 0
                    Item {
                        width: ceilSize; height: ceilSize
                        property int rw : Math.floor(index/column)
                        property int cn : Math.floor(index%column)
                        property int prw: rw+1
                        property int pcm: cn+1

                        Rectangle{
                            height: (prw % 5 == 0) || (prw == columnSize) ? ceilSize : incCeilSize
                            width:  (pcm % 5 == 0)  ? ceilSize : incCeilSize
                            color: "transparent"
                            border.width: 1
                            Text {
                                anchors.centerIn: parent
                                text:showOnlyNaturalNumber(
                                         crossword.columnValue(cn,rw));
                                font{
                                    family: mandarinFont.name
                                    pixelSize: fontSize
                                }
                            }
                        }
                    }
                }
            }

            Grid {
                id: rGrid
                rows: rows
                columns: rowSize

                Repeater {
                    id: rRepeater
                    model: 0
                    Item {
                        width: ceilSize; height: ceilSize
                        property int rw : Math.floor(index/rowSize)
                        property int cn : Math.floor(index%rowSize)
                        property int prw: rw+1
                        property int pcn: cn+1

                        Rectangle{
                            height: prw % 5 == 0 ? ceilSize : incCeilSize
                            width:  (pcn % 5 == 0) || (pcn == rowSize)
                                    ? ceilSize : incCeilSize

                            color: "transparent"

                            border.width: 1
                            Text {
                                anchors.centerIn: parent
                                text:showOnlyNaturalNumber(
                                         crossword.rowValue(rw,cn));
                                font{
                                    family: mandarinFont.name
                                    pixelSize: fontSize
                                }
                            }
                        }
                    }
                }
            }

            Rectangle{
                width: column * ceilSize
                height:rows   * ceilSize
                border.width: 1
                color: "transparent"

                Grid{
                    rows: rows
                    columns:column
                    Repeater {
                        id: bRepeater
                        model: rows * column
                        Item {
                            id: ceilItm
                            width: ceilSize; height: ceilSize
                            property int rw : Math.floor(index/column)
                            property int cn : Math.floor(index%column)

                            state: "default"

                            Rectangle{
                                id: itmRec
                                height: (rw+1) % 5 == 0 ? ceilSize : incCeilSize
                                width: (cn+1) % 5 == 0  ? ceilSize : incCeilSize

                                color: "transparent"

                                border.width: 1
                            }

                            Text{
                                id: itmTxt
                                visible:false
                                height: parent.height
                                width: parent.width
                                font.pixelSize: ceilSize
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment:   Text.AlignVCenter
                                text:"+"
                                rotation:45
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if(parent.state == "default"){
                                        parent.state = "SHADED";
                                    }else if(parent.state == "SHADED"){
                                        parent.state = "CLEAR";
                                    }else{
                                        parent.state = "default";
                                    }

                                }
                            }

                            states: [
                                State{
                                    name:"SHADED"
                                    PropertyChanges {
                                        target: itmRec; color: "black";
                                    }
                                    PropertyChanges {
                                        target: itmTxt; visible: false;
                                    }
                                },
                                State{
                                    name:"CLEAR"
                                    PropertyChanges {
                                        target: itmRec; color: "transparent";
                                    }
                                    PropertyChanges {
                                        target: itmTxt; visible: true;
                                    }
                                }
                            ]
                        }
                    }
                }
            }
        }

    Connections {
        target: crossword
        onLoaded: {
            drawCrossword();
        }
    }

}
