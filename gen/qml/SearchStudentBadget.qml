import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import Sponsorship 1.0

StudentBadge {
    id: badge

    property bool searching: false

    lastNameVisible: !searching

    BusyIndicator {
        anchors.centerIn: parent

        running: badge.searching
        width: badge.width / 2
        height: badge.height / 2
    }
}
