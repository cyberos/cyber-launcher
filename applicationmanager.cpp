#include "applicationmanager.h"
#include "application.h"
#include <QtConcurrent/QtConcurrentRun>
#include <QFileSystemWatcher>
#include <QDebug>
#include <QIcon>

ApplicationManager::ApplicationManager(QObject *parent)
    : QAbstractListModel(parent)
{
    QtConcurrent::run(ApplicationManager::refresh, this);

    QFileSystemWatcher *watcher = new QFileSystemWatcher(this);
    watcher->addPath("/usr/share/applications");
    connect(watcher, &QFileSystemWatcher::directoryChanged, this, [this](const QString &) {
        QtConcurrent::run(ApplicationManager::refresh, this);
    });
}

ApplicationManager::~ApplicationManager()
{
    while (!m_apps.isEmpty())
        delete m_apps.takeFirst();
}

int ApplicationManager::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_apps.size();
}

QHash<int, QByteArray> ApplicationManager::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Qt::DisplayRole, "display");
    roles.insert(Qt::DecorationRole, "decoration");
    roles.insert(AppIdRole, "appId");
    roles.insert(ApplicationRole, "application");
    roles.insert(NameRole, "name");
    roles.insert(GenericNameRole, "genericName");
    roles.insert(CommentRole, "comment");
    roles.insert(IconNameRole, "iconName");
    roles.insert(CategoriesRole, "categories");
    roles.insert(FilterInfoRole, "filterInfo");
    roles.insert(PinnedRole, "pinned");
    roles.insert(PinnedIndexRole, "pinnedIndex");
    roles.insert(RunningRole, "running");
    roles.insert(StartingRole, "starting");
    roles.insert(ActiveRole, "active");
    roles.insert(HasWindowsRole, "hasWindows");
    roles.insert(HasCountRole, "hasCount");
    roles.insert(CountRole, "count");
    roles.insert(HasProgressRole, "hasProgress");
    roles.insert(ProgressRole, "progress");
    return roles;
}

QVariant ApplicationManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Application *app = m_apps.at(index.row());
    if (!app)
        return QVariant();

    switch (role) {
    case Qt::DecorationRole:
        return QIcon::fromTheme(app->iconName());
    case NameRole:
        return app->name();
    case IconNameRole:
        return app->iconName();
    case FilterInfoRole:
        return QString(app->name() + QStringLiteral(" ") + app->genericName() + QStringLiteral(" ") + app->comment());
    default:
        return QVariant();
    }
}

Application *ApplicationManager::findApplication(const QString &appId)
{
    for (Application *app : qAsConst(m_apps)) {
        if (app->appId() == appId)
            return app;
    }
    return nullptr;
}

Application *ApplicationManager::newApplication(const QString &appId)
{
    Application *app = new Application(appId, QStringList(), this);
    app->moveToThread(thread());
    m_apps.append(app);

    return app;
}

void ApplicationManager::refresh(ApplicationManager *manager)
{
    QStringList toRemove;
    for (Application *app : qAsConst(manager->m_apps))
        toRemove.append(app->appId());

    QStringList addedEntries;
    QDirIterator it("/usr/share/applications", {"*.desktop"}, QDir::NoFilter, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        const auto filename = it.next();
        if (!QFile::exists(filename))
            continue;

        if (addedEntries.contains(filename))
            continue;
        addedEntries.append(filename);

        if (!manager->findApplication(filename))
            QMetaObject::invokeMethod(manager, "addApp", Q_ARG(QString, filename));
    }

    for (const QString &appId : qAsConst(toRemove)) {
        Application *app = manager->findApplication(appId);
        if (app)
            QMetaObject::invokeMethod(manager, "removeApp", Q_ARG(QObject*, qobject_cast<QObject*>(app)));
    }

    // Signal the model was refreshed
    QMetaObject::invokeMethod(manager, "refreshed");
}

Application *ApplicationManager::get(int index) const
{
    if (index < 0 || index >= m_apps.size())
        return nullptr;

    return m_apps.at(index);
}

QString ApplicationManager::getIconName(const QString &appId)
{
    Application *app = get(indexFromAppId(appId));
    if (app)
        return app->iconName();

    return QString();
}

int ApplicationManager::indexFromAppId(const QString &appId) const
{
    for (int i = 0; i < m_apps.size(); i++) {
        if (m_apps.at(i)->appId() == appId)
            return i;
    }

    return -1;
}

bool ApplicationManager::launch(const QStringList &urls)
{

}

bool ApplicationManager::quit()
{

}

void ApplicationManager::addApp(const QString &appId)
{
    beginInsertRows(QModelIndex(), m_apps.count(), m_apps.count());

    Application *app = newApplication(appId);
    Q_EMIT applicationAdded(app);

    endInsertRows();
}

void ApplicationManager::removeApp(QObject *object)
{
    Application *app = qobject_cast<Application *>(object);
    if (!app)
        return;

    int index = m_apps.indexOf(app);
    if (index < 0)
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_apps.removeAt(index);
    endRemoveRows();

    Q_EMIT applicationRemoved(app);
    app->deleteLater();
}
