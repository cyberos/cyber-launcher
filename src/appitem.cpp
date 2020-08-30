/*
 * Copyright (C) 2020 CyberOS.
 *
 * Author:     revenmartin <revenmartin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "appitem.h"
#include "desktopproperties.h"
#include <QDebug>

static QByteArray detectDesktopEnvironment()
{
    const QByteArray desktop = qgetenv("XDG_CURRENT_DESKTOP");

    if (!desktop.isEmpty())
        return desktop.toUpper();

    return QByteArray("UNKNOWN");
}

AppItem::AppItem(QObject *parent)
    : QObject(parent),
      m_isValid(false)
{
}

void AppItem::load(const QString &fileName)
{
    m_appId = fileName;

    const QString env = detectDesktopEnvironment();
    DesktopProperties desktop(fileName, "Desktop Entry");
    if (desktop.contains("OnlyShowIn")) {
        const QString &value = desktop.value("OnlyShowIn").toString();
        if (!value.contains(env, Qt::CaseInsensitive)) {
            return;
        }
    }

    if (desktop.value("NoDisplay").toBool() ||
        desktop.value("Hidden").toBool())
        return;

    QString appName = desktop.value(QString("Name[%1]").arg(QLocale::system().name())).toString();
    QString appExec = desktop.value("Exec").toString();

    if (appName.isEmpty())
        appName = desktop.value("Name").toString();


    appExec.remove(QRegularExpression("%."));
    appExec.remove(QRegularExpression("^\""));
    // appExec.remove(QRegularExpression(" *$"));
    appExec = appExec.simplified();

    m_name = appName;
    m_iconName = desktop.value("Icon").toString();
    m_genericName = desktop.value("GenericName").toString();
    m_comment = desktop.value("Comment").toString();
    m_args = appExec.split(" ");
    m_isValid = true;

    qDebug() << appName << appExec.split(" ");

    emit loadFinished(this);
}

bool AppItem::isValid()
{
    return m_isValid;
}

QString AppItem::name() const
{
    return m_name;
}

QString AppItem::genericName() const
{
    return m_genericName;
}

QString AppItem::comment() const
{
    return m_comment;
}

QString AppItem::iconName() const
{
    return m_iconName;
}

QStringList AppItem::args() const
{
    return m_args;
}

