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

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QGuiApplication>
#include <QQuickView>

class Launcher : public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(int screenAvailableWidth READ screenAvailableWidth NOTIFY screenAvailableWidthChanged)
    Q_PROPERTY(int screenAvailableHeight READ screenAvailableHeight NOTIFY screenAvailableHeightChanged)

public:
    Launcher(QQuickView *w = nullptr);

    void show();
    void hide();
    void toggle();

    int screenAvailableWidth();
    int screenAvailableHeight();

signals:
    void screenAvailableWidthChanged();
    void screenAvailableHeightChanged();

protected:
    void showEvent(QShowEvent *e) override;

private:
    void resizeWindow();
    void onActiveChanged();

private slots:
    void onAvailableGeometryChanged(const QRect &geometry);

private:
    int m_screenAvailableWidth;
    int m_screenAvailableHeight;
};

#endif // LAUNCHER_H
