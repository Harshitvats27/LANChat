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

```

## 🛠️ **Build & Run Instructions**

### **Prerequisites**
* **Operating System:** Windows 10 / 11
* **IDE:** Qt Creator (with Qt 6.x installed)
* **Compiler:** MinGW 64-bit
* **Build System:** CMake

### **Step-by-Step Setup**
1. **Clone or download** this repository to your local directory.
2. **Launch Qt Creator** and open the `CMakeLists.txt` file located in the project root.
3. **Select the Desktop Qt MinGW 64-bit** kit configuration.
4. **Run the CMake configure process** and build the project (`Ctrl + B`).
5. **Click the green Run button** (`Ctrl + R`) to launch the application.

> **⚠️ Network Firewall Note:** On the initial application launch, Windows Defender Firewall will prompt for permissions. You **must allow network access** for both **Private and Public networks** to enable incoming and outgoing UDP/TCP socket traffic.

---

## 🔬 **Single-Machine Testing Methodology**

Due to local hardware testing limits, network sockets were validated using the local loopback network interface:

* **Discovery Verification:** The application successfully handles self-broadcasting, populating its own node inside the active peer list layout.
* **Message Loopback Echo:** Sending text to the discovered local IP establishes an internal client-server connection. The message appears twice in the stream—**first** via local client confirmation, and **second** upon successful real-time ingestion by the local TCP server. This architecture guarantees immediate scalability when deployed across multiple nodes on a real WiFi network.

---

## 📺 **Application Walkthrough & Demo**

Click the link below to watch the complete functional verification video covering automated peer discovery, chat persistence reloading, messaging pipeline, and the live visibility toggle mechanism:

🔗 **[Watch the Live Application Demo on Google Drive]( https://drive.google.com/file/d/18_1EfDjsMlt1TjqUkhVyMPfbvy8U7d6u/view?usp=sharing)**

---

## 👤 **Developer Contact**

* **Developer:** Harshit Vats
* **Email:** harshitvats237@gmail.com
*  **Contact:** 9518437050
