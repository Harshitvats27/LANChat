# LANChat: Peer-to-Peer Local WiFi Chat Application

A high-performance, serverless local area network (LAN) peer-to-peer chat application built using **C++17** and the **Qt 6 Framework** (Qt Quick/QML). This application enables users connected to the same WiFi network to dynamically discover each other, toggle network visibility, and engage in real-time direct private messaging without requiring a centralized server.

---

## 🚀 Key Features

* **Dynamic UDP Discovery:** Utilizes `QUdpSocket` broadcasting on port `45454` to automatically discover and list active peers across the local network mesh.
* **Visibility Toggle (ON/OFF):** Features an active presence management system using `QTimer`. Toggling visibility off stops the heartbeat broadcast and transmits an explicit `OFFLINE` datagram to instantly clear the user from neighboring peer lists.
* **Direct TCP Messaging:** Establishes independent peer-to-peer `QTcpSocket` channels on port `45455` for reliable, low-latency, real-time message delivery.
* **Local History Persistence:** Automatically serializes chat threads to a local flat-file storage (`chat_history.txt`) using `QFile` and `QTextStream`, ensuring complete historical reload upon application restart.
* **Clean Architectural Separation:** Strictly decouples the QML asynchronous user interface from the C++ networking backbone using Qt's Meta-Object System (Signals and Slots).

---

## 📂 Project Structure

```text
/LANChat
 ├── CMakeLists.txt        # Build system configuration
 ├── include/              # Core C++ header files
 │    └── networkmanager.h
 ├── src/                  # Core C++ source implementations
 │    ├── main.cpp
 │    └── networkmanager.cpp
 └── ui/                   # QML declarative user interface layout
      └── Main.qml
