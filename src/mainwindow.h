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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtVersion>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QTextCharFormat> // For styling the dates
#include <QBrush>          // For colors
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QList>
#include <qlistwidget.h>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTimeZone>
#include <QShortcut>
#include <QSettings>
#include <QCloseEvent>
#include "calendarevent.h"
#include "synthesizer.h"
#include "diphone.h"


#define PROJECT_VERSION "0.6.6"


struct ParsedDate {
    int year, month, day, hour, minute;
    bool isValid = false;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void initDatabase();
    void onDateClicked(const QDate &date);   
    void on_btnDelete_clicked();
    void on_btnNewEvent_clicked();
    void on_btnClearAll_clicked();
    void on_btnEditEvent_clicked();
    void handleEventDoubleClicked(QListWidgetItem *item); 
    void goToToday();
    void onCalendarPageChanged();
    void on_actionImport_iCal_triggered();
    void on_actionExport_iCal_triggered();
    void onEventClicked(QListWidgetItem *item);   
    void on_actionPreferences_triggered();
    void on_actionSearch_triggered();
    void on_eventList_itemDoubleClicked(QListWidgetItem *item);
    void talkCurrentTime();

    void on_actionAbout_triggered();
    void on_actionInformation_triggered();
    void on_actionExit_triggered();
    void on_actionEaster_Calculator_triggered();
    void on_actionHome_triggered();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;

    Diphone *m_diphone;
    Dictionary *m_voiceDict;
    Synthesizer *m_engine;



    QList<CalendarEvent> loadEventsForDate(const QDate &date);
    QList<CalendarEvent> getEventsForDate(const QDate &date);
    CalendarEvent getEventById(int id);
    void editSelectedEvent();
    void updateCalendarHighlights();
    void updateEventListUI(const QList<CalendarEvent> &events);
    ParsedDate parseICalDate(const QString &icalStr);    
    QString getUpcomingEventsPhrase();

    CalendarEvent getEventFromQuery(const QSqlQuery &query);
    void performSearch(const QString &summarySearch, const QString &locationSearch);

    //config
    bool m_talk;
    bool m_talk_startup;    
    bool m_upcoming;
    int m_upcoming_days;
    int m_tempo;

    int m_window_x;
    int m_window_y;
    int m_window_width;
    int m_window_height;

    int m_font_scale=1;

    int m_font_size;
    QColor m_eventColor;
    QColor m_priorityColor;

};
#endif // MAINWINDOW_H
