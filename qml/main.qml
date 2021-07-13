import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import my 1.0

Item {
    id: root
    width: 500; height: 440

    property var renderingMode: app.renderingMode
    property int lineNum: 0

    property var from: Qt.point(0, 20)
    property var to: Qt.point(500, 440)

    Label {
        text: renderingMode
    }


    // create 100 Line Items
    Repeater {
        model : 100

        QLineItem {
            from: root.from
            to: root.to
        }
    }

    function drawRectangle(count)
    {
        switch (root.lineNum) {
        case 0:
            root.from = Qt.point(5, 20);
            root.to = Qt.point(500, 20);
            root.lineNum = 1
            break;
        case 1:
            root.from = Qt.point(500, 20);
            root.to = Qt.point(500, 440);
            root.lineNum = 2
            break;
        case 2:
            root.from = Qt.point(500, 440);
            root.to = Qt.point(5, 440);
            root.lineNum = 3
            break;
        case 3:
            root.from = Qt.point(5, 440);
            root.to = Qt.point(5, 20);
            root.lineNum = 0
            break;
        }
    }

    Timer {
        interval: 5
        running: true
        repeat: true

        onTriggered: {
            drawRectangle(100)
        }
    }
}
