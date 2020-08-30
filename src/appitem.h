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

#ifndef APPITEM_H
#define APPITEM_H

#include <QObject>
#include <QtQml>
#include <QtQml/QQmlListProperty>

class AppItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appId READ appId CONSTANT)
    Q_PROPERTY(QString name READ name NOTIFY dataChanged)
    Q_PROPERTY(QString genericName READ genericName NOTIFY dataChanged)
    Q_PROPERTY(QString comment READ comment NOTIFY dataChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY dataChanged)
    Q_PROPERTY(QStringList args READ args NOTIFY dataChanged)

public:
    explicit AppItem(QObject *parent = nullptr);

    void load(const QString &fileName);
    bool isValid();

    QString name() const;
    QString genericName() const;
    QString comment() const;
    QString iconName() const;
    QStringList args() const;
    QStringList categories() const { return m_categories; }

    QString appId() { return m_appId; }

signals:
    void dataChanged();
    void loadFinished(AppItem *item);

private:
    bool m_isValid;
    QString m_name;
    QString m_genericName;
    QString m_comment;
    QString m_iconName;
    QString m_appId;
    QStringList m_args;
    QStringList m_categories;
    QSettings *m_desktop;
};

#endif // APPITEM_H
