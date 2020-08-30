#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "applicationmanager.h"

class Launcher : public QGuiApplication
{
    Q_OBJECT

public:
    Launcher(int &argc, char **argv);

    void show();
    void hide();
    void toggle();

private:
    QQmlApplicationEngine *m_engine;
};

#endif // LAUNCHER_H
