/*
 *
 * Copyright 2025 Alan Crispin <crispinalan@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GNU Lesser General Public License v2.1
 */
#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    // GNOME font scaling (Qt 6.4+)
    // This tells Qt to respect the system scale precisely
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication a(argc, argv);

    // Set Global Identity - use these strings exactly everywhere
    a.setOrganizationName("TalkCalendarProject");
    a.setApplicationName("TalkCalendar");

    // Link to desktop file for Wayland/GNOME icon
    QGuiApplication::setDesktopFileName("talkcalendar");

    MainWindow w;
    w.show();
    return a.exec();
}
