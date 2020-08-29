#include "application.h"
#include <QDebug>

Application::Application(const QString &appId, const QStringList &categories, QObject *parent)
    : QObject(parent),
      m_appId(appId),
      m_categories(categories)
{
//    QString fileName = QStandardPaths::locate(QStandardPaths::ApplicationsLocation,
//                                              appId + QStringLiteral(".desktop"));
    QSettings desktop(appId, QSettings::IniFormat);
    desktop.beginGroup("Desktop Entry");
    m_name = desktop.value("Name").toString();
    m_genericName = desktop.value("GenericName").toString();
    m_comment = desktop.value("Comment").toString();
    m_iconName = desktop.value("Icon").toString();
}

QString Application::name() const
{
    return m_name;
}

QString Application::genericName() const
{
    return m_genericName;
}

QString Application::comment() const
{
    return m_comment;
}

QString Application::iconName() const
{
    return m_iconName;
}
