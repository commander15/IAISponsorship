import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import Sponsorship 1.0

Page {
    id: page

    function prepareSponsorshipGeneration()
    {
        if (Sponsorship.hasNextStudentId(1)) {
            saveButton.icon.color = "red";
            readyLabel.ready = true;
        }
    }

    function generateSponsorship()
    {
        readyLabel.ready = false;

        if (Sponsorship.hasNextStudentId(1))
            view.generateSponsorship();
        else
            page.finished();
    }

    signal finished()

    Image {
        source: "qrc:/qml/images/iai.png"
        fillMode: Image.PreserveAspectFit

        x: (page.width / 2) - (width / 2)
        y: 0
    }

    ColumnLayout {
        x: view.x + (view.width / 2) - (width / 2)
        y: view.y + (view.height / 2)
        width: 256
        height: 16

        Label {
            text: "Parainage"
            font.pointSize: 32
            font.bold: true
            Layout.alignment: Qt.AlignCenter
        }

        Rectangle {
            color: "orange"
            radius: 12

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 16
        }
    }

    ColumnLayout {
        id: layout

        readonly property double ratio: 1 / 10

        anchors.fill: parent

        SponsorshipView {
            id: view

            onSponsorshipGenerated: saveButton.icon.color = (Sponsorship.saveSponsorship(view.sponsorId, view.sponsoredId) ? "green" : "red")

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: page.height * layout.ratio
        }

        Label {
            id: readyLabel

            property bool ready: false

            text: (ready ? "Ready !" : "")

            font.pointSize: 22
            font.bold: true

            Layout.preferredHeight: font.pixelSize
            Layout.alignment: Qt.AlignCenter
        }

        Row {
            spacing: page.width * layout.ratio

            Layout.alignment: Qt.AlignCenter
            Layout.bottomMargin: page.height * layout.ratio

            RoundButton {
                id: saveButton

                icon.source: "qrc:/qml/icons/save.png"
                icon.color: "red"
                focus: false
            }
        }
    }
}
