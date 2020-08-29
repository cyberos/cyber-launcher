#include "launcher.h"
#include "launcheradaptor.h"
#include "iconthemeimageprovider.h"

#include <QDBusConnection>

#include <QQmlApplicationEngine>
#include <QQmlContext>

Launcher::Launcher(int &argc, char **argv)
  : QGuiApplication(argc, argv),
    m_engine(new QQmlApplicationEngine(this))
{
    new LauncherAdaptor(this);

    m_engine->addImageProvider("icontheme", new IconThemeImageProvider);
    m_engine->load(QUrl(QLatin1String("qrc:/qml/main.qml")));
}

void Launcher::show()
{
    QMetaObject::invokeMethod(m_engine->rootObjects().first(), "show");
}

void Launcher::hide()
{
    QMetaObject::invokeMethod(m_engine->rootObjects().first(), "hide");
}

void Launcher::toggle()
{
    QMetaObject::invokeMethod(m_engine->rootObjects().first(), "toggle");
}