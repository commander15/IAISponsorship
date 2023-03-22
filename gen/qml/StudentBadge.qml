import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import QtGraphicalEffects 1.0

import Sponsorship 1.0

Item {
    id: badge

    property int studentId: -1
    property int studentLevel: -1

    readonly property url imageSource: Sponsorship.studentPhotoUrl(studentId, studentLevel)
    property size imageSize: Qt.size(320, 240)
    readonly property string name: Sponsorship.studentFirstName(studentId, studentLevel)

    property bool lastNameVisible: true

    implicitWidth: layout.implicitWidth
    implicitHeight: layout.implicitHeight

    ColumnLayout {
        id: layout

        spacing: 5

        anchors.fill: parent

        Image {
            id: img

            readonly property bool rounded: true
            readonly property bool adapt: true

            source: (badge.imageSource.toString().length > 0 ? badge.imageSource : "qrc:/qml/images/avatar.jpg")
            sourceSize: badge.imageSize
            fillMode: (roundImages ? Image.PreserveAspectCrop : Image.PreserveAspectFit)
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter

            layer.enabled: rounded
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: img.width
                    height: img.height

                    Rectangle {
                        anchors.centerIn: parent
                        width: img.adapt ? img.width : Math.min(img.width, img.height)
                        height: img.adapt ? img.height : width
                        radius: Math.min(width, height)
                    }
                }
            }

            Layout.preferredWidth: 400
            Layout.preferredHeight: 400
            Layout.alignment: Qt.AlignCenter
        }

        Label {
            text: (badge.name.length > 0 ? badge.name : "...")
            font.pointSize: 40
            font.bold: true

            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            readonly property string name: Sponsorship.studentLastName(badge.studentId, badge.studentLevel)

            text: (badge.lastNameVisible ? name : "")
            font.pointSize: 20

            Layout.alignment: Qt.AlignCenter
        }
    }
}
