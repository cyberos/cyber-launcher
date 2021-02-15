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

#include "launcher.h"
#include "launcheradaptor.h"
#include "iconthemeimageprovider.h"

#include <QDBusConnection>
#include <QQmlContext>
#include <QScreen>

#include <KWindowSystem>

Launcher::Launcher(QQuickView *w)
  : QQuickView(w)
{
    m_screenAvailableWidth = qApp->primaryScreen()->availableGeometry().width();
    m_screenAvailableHeight = qApp->primaryScreen()->availableGeometry().height();

    new LauncherAdaptor(this);

    engine()->rootContext()->setContextProperty("launcher", this);

    setFlags(Qt::FramelessWindowHint);
    setResizeMode(QQuickView::SizeRootObjectToView);
    setClearBeforeRendering(true);
    setScreen(qApp->primaryScreen());
    resizeWindow();

    setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    setTitle(tr("Launcher"));
    setVisible(false);

    connect(qApp->primaryScreen(), &QScreen::virtualGeometryChanged, this, &Launcher::resizeWindow, Qt::QueuedConnection);
    connect(qApp->primaryScreen(), &QScreen::geometryChanged, this, &Launcher::resizeWindow, Qt::QueuedConnection);
    connect(qApp->primaryScreen(), &QScreen::availableGeometryChanged, this, &Launcher::onAvailableGeometryChanged, Qt::QueuedConnection);

    connect(this, &QQuickView::activeChanged, this, &Launcher::onActiveChanged);
}

void Launcher::show()
{
    setVisible(true);
}

void Launcher::hide()
{
    setVisible(false);
}

void Launcher::toggle()
{
    isVisible() ? hide() : show();
}

int Launcher::screenAvailableWidth()
{
    return m_screenAvailableWidth;
}

int Launcher::screenAvailableHeight()
{
    return m_screenAvailableHeight;
}

void Launcher::showEvent(QShowEvent *e)
{
    KWindowSystem::setState(winId(), NET::SkipTaskbar | NET::SkipPager);

    QQuickView::showEvent(e);
}

void Launcher::resizeWindow()
{
    QRect geometry = qApp->primaryScreen()->geometry();
    setGeometry(geometry);
}

void Launcher::onActiveChanged()
{
    if (!isActive())
        Launcher::hide();
}

void Launcher::onAvailableGeometryChanged(const QRect &geometry)
{
    if (geometry.width() != m_screenAvailableWidth) {
        m_screenAvailableWidth = geometry.width();
        emit screenAvailableWidthChanged();
    }

    if (geometry.height() != m_screenAvailableHeight) {
        m_screenAvailableHeight = geometry.height();
        emit screenAvailableHeightChanged();
    }
}
