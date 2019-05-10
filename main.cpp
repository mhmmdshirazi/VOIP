#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include "phone.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
/////////////////////user code
///
    phone *myPhone = new phone();
    engine.rootContext()->setContextProperty("phone",myPhone);

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    QObject::connect(myPhone,SIGNAL(onCalling(qint16)),window,SLOT(setTimer()));
///////////////////////////////
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
