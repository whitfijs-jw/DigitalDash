#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFont>
#include <QFontDatabase>
#include <QList>

#include <config.h>

#ifdef RASPBERRY_PI
#include <dash.h>
#else
#include <dash_host.h>
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/HandelGothReg.ttf");
    QFont mFont;
    mFont.setFamily("Handel Gothic");
    app.setFont(mFont);

    //Setup QML
    QQmlApplicationEngine engine;
    QQmlContext * ctxt = engine.rootContext();

    // Initialize Dash
#ifdef RASPBERRY_PI
    Dash * dash = new Dash(&app, ctxt);
#else
    DashHost * dash = new DashHost(&app, ctxt);
#endif
    dash->init();

    // load main.qml
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // connect quit
    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));

    // Start Dash
    dash->start();

    return app.exec();
}
