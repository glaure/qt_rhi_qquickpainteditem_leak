import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import my 1.0

Item {
    id: root
    width: 500; height: 440

    property var renderingMode: app.renderingMode
    property int lineNum: 0


    Label {
        text: renderingMode
    }

    QLineItem {
        id: myLine
        from: Qt.point(0, 20)
        to: Qt.point(500, 440)
    }

    Timer {
        interval: 5
        running: true
        repeat: true

        onTriggered: {
            switch (root.lineNum) {
            case 0:
                myLine.from = Qt.point(5, 20);
                myLine.to = Qt.point(500, 20);
                root.lineNum = 1
                break;
            case 1:
                myLine.from = Qt.point(500, 20);
                myLine.to = Qt.point(500, 440);
                root.lineNum = 2
                break;
            case 2:
                myLine.from = Qt.point(500, 440);
                myLine.to = Qt.point(5, 440);
                root.lineNum = 3
                break;
            case 3:
                myLine.from = Qt.point(5, 440);
                myLine.to = Qt.point(5, 20);
                root.lineNum = 0
                break;
            }

        }
    }
}
