#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include "audio.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
/////////////////////user code
///
    audio *myAudio = new audio();
    engine.rootContext()->setContextProperty("audio",myAudio);

///////////////////////////////
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
