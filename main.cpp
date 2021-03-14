#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "master_mind.h"
#include "guess_table.h"
#include "computer.h"
#include <QtQuick>
#include <time.h>
int main(int argc, char *argv[])
{
    srand(time(NULL));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<master_mind>("mm", 1, 0, "MasterMind");
    qmlRegisterType<guess_table>("mm", 1, 0, "GuessTable");
    qmlRegisterType<computer>("mm", 1, 0, "Computer");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
