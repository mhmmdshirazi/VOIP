#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include "phone.h"
#include <QStandardPaths>
#include <QFile>
#include <QDir>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
/////////////////////user code
///
    phone *myPhone = new phone();
    engine.rootContext()->setContextProperty("audio",myPhone);
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    auto fileName= path + "/myfile.txt";
    QDir _dir;
    // check if "scripts" folder exists
    int _dirExists = _dir.exists(path);
    // if not, create it
    if( !_dirExists )
        _dir.mkpath(path);

    QFile myFile(fileName);
    if ( myFile.open(QIODevice::ReadWrite) )
    {
        qDebug("open shod");
        QTextStream stream( &myFile );
        //stream << "something" << endl;
        qDebug() << stream.readAll();
    }

///////////////////////////////
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
