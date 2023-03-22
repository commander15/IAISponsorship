import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQuick.Window 2.14

ApplicationWindow {
    id: win

    title: "IAI Sponsorship 1.0"
    x: 0
    y: 0
    width: 800
    height: 400
    visibility: ApplicationWindow.FullScreen
    visible: true
    background: Rectangle { color: "light yellow" }

    PropertyAnimation on x {
        id: winXAnimation

        to: (Screen.width / 2) - (win.width / 2)
        duration: 500
    }

    PropertyAnimation on y {
        id: winYAnimation

        to: (Screen.height / 2) - (win.height / 2)
        duration: 1000
    }

    StackView {
        id: stack

        initialItem: loadingPage
        focus: true

        anchors.fill: parent
    }

    MouseArea {
        acceptedButtons: Qt.NoButton
        cursorShape: Qt.BlankCursor

        anchors.fill: parent
    }

    Component {
        id: loadingPage

        ColumnLayout {
            spacing: 5

            Image {
                source: "qrc:/qml/images/iai.png"
                fillMode: Image.PreserveAspectFit

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            BusyIndicator {
                id: busyIndicator

                readonly property int size: 80

                running: true

                Layout.minimumWidth: size
                Layout.minimumHeight: size
                Layout.alignment: Qt.AlignCenter
                Layout.bottomMargin: 16
            }

            Timer {
                interval: 5000
                repeat: false
                running: true

                onTriggered: stack.replace(generationPage)
            }
        }
    }

    Component {
        id: generationPage

        GenerationPage {
            property bool prepared: false

            background: win.background
            focus: true

            Keys.onSpacePressed: {
                if (!prepared) {
                    prepareSponsorshipGeneration();
                    prepared = true;
                } else {
                    generateSponsorship();
                    prepared = false;
                }
            }

            onFinished: stack.replace(endPage)
        }
    }

    Component {
        id: endPage

        Image {
            source: "qrc:/qml/images/iai.png"
            fillMode: Image.PreserveAspectFit
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter

            Timer {
                interval: 1000
                repeat: false
                running: true

                onTriggered: win.visibility = ApplicationWindow.Windowed
            }

            Timer {
                interval: 1500
                repeat: false
                running: true

                onTriggered: {
                    winXAnimation.start();
                    winYAnimation.start();
                }
            }
        }
    }
}
