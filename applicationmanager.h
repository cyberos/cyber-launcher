#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include <QLoggingCategory>
#include <QAbstractListModel>

class Application;
class ApplicationManager : public QAbstractListModel
{
    Q_OBJECT

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

    explicit ApplicationManager(QObject *parent = nullptr);
    ~ApplicationManager();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Application *findApplication(const QString &appId);
    Application *newApplication(const QString &appId);

    static void refresh(ApplicationManager *manager);

    Q_INVOKABLE Application *get(int index) const;

    Q_INVOKABLE QString getIconName(const QString &appId);
    Q_INVOKABLE int indexFromAppId(const QString &appId) const;

public Q_SLOTS:
    Q_INVOKABLE bool launch(const QStringList &urls);
    Q_INVOKABLE bool quit();

    Q_INVOKABLE bool launch() { return launch(QStringList()); }

Q_SIGNALS:
    void refreshed();
    void applicationAdded(Application *app);
    void applicationRemoved(Application *app);
    void applicationLaunched(Application *app);

private Q_SLOTS:
    void addApp(const QString &appId);
    void removeApp(QObject *object);

private:
    QList<Application *> m_apps;
};

#endif // APPLICATIONMANAGER_H
