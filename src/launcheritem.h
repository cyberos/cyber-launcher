#ifndef LAUNCHERITEM_H
#define LAUNCHERITEM_H

#include <QObject>

class LauncherItem : public QObject
{
    Q_OBJECT

public:
    explicit LauncherItem(QObject *parent = nullptr);

    QString id;
    QString name;
    QString genericName;
    QString comment;
    QString iconName;
    QStringList args;
};

#endif // LAUNCHERITEM_H
