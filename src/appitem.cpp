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
#include <QDebug>

AppItem::AppItem(const QString &appId, const QStringList &categories, QObject *parent)
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
