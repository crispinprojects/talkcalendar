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
