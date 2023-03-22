import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import Sponsorship 1.0

Item {
    id: view

    implicitWidth: layout.implicitWidth
    implicitHeight: layout.implicitHeight

    readonly property int sponsorId: badge2.studentId
    readonly property int sponsoredId: badge1.studentId

    function generateSponsorship()
    {
        badge1.studentId = -1;
        badge1.searching = true;
        badge2.studentId = Sponsorship.nextStudentId(2);

        generationTimer.id = Sponsorship.nextStudentId(1);
        generationTimer.start();
    }

    signal sponsorshipGenerated()

    RowLayout {
        id: layout

        readonly property size badgeImageSize: Qt.size(320, 240)

        spacing: Math.min(view.width, view.height) / 2

        anchors.fill: parent
        anchors.leftMargin: 32
        anchors.rightMargin: anchors.leftMargin

        StudentBadge {
            id: badge2

            studentLevel: 2
            imageSize: parent.badgeImageSize

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        SearchStudentBadget {
            id: badge1

            studentLevel: 1
            imageSize: parent.badgeImageSize

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Timer {
        id: generationTimer

        readonly property int loops: 50

        property int id

        function setRandom()
        {badge1.studentId = Sponsorship.randomStudentId(1);}

        function setSpecific()
        {
            badge1.studentId = id;
            badge1.searching = false;
        }

        interval: 1000
        repeat: false
        triggeredOnStart: false

        onTriggered: generationLoopingTimer.start()
    }

    Timer {
        id: generationLoopingTimer

        property int remainingLoops: generationTimer.loops

        interval: remainingLoops
        repeat: true

        onTriggered: {
            if (--remainingLoops != 0)
                generationTimer.setRandom();
            else {
                generationTimer.setSpecific();
                stop();

                remainingLoops = generationTimer.loops;

                view.sponsorshipGenerated();
            }
        }
    }
}
