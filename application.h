#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QSettings>
#include <QtQml>
#include <QtQml/QQmlListProperty>

class Application : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appId READ appId CONSTANT)
    Q_PROPERTY(QString name READ name NOTIFY dataChanged)
    Q_PROPERTY(QString genericName READ genericName NOTIFY dataChanged)
    Q_PROPERTY(QString comment READ comment NOTIFY dataChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY dataChanged)

public:
    explicit Application(const QString &appId, const QStringList &categories, QObject *parent = nullptr);

    QString name() const;
    QString genericName() const;
    QString comment() const;
    QString iconName() const;
    QStringList categories() const { return m_categories; }

    QString appId() { return m_appId; }

signals:
    void dataChanged();

private:
    QString m_name;
    QString m_genericName;
    QString m_comment;
    QString m_iconName;
    QString m_appId;
    QStringList m_categories;
    QSettings *m_desktop;
};

#endif // APPLICATION_H
