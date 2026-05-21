#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "networkmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<NetworkManager>("Backend", 1, 0, "NetworkManager");
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("LanChat", "Main");

    return QGuiApplication::exec();
}
