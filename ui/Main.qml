import QtQuick
import QtQuick.Controls
import Backend 1.0

Window {
    width: 650
    height: 550
    visible: true
    title: "P2P Local WiFi Chat Application"

    property string selectedIp: ""
    property string selectedName: ""
    property string myName: ""
    property bool isVisibleOnNet: false

    NetworkManager {
        id: networkManager

        onUserFound: function(ipAddress, username) {
            var exists = false;
            for (var i = 0; i < userModel.count; i++) {
                if (userModel.get(i).ip === ipAddress) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                userModel.append({"name": username, "ip": ipAddress})
            }
        }

        onUserLeft: function(ipAddress) {
            for (var i = 0; i < userModel.count; i++) {
                if (userModel.get(i).ip === ipAddress) {
                    userModel.remove(i);
                    break;
                }
            }
            if (selectedIp === ipAddress) {
                selectedIp = "";
                selectedName = "";
            }
        }

        onMessageReceived: function(messageDisplay) {
            chatDisplay.text += messageDisplay + "\n"
        }
    }

    Component.onCompleted: {
        var history = networkManager.loadChatHistory();
        if (history !== "") {
            chatDisplay.text = history + "\n--- [System]: Previous Chat History Loaded ---\n\n"
        }
    }

    ListModel {
        id: userModel
    }

    Row {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 15

        // ================= LEFT COLUMN =================
        Column {
            width: 220
            height: parent.height
            spacing: 12

            Text {
                text: "Your Profile"
                font.bold: true
                font.pixelSize: 14
            }

            TextField {
                id: nameInput
                placeholderText: "Enter your nickname..."
                width: parent.width
                onTextChanged: myName = text
            }

            Button {
                text: isVisibleOnNet ? "Visibility: ON (Click to Turn OFF)" : "Enable My Visibility"
                width: parent.width
                palette.buttonText: isVisibleOnNet ? "green" : "black"

                onClicked: {
                    if (nameInput.text !== "") {
                        isVisibleOnNet = !isVisibleOnNet;
                        networkManager.setVisibility(nameInput.text, isVisibleOnNet);
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: 1
                color: "#D0D0D0"
            }

            Text {
                text: "Online Users"
                font.bold: true
                font.pixelSize: 14
            }

            ScrollView {
                width: parent.width
                height: 300
                clip: true

                ListView {
                    id: userListView
                    model: userModel
                    width: parent.width
                    spacing: 5

                    delegate: ItemDelegate {
                        width: userListView.width
                        highlighted: selectedIp === model.ip

                        contentItem: Text {
                            text: "🟢 " + model.name + "\n     IP: " + model.ip
                            font.pixelSize: 13
                            color: highlighted ? "white" : "black"
                        }

                        onClicked: {
                            selectedIp = model.ip
                            selectedName = model.name
                        }
                    }
                }
            }
        }

        Rectangle {
            width: 1
            height: parent.height
            color: "#D0D0D0"
        }

        // ================= RIGHT COLUMN =================
        Column {
            width: parent.width - 250
            height: parent.height
            spacing: 10

            Text {
                text: selectedName !== "" ? "💬 Chatting with: " + selectedName + " (" + selectedIp + ")" : "⚠️ Select a user from the list to start chatting"
                font.bold: true
                font.pixelSize: 14
                color: selectedName !== "" ? "#0066CC" : "gray"
            }

            ScrollView {
                width: parent.width
                height: 400
                clip: true

                background: Rectangle {
                    border.color: "lightgray"
                    radius: 4
                    color: "#FAFAFA"
                }

                TextArea {
                    id: chatDisplay
                    readOnly: true
                    selectByMouse: true
                    wrapMode: TextEdit.Wrap
                    font.pixelSize: 13


                    onTextChanged: {
                        cursorPosition = length
                    }
                }
            }

            Row {
                width: parent.width
                spacing: 10

                TextField {
                    id: messageInput
                    placeholderText: "Type a text message here..."
                    width: parent.width - 90
                    enabled: selectedIp !== "" && myName !== ""
                    onAccepted: sendBtn.clicked()
                }

                Button {
                    id: sendBtn
                    text: "Send"
                    width: 80
                    enabled: selectedIp !== "" && myName !== "" && messageInput.text !== ""
                    palette.button: "#25D366"
                    palette.buttonText: "black"
                    onClicked: {
                        networkManager.sendMessage(selectedIp, myName, messageInput.text)
                        messageInput.text = ""
                    }
                }
            }
        }
    }
}