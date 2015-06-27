#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/appcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    AppController appController;

    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("appController", &appController);

    appController.showPreparation();
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
