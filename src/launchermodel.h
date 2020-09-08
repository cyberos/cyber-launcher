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

#ifndef LAUNCHERMODEL_H
#define LAUNCHERMODEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QAbstractListModel>

class LauncherItem;
class LauncherModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum Roles
    {
        AppIdRole = Qt::UserRole + 1,
        ApplicationRole,
        NameRole,
        GenericNameRole,
        CommentRole,
        IconNameRole,
        CategoriesRole,
        FilterInfoRole,
        PinnedRole,
        PinnedIndexRole,
        RunningRole,
        StartingRole,
        ActiveRole,
        HasWindowsRole,
        HasCountRole,
        CountRole,
        HasProgressRole,
        ProgressRole,
        ActionsRole
    };
    Q_ENUM(Roles)

    explicit LauncherModel(QObject *parent = nullptr);
    ~LauncherModel();

    int count() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    LauncherItem *findApplication(const QString &appId);

    static void refresh(LauncherModel *manager);

    Q_INVOKABLE LauncherItem *get(int index) const;

    Q_INVOKABLE QString getIconName(const QString &appId);
    Q_INVOKABLE int indexFromAppId(const QString &appId) const;

public Q_SLOTS:
    Q_INVOKABLE bool launch(const QString &path);
    Q_INVOKABLE bool launch() { return launch(QString()); }

Q_SIGNALS:
    void countChanged();
    void refreshed();
    void applicationAdded(LauncherItem *app);
    void applicationRemoved(LauncherItem *app);
    void applicationLaunched();

private Q_SLOTS:
    void addApp(const QString &fileName);
    void removeApp(QObject *object);

private:
    QList<LauncherItem *> m_apps;
};

#endif // LAUNCHERMODEL_H
