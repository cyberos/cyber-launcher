#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QtQml/QtQml>

#include "qqmlsortfilterproxymodel.h"
#include "iconthemeimageprovider.h"
#include "applicationmanager.h"
#include "application.h"
#include "launchermodel.h"
#include "pagemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("cyber-launcher"));
    app.setDesktopFileName(QStringLiteral("org.cyber.launcher"));

    QByteArray uri = "org.cyber.launcher";

    qmlRegisterAnonymousType<QAbstractItemModel>(uri, 1);
    qmlRegisterType<QQmlSortFilterProxyModel>(uri, 1, 0, "SortFilterProxyModel");
    qmlRegisterUncreatableType<Application>(uri, 1, 0, "Application", "cannot init application");
    qmlRegisterType<ApplicationManager>(uri, 1, 0, "ApplicationManager");
    qmlRegisterType<LauncherModel>(uri, 1, 0, "LauncherModel");
    qmlRegisterType<PageModel>(uri, 1, 0, "PageModel");

    QQmlApplicationEngine engine;
    QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.addImageProvider("icontheme", new IconThemeImageProvider);
    engine.load(url);

    return app.exec();
}
