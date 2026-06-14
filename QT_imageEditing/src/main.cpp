#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <ImageController.h>
#include <FileManager.h>
#include <QUrl>
int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    ImageController imgController;

    
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    engine.rootContext()->setContextProperty("backendController", &imgController);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
