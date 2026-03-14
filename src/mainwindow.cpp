/*
 * mainWindow.cpp
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
#include "./ui_mainwindow.h"
#include "configdialog.h"
#include "easterdialog.h"
#include "eventeditordialog.h"
#include "searchdialog.h"
#include <QMessageBox>
#include <QSqlError>
#include <QFileDialog>
#include <QTextStream>
#include <QTimeZone>

/**
 * @brief MainWindow constructor.
 * @param parent The parent widget (default nullptr).
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup Database Connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/calendar.db";
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Database Error:" << db.lastError().text();
    } else {
        initDatabase();
    }

    // Setup synthesizer
    m_diphone = new Diphone();
    m_engine = new Synthesizer(this);
    m_voiceDict = new Dictionary(this);
    //m_tempo=1.7f;
    m_tempo=17;



    // Initial UI State
    ui->btnDelete->setEnabled(false);
    ui->btnEditEvent->setEnabled(false);

    qRegisterMetaType<CalendarEvent>("CalendarEvent");

    // Connections
    connect(ui->eventList, &QListWidget::itemSelectionChanged, this, [this]() {
        bool hasSelection = (ui->eventList->selectedItems().count() > 0);
        ui->btnDelete->setEnabled(hasSelection);
        ui->btnEditEvent->setEnabled(hasSelection);
    });

    connect(ui->mainCalendar, &QCalendarWidget::clicked, this, &MainWindow::onDateClicked);
    //connect(ui->mainCalendar, &QCalendarWidget::clicked, this, &MainWindow::onDateClicked);
    connect(ui->eventList, &QListWidget::itemDoubleClicked, this, &MainWindow::handleEventDoubleClicked);
    connect(ui->eventList, &QListWidget::itemClicked, this, &MainWindow::onEventClicked);
    connect(ui->mainCalendar, &QCalendarWidget::currentPageChanged, this, &MainWindow::onCalendarPageChanged);

    // Shortcuts
    new QShortcut(QKeySequence(Qt::Key_Home), this, SLOT(goToToday()));
    // Shortcut for the 'T' key
    new QShortcut(QKeySequence(Qt::Key_T), this, SLOT(talkCurrentTime()));

    // Spacebar Shortcut to use onDateClicked:
    QShortcut *spaceShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    connect(spaceShortcut, &QShortcut::activated, this, [this]() {
        onDateClicked(ui->mainCalendar->selectedDate()); // Change this from onDateSelected
    });

    QSettings settings; //automatically uses organization and app name from main.cpp
    m_talk = settings.value("talk", true).toBool(); // 'true' is the default if not found
    m_talk_startup = settings.value("talk_startup", true).toBool();

    m_upcoming = settings.value("upcoming", true).toBool();
    m_upcoming_days = settings.value("upcoming_days", 3).toInt();
    m_tempo = settings.value("tempo", 17).toInt();
    m_font_size = settings.value("font_size", 14).toInt();

    m_window_x=settings.value("window_x",0).toInt();
    m_window_y=settings.value("window_y",0).toInt();
    m_window_width=settings.value("window_width",640).toInt();
    m_window_height=settings.value("window_height",480).toInt();

    // qDebug() << "Constructor" << m_window_width << "x" << m_window_height
    //          << "Position: (" << m_window_x << ", " << m_window_y << ")";

    resize(m_window_width, m_window_height);
    move(m_window_x, m_window_y);


    // load the colours. If they don't exist yet, use defaults.
    m_eventColor = QColor(settings.value("colors/event", "#ffff00").toString()); // Default Yellow
    m_priorityColor = QColor(settings.value("colors/priority", "#9370db").toString()); // Default Purple


    // Commonly recommended font families for Qt6 C++ applications
    // include "Helvetica," "Arial," and "Times New Roman," as they are widely supported
    // and provide good readability.
    // Using system fonts can ensure better compatibility across different platforms.

    QFont defaultFont = QApplication::font();
    //qDebug() << "Default Font:" << defaultFont.family() << "Size:" << defaultFont.pointSize();


    // Set the global font for the application
    //QFont appFont("Arial", m_font_size); // Specify font family and size
    QFont appFont(defaultFont.family(), m_font_size); // Specify font family and size
    QApplication::setFont(appFont);
    ui->mainCalendar->setFont(appFont);
    ui->eventList->setFont(appFont);

    //  Startup Actions
    QDate today = QDate::currentDate();
    ui->mainCalendar->setSelectedDate(today);
    updateCalendarHighlights(); //

    QList<CalendarEvent> events = getEventsForDate(today); //
    updateEventListUI(events); //populate the list view visually WITHOUT speaking

    if (m_talk && m_talk_startup) {
        QString welcome = "Talk Calendar ";

        QString datePhrase = m_voiceDict->getDatePhrase(today)+ " ";
        welcome.append(datePhrase);
        // Add Today's Events
        if (!events.isEmpty()) {

            for (const CalendarEvent &ev : events) {
                // time phrase
                QString timePhrase = m_voiceDict->getTimePhrase(ev.m_startHour, ev.m_startMin, ev.m_isAllDay)+ " ";
                if (ev.m_isAllDay) {
                    welcome.append(ev.m_summary);
                    welcome.append(" ");
                } else {
                    welcome.append(ev.m_summary);
                    welcome.append(" ");
                    welcome.append(timePhrase);
                    welcome.append(" ");
                }
            }

        } else
        {
            //welcome.append("No events ");
            welcome.append(" ");
        }

        // Add Upcoming Events
        welcome += getUpcomingEventsPhrase();
        //qDebug()<<"welcome = "<<welcome;
        m_engine->speak(welcome,m_voiceDict,static_cast<float>(m_tempo) / 10.0f);


    }

}

/**
 * @brief MainWindow destructor.
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief Creates the events table if it does not already exist.
 */
void MainWindow::initDatabase() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS events ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "summary TEXT, "
               "location TEXT, "
               "description TEXT, "
               "start_year INTEGER, start_month INTEGER, start_day INTEGER, "
               "start_hour INTEGER, start_min INTEGER, "
               "end_year INTEGER, end_month INTEGER, end_day INTEGER, "
               "end_hour INTEGER, end_min INTEGER, "
               "is_allday INTEGER DEFAULT 0, "
               "is_priority INTEGER DEFAULT 0, "
               "recurrence_type INTEGER DEFAULT 0" // 0:None, 1:Daily, 2:Weekly, 3:Monthly, 4:Yearly
               ");");
}

/**
 * @brief Updates the event list widget with the provided events.
 * @param events List of CalendarEvent objects to display.
 */
void MainWindow::updateEventListUI(const QList<CalendarEvent> &events) {
    ui->eventList->clear();
    for (const CalendarEvent &e : events) {
        // Construct the date string from the EVENT'S data, not the calendar's state
        QString dateStr = QString("%1/%2/%3")
                              .arg(e.m_startDay, 2, 10, QChar('0'))
                              .arg(e.m_startMonth, 2, 10, QChar('0'))
                              .arg(e.m_startYear);

        QString timeStr = (e.m_isAllDay == 1) ? "All Day" :
                              QString("%1:%2").arg(e.m_startHour, 2, 10, QChar('0'))
                                  .arg(e.m_startMin, 2, 10, QChar('0'));

        //qDebug()<<"updateEventListUI: summary = "<<  e.m_summary;
        // BUILD THE FULL STRING: Date + Time + Summary + Description+ Location
        QString displayText = QString("%1 | %2 | %3").arg(dateStr, timeStr, e.m_summary);


        // Add  description if it exists
        if (!e.m_description.isEmpty()) {
            //qDebug()<<"updateEventListUI: description = "<<  e.m_description;
            displayText += ", " + e.m_description;
        }

        if (!e.m_location.isEmpty()) {
            //qDebug<<"updateEventListUI: location = "<<  e.m_location;
            displayText += ", " + e.m_location ;

        }

        QListWidgetItem *item = new QListWidgetItem(displayText, ui->eventList);
        item->setData(Qt::UserRole, e.m_id); // This is vital for clicking/editing later
    }
}

/**
 * @brief Highlights dates on the calendar that have events.
 */
void MainWindow::updateCalendarHighlights() {
    ui->mainCalendar->setDateTextFormat(QDate(), QTextCharFormat());

    int month = ui->mainCalendar->monthShown();
    int year = ui->mainCalendar->yearShown();

    QSqlQuery query;
    // match the month AND (either match the year OR it's a yearly recurrence)
    query.prepare("SELECT start_day, is_priority FROM events "
                  "WHERE start_month = :m "
                  "AND (start_year = :y OR recurrence_type = 4)");
    query.bindValue(":m", month);
    query.bindValue(":y", year);

    QTextCharFormat standardFormat;
    standardFormat.setFontWeight(QFont::Bold);
    standardFormat.setForeground(Qt::black); // Set text to black for better contrast on light colors
    standardFormat.setBackground(m_eventColor); // <-- USE VARIABLE

    QTextCharFormat priorityFormat;
    priorityFormat.setFontWeight(QFont::Bold);
    priorityFormat.setForeground(Qt::white);
    priorityFormat.setBackground(m_priorityColor); // <-- USE VARIABLE

    if (query.exec()) {
        while (query.next()) {
            int day = query.value(0).toInt();
            int isPriority = query.value(1).toInt();

            QDate date(year, month, day);

            if (isPriority == 1) {
                ui->mainCalendar->setDateTextFormat(date, priorityFormat);
            } else {
                ui->mainCalendar->setDateTextFormat(date, standardFormat);
            }
        }
    }
}

/**
 * @brief Loads all events for a given date from the database.
 * @param date The QDate to query events for.
 * @return List of CalendarEvent objects.
 */
QList<CalendarEvent> MainWindow::loadEventsForDate(const QDate &date) {
    QList<CalendarEvent> events;
    QSqlQuery query;

    query.prepare("SELECT * FROM events WHERE (start_day = :d AND start_month = :m) "
                  "AND (start_year = :y OR recurrence_type = 4)");
    query.bindValue(":d", date.day());
    query.bindValue(":m", date.month());
    query.bindValue(":y", date.year());

    if (query.exec()) {
        while (query.next()) {
            int recType = query.value("recurrence_type").toInt();

            // passing EXACTLY 17 arguments now to match event.h
            events.append(CalendarEvent(
                query.value("id").toInt(),             // 1
                query.value("summary").toString(),     // 2
                query.value("location").toString(),    // 3
                query.value("description").toString(), // 4
                query.value("start_year").toInt(),     // 5
                query.value("start_month").toInt(),    // 6
                query.value("start_day").toInt(),      // 7
                query.value("start_hour").toInt(),     // 8
                query.value("start_min").toInt(),      // 9
                query.value("end_year").toInt(),       //10
                query.value("end_month").toInt(),      //11
                query.value("end_day").toInt(),        //12
                query.value("end_hour").toInt(),       //13
                query.value("end_min").toInt(),        //14
                recType,                               //15 (recurrenceType)
                query.value("is_allday").toInt(),      //16
                query.value("is_priority").toInt()     //17
                // NO MORE REMINDER ARGUMENTS HERE
                ));
        }
    }
    return events;
}

/**
 * @brief Handles a click on a date in the calendar widget.
 * @param date The QDate that was clicked.
 */
void MainWindow::onDateClicked(const QDate &date) {

    QList<CalendarEvent> events = getEventsForDate(date);
    updateEventListUI(events);
    if (m_talk) {
        QString phrase = m_voiceDict->getDatePhrase(date)+ " ";
        for (const CalendarEvent &ev : events) {
            QString timePhrase = m_voiceDict->getTimePhrase(ev.m_startHour, ev.m_startMin, ev.m_isAllDay)+ " ";
            if (ev.m_isAllDay) {
                phrase.append(ev.m_summary);
                phrase.append(" ");
            } else {
                phrase.append(timePhrase);
                phrase.append(" ");
                phrase.append(ev.m_summary);
                phrase.append(" ");
            }           
        }

         m_engine->speak(phrase,m_voiceDict,static_cast<float>(m_tempo) / 10.0f);


    }
}

/**
 * @brief Parses an iCalendar date string into a ParsedDate structure.
 * @param icalStr The iCal date string to parse.
 * @return ParsedDate containing year, month, day, hour, minute and validity flag.
 */
ParsedDate MainWindow::parseICalDate(const QString &icalStr) {
    ParsedDate result;
    QString cleanStr = icalStr.section(';', 0, 0).trimmed();
    QDateTime dt;

    if (cleanStr.contains('T')) {
        //look for YYYYMMDDTHHMM (at least 12 chars)
        dt = QDateTime::fromString(cleanStr.left(13), "yyyyMMddTHHmm");
    } else {
        dt = QDateTime::fromString(cleanStr.left(8), "yyyyMMdd");
        result.hour = 0;
        result.minute = 0;
    }

    if (dt.isValid()) {
        result.year = dt.date().year();
        result.month = dt.date().month();
        result.day = dt.date().day();
        if (cleanStr.contains('T')) {
            result.hour = dt.time().hour();
            result.minute = dt.time().minute();
        }
        result.isValid = true;
    } else {
        qDebug() << "Parser failed for string:" << icalStr;
    }
    return result;
}

/**
 * @brief Imports events from an iCalendar (.ics/.ical) file into the database.
 */
void MainWindow::on_actionImport_iCal_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Import iCal", "", "iCalendar Files (*.ics *.ical);;All Files (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream inStream(&file);
    bool inEvent = false;
    QString summary, dtStart, description, location;
    int isPriority = 0, recurrenceType = 0;

    while (!inStream.atEnd()) {
        QString line = inStream.readLine().trimmed();
        if (line.startsWith("BEGIN:VEVENT")) {
            inEvent = true;
            summary = "No Summary"; dtStart = ""; description = ""; location = "";
            isPriority = 0; recurrenceType = 0;
        } else if (line.startsWith("END:VEVENT")) {
            inEvent = false;
            ParsedDate start = parseICalDate(dtStart);
            if (start.isValid) {
                QSqlQuery query;
                // Updated Query: Using recurrence_type and ensuring columns match initDatabase()
                query.prepare("INSERT INTO events (summary, location, description, "
                              "start_year, start_month, start_day, start_hour, start_min, "
                              "is_allday, is_priority, recurrence_type) "
                              "VALUES (:s, :l, :desc, :y, :m, :d, :h, :min, :allday, :pri, :rec)");

                query.bindValue(":s", summary);
                query.bindValue(":l", location);
                query.bindValue(":desc", description);
                query.bindValue(":y", start.year);
                query.bindValue(":m", start.month);
                query.bindValue(":d", start.day);
                query.bindValue(":h", start.hour);
                query.bindValue(":min", start.minute);
                query.bindValue(":allday", dtStart.contains('T') ? 0 : 1);
                query.bindValue(":pri", isPriority);
                query.bindValue(":rec", recurrenceType); // This will be 4 for yearly, 0 for none

                if (!query.exec()) {
                    qDebug() << "Import Insert Error:" << query.lastError().text();
                }
            }
        } else if (inEvent) {
            QString value = line.mid(line.indexOf(':') + 1);

            if (line.startsWith("SUMMARY:")) {
                summary = value;
            }
            else if (line.startsWith("DTSTART")) {
                dtStart = value;
            }
            else if (line.startsWith("RRULE") && line.contains("FREQ=YEARLY")) {
                recurrenceType = 4; // Use our new integer code for Yearly
            }
            else if (line.startsWith("PRIORITY:")) {
                int pVal = value.toInt();
                isPriority = (pVal > 0 && pVal < 4) ? 1 : 0;
            }
            else if (line.startsWith("LOCATION:")) {
                location = value;
            }
            else if (line.startsWith("DESCRIPTION:")) {
                description = value;
            }
        }
    }
    file.close();
    updateCalendarHighlights();
    onDateClicked(ui->mainCalendar->selectedDate());
}

/**
 * @brief Exports all events from the database to an iCalendar (.ics/.ical) file.
 */
void MainWindow::on_actionExport_iCal_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export iCal", "", "iCalendar Files (*.ics *.ical)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    out << "BEGIN:VCALENDAR\nVERSION:2.0\nPRODID:-//TalkCalendar//Qt6//EN\n";

    QSqlQuery query("SELECT * FROM events");
    while (query.next()) {
        out << "BEGIN:VEVENT\n";
        out << "SUMMARY:" << query.value("summary").toString() << "\n";

        // Handle DTSTART based on All Day status
        if (query.value("is_allday").toInt() == 1) {
            out << "DTSTART;VALUE=DATE:" << QString("%1%2%3")
            .arg(query.value("start_year").toInt(), 4, 10, QChar('0'))
                    .arg(query.value("start_month").toInt(), 2, 10, QChar('0'))
                    .arg(query.value("start_day").toInt(), 2, 10, QChar('0')) << "\n";
        } else {
            out << "DTSTART:" << QString("%1%2%3T%4%500")
            .arg(query.value("start_year").toInt(), 4, 10, QChar('0'))
                    .arg(query.value("start_month").toInt(), 2, 10, QChar('0'))
                    .arg(query.value("start_day").toInt(), 2, 10, QChar('0'))
                    .arg(query.value("start_hour").toInt(), 2, 10, QChar('0'))
                    .arg(query.value("start_min").toInt(), 2, 10, QChar('0')) << "\n";
        }

        // check recurrence_type
        int recType = query.value("recurrence_type").toInt();
        if (recType == 4) { // 4 is internal code for Yearly
            out << "RRULE:FREQ=YEARLY\n";
        }

        // Handle Priority
        if (query.value("is_priority").toInt() == 1) {
            out << "PRIORITY:1\n";
        }

        out << "LOCATION:" << query.value("location").toString() << "\n";
        out << "DESCRIPTION:" << query.value("description").toString() << "\n";
        out << "END:VEVENT\n";
    }

    out << "END:VCALENDAR\n";
    file.close();

    QMessageBox::information(this, "Export", "Calendar exported successfully.");
}

/**
 * @brief Slot invoked when the 'New Event' button is clicked.
 */
void MainWindow::on_btnNewEvent_clicked() {
    QDate selectedDate = ui->mainCalendar->selectedDate();
    EventEditorDialog dialog(selectedDate, nullptr, this);

    if (dialog.exec() == QDialog::Accepted) {
        onDateClicked(selectedDate);
        updateCalendarHighlights(); // refresh calendar highlights after adding
    }
}

/**
 * @brief Slot invoked when the 'Delete' button is clicked.
 */
void MainWindow::on_btnDelete_clicked() {
    QListWidgetItem *item = ui->eventList->currentItem();
    if (!item) return;

    if (QMessageBox::question(this, "Confirm Delete", "Are you sure?") == QMessageBox::Yes) {
        int eventId = item->data(Qt::UserRole).toInt();
        QSqlQuery query;
        query.prepare("DELETE FROM events WHERE id = :id");
        query.bindValue(":id", eventId);

        if (query.exec()) {
            onDateClicked(ui->mainCalendar->selectedDate());
            updateCalendarHighlights(); // Refresh the dots after deleting
        }
    }
}

/**
 * @brief Helper that opens the editor for the currently selected event.
 */
void MainWindow::editSelectedEvent() {
    QListWidgetItem *item = ui->eventList->currentItem();
    if (!item) return;

    int eventId = item->data(Qt::UserRole).toInt();
    CalendarEvent selectedEvent = getEventById(eventId);

    EventEditorDialog dialog(ui->mainCalendar->selectedDate(), &selectedEvent, this);
    if (dialog.exec() == QDialog::Accepted) {
        onDateClicked(ui->mainCalendar->selectedDate());
        updateCalendarHighlights();
    }
}

/**
 * @brief Slot invoked when the 'Edit Event' button is clicked.
 */
void MainWindow::on_btnEditEvent_clicked() {
    editSelectedEvent();
}

/**
 * @brief Handles a double click on an event list item by opening the editor.
 * @param item The QListWidgetItem that was double‑clicked.
 */
void MainWindow::handleEventDoubleClicked(QListWidgetItem *item) {
    Q_UNUSED(item);
    editSelectedEvent();
}

/**
 * @brief Slot invoked when the 'Clear All' button is clicked.
 */
void MainWindow::on_btnClearAll_clicked() {
    // confirmation Dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "DANGER ZONE: Database",
                                 "This will permanently delete ALL events. Are you sure?",
                                 QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        if (query.exec("DELETE FROM events")) {
            onDateClicked(ui->mainCalendar->selectedDate());
            updateCalendarHighlights(); // Refresh highlights after deleting
            QMessageBox::information(this, "Success", "Database cleared.");
        } else {
            qDebug() << "Delete All Error:" << query.lastError().text();
        }
    }
}

/**
 * @brief Goes to today's date in the calendar.
 */
void MainWindow::goToToday() {
    ui->mainCalendar->setSelectedDate(QDate::currentDate());
    // Trigger the update for the event list below the calendar
    onDateClicked(QDate::currentDate());
}

/**
 * @brief Clears the event list and updates highlights when the calendar page changes.
 */
void MainWindow::onCalendarPageChanged() {
    ui->eventList->clear();
    updateCalendarHighlights(); // Refresh the dots for the new month
}

/**
 * @brief Slot invoked when an event list item is clicked to speak its details.
 * @param item The QListWidgetItem that was clicked.
 */
void MainWindow::onEventClicked(QListWidgetItem *item) {
    if (!item) return;

    int eventId = item->data(Qt::UserRole).toInt();
    CalendarEvent ev = getEventById(eventId);

    // build sentence
    QString timePhrase = m_voiceDict->getTimePhrase(ev.m_startHour, ev.m_startMin, ev.m_isAllDay)+ " ";
    QString fullSentence="";
    fullSentence.append(timePhrase);
    fullSentence.append(" ");
    fullSentence.append(ev.m_summary);
    fullSentence.append(" ");
    m_engine->speak(fullSentence,m_voiceDict,static_cast<float>(m_tempo) / 10.0f);


}

/**
 * @brief Retrieves all events for a given date.
 * @param date The QDate to query.
 * @return List of CalendarEvent objects matching the date.
 */
QList<CalendarEvent> MainWindow::getEventsForDate(const QDate &date) {
    QList<CalendarEvent> events;
    QSqlQuery query;

    //SELECT statement
    QString sql = "SELECT id, summary, location, description, "
                  "start_year, start_month, start_day, start_hour, start_min, "
                  "is_allday, is_priority, recurrence_type "
                  "FROM events "
                  "WHERE start_day = ? AND start_month = ? "
                  "AND (start_year = ? OR recurrence_type = 4) "
                  "ORDER BY is_allday DESC, start_hour ASC, start_min ASC";

    if (!query.prepare(sql)) return events;

    query.addBindValue(date.day());
    query.addBindValue(date.month());
    query.addBindValue(date.year());

    if (query.exec()) {
        while (query.next()) {
            // Now these values will actually exist!
            CalendarEvent ev(
                query.value("id").toInt(),
                query.value("summary").toString(),
                query.value("location").toString(),
                query.value("description").toString(),
                query.value("start_year").toInt(),
                query.value("start_month").toInt(),
                query.value("start_day").toInt(),
                query.value("start_hour").toInt(),
                query.value("start_min").toInt(),
                0,0,0,0,0, // end times (placeholders)
                query.value("recurrence_type").toInt(),
                query.value("is_allday").toInt(),
                query.value("is_priority").toInt()
                );
            events.append(ev);
        }
    }
    return events;
}

/**
 * @brief Retrieves a single event by its database ID.
 * @param id The event's unique identifier.
 * @return CalendarEvent object, or an empty one if not found.
 */
CalendarEvent MainWindow::getEventById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM events WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        int recType = query.value("recurrence_type").toInt();

        return CalendarEvent(
            query.value("id").toInt(),
            query.value("summary").toString(),
            query.value("location").toString(),
            query.value("description").toString(),
            query.value("start_year").toInt(),
            query.value("start_month").toInt(),
            query.value("start_day").toInt(),
            query.value("start_hour").toInt(),
            query.value("start_min").toInt(),
            query.value("end_year").toInt(),
            query.value("end_month").toInt(),
            query.value("end_day").toInt(),
            query.value("end_hour").toInt(),
            query.value("end_min").toInt(),
            recType, // Mapping  recurrence_type integer
            query.value("is_allday").toInt(),
            query.value("is_priority").toInt()
            );
    }
    return CalendarEvent(); // Return an empty event if not found
}

/**
 * @brief Slot invoked when the Preferences action is triggered.
 */
void MainWindow::on_actionPreferences_triggered()
{
    // pass existing member variables (m_eventColor, m_priorityColor) to the dialog
    ConfigDialog dialog(m_talk, m_talk_startup, m_upcoming, m_upcoming_days, m_tempo, m_font_size,
                        m_eventColor, m_priorityColor, this);

    if (dialog.exec() == QDialog::Accepted) {
        m_talk = dialog.talkEnabled();
        m_talk_startup = dialog.startupEnabled();        
        m_upcoming = dialog.upcomingEnabled();
        m_upcoming_days = dialog.upcomingDays();
        m_font_size=dialog.fontSize();
        m_tempo = dialog.tempo();
        //m_tempo = static_cast<float>(tempo) / 10.0f;

        // Retrieve the new colors from the dialog
        m_eventColor = dialog.eventColor();
        m_priorityColor = dialog.priorityColor();

        // Save everything to QSettings
        QSettings settings; // automatically uses the names from main.cpp
        settings.setValue("talk", m_talk);
        settings.setValue("talk_startup", m_talk_startup);       
        settings.setValue("upcoming", m_upcoming);
        settings.setValue("upcoming_days", m_upcoming_days);
        settings.setValue("font_size", m_font_size);
        settings.setValue("tempo",m_tempo);


        m_eventColor = dialog.eventColor();
        m_priorityColor = dialog.priorityColor();

        //existing settings.setValue() calls
        settings.setValue("colors/event", m_eventColor.name());
        settings.setValue("colors/priority", m_priorityColor.name());

        QFont defaultFont = QApplication::font();
        // Set the global font for the application
        QFont appFont(defaultFont.family(), m_font_size); // Specify font family and size
        //QFont appFont("Arial", m_font_size); // Specify font family and size
        QApplication::setFont(appFont);
        ui->mainCalendar->setFont(appFont);
        ui->eventList->setFont(appFont);


        // refresh the calendar to show the new colors immediately
        updateCalendarHighlights();
    }
}

/**
 * @brief Builds a phrase summarising upcoming events.
 * @return A string containing information about upcoming events, or an empty string if none.
 */
QString MainWindow::getUpcomingEventsPhrase() {

    //qDebug()<<"m_upcoming = "<<m_upcoming;
    if (!m_upcoming) return ""; // Respect the config setting

    QString upcomingPhrase = "";
    QDate today = QDate::currentDate();
    QDate endDate = today.addDays(m_upcoming_days);
    int count = 0;

    QSqlQuery query;
    // This query finds:
    // 1. Regular events within the date range
    // 2. Yearly events where the (Month/Day) falls within the range
    query.prepare("SELECT summary, start_month, start_day, recurrence_type FROM events "
                  "WHERE ( "
                  "  (start_year = :y AND start_month = :m AND start_day >= :d) OR " // Remainder of this month
                  "  (start_year = :y AND start_month > :m AND start_month <= :em) OR " // Following months
                  "  (recurrence_type = 4) " // All yearly events (we filter them in the loop)
                  ") ORDER BY start_month ASC, start_day ASC");

    query.bindValue(":y", today.year());
    query.bindValue(":m", today.month());
    query.bindValue(":d", today.day());
    query.bindValue(":em", endDate.month());

    if (query.exec()) {
        while (query.next()) {
            int evMonth = query.value("start_month").toInt();
            int evDay = query.value("start_day").toInt();

            QDate evDate(today.year(), evMonth, evDay);

            // recurrence event
            if (evDate < today && query.value("recurrence_type").toInt() == 4) {
                evDate = evDate.addYears(1);
            }

            if (evDate > today && evDate <= endDate) {
                QString summary = query.value("summary").toString();
                //summary.append(" ");
                QString datePhrase = m_voiceDict->getDatePhrase(evDate);
                datePhrase.append(" ");
                upcomingPhrase += QString("%1 on %2 ").arg(summary, datePhrase);
                count++;
            }
        }
    }

    if (count > 0) {
        QString countStr =m_voiceDict->getCardinalStr(count);
        //countStr.append(" ");
        return QString("You have %1 up coming events %2").arg(countStr, upcomingPhrase);
        //return QString("You have %1 up coming events. %2").arg(QString::number(count), upcomingPhrase);
    }
    return "";
}

/**
 * @brief Extracts a CalendarEvent from the current QSqlQuery row.
 * @param query The QSqlQuery positioned at the desired record.
 * @return CalendarEvent object constructed from the row data.
 */
CalendarEvent MainWindow::getEventFromQuery(const QSqlQuery &query) {
    int recType = query.value("recurrence_type").toInt();
    return CalendarEvent(
        query.value("id").toInt(),
        query.value("summary").toString(),
        query.value("location").toString(),
        query.value("description").toString(),
        query.value("start_year").toInt(),
        query.value("start_month").toInt(),
        query.value("start_day").toInt(),
        query.value("start_hour").toInt(),
        query.value("start_min").toInt(),
        0,0,0,0,0, // end times (placeholders)
        query.value("recurrence_type").toInt(),
        query.value("is_allday").toInt(),
        query.value("is_priority").toInt()
        );
}

/**
 * @brief Performs a search for events by summary and/or location.
 * @param summarySearch Search string for the event summary (may be empty).
 * @param locationSearch Search string for the event location (may be empty).
 */
void MainWindow::performSearch(const QString &summarySearch, const QString &locationSearch) {
    QList<CalendarEvent> results;
    QSqlQuery query;

    QString sql = "SELECT * FROM events WHERE 1=1";
    if (!summarySearch.isEmpty()) sql += " AND summary LIKE :summary";
    if (!locationSearch.isEmpty()) sql += " AND location LIKE :location";
    sql += " ORDER BY start_year DESC, start_month DESC, start_day DESC";

    query.prepare(sql);
    if (!summarySearch.isEmpty()) query.bindValue(":summary", "%" + summarySearch + "%");
    if (!locationSearch.isEmpty()) query.bindValue(":location", "%" + locationSearch + "%");

    if (query.exec()) {
        while (query.next()) {
            results.append(getEventFromQuery(query));
        }
        updateEventListUI(results); // UI updater

        QString msg;
        if (results.size() == 1) {
            msg = "one  event.";
            //qDebug()<<"search speech msg = "<<msg;
        } else {
            msg = QString(" %1  events.").arg(results.size());
            //qDebug()<<"search speech msg = "<<msg;
        }

        if (results.isEmpty()) {
            msg = "no events found.";
        } else {
            QString countStr = QString::number(results.size());
            QString word = (results.size() == 1) ? "event" : "events";
            msg =" Found "+countStr + " " + word;
        }

    }
}

/**
 * @brief Slot invoked when the Search action is triggered.
 */
void MainWindow::on_actionSearch_triggered()
{
    SearchDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString summary = dialog.getSummary();
        QString location = dialog.getLocation();
        // execute search and populate the main list view (click another date to clear)
        performSearch(summary, location);
    }
}

/**
 * @brief Slot invoked when an event list item is double‑clicked during a search.
 * @param item The QListWidgetItem that was double‑clicked.
 */
void MainWindow::on_eventList_itemDoubleClicked(QListWidgetItem *item) {
    if (!item) return;
    int id = item->data(Qt::UserRole).toInt();
    CalendarEvent ev = getEventById(id); //helper that selects all columns

    if (ev.m_id != -1) {
        QDate eventDate(ev.m_startYear, ev.m_startMonth, ev.m_startDay);
        ui->mainCalendar->setSelectedDate(eventDate);

        // This ensures the list view updates to show ONLY that day's events
        // effectively "clearing" the search results view.
        onDateClicked(eventDate);
    }
}

/**
 * @brief Announces the current time via speech.
 */
void MainWindow::talkCurrentTime() {

    int hour = QTime::currentTime().hour();
    int minute = QTime::currentTime().minute();
    QString timePhrase =m_voiceDict->getTimePhrase(hour, minute, false);

    QString speakTimePhrase ="The time is ";
    speakTimePhrase.append(timePhrase);
    //qDebug()<<"speak time phrase "<<speakTimePhrase;   
    m_engine->speak(speakTimePhrase,m_voiceDict,static_cast<float>(m_tempo) / 10.0f);

}

/**
 * @brief Slot invoked when the About action is triggered.
 */
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("About Talk Calendar");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Talk Calendar is a desktop calendar with some speech capability. For more information go to the  <a href='https://github.com/crispinprojects/talkcalendar'>Talk Calendar website.</a> Alan Crispin (2026)");
    msgBox.exec();
}

/**
 * @brief Slot invoked when the Information action is triggered.
 */
void MainWindow::on_actionInformation_triggered() {
    // custom version number
    QString msg = QString("Talk Calendar Version: %1\n").arg(PROJECT_VERSION);

    // Qt version
    msg.append(QString("Qt Version: %1\n").arg(qVersion()));

    //font information
    QFont defaultFont = QApplication::font();
    //qDebug() << "Default Font:" << defaultFont.family() << "Size:" << defaultFont.pointSize();
    msg.append("System Font: ");
    msg.append(defaultFont.family());
    msg.append("\n");
    //msg.append(QString("System Font Size: %1\n").arg(defaultFont.pointSize()));

    msg.append(QString("Talk Calendar Font Size: %1\n").arg(m_font_size));


    // Show message box
    QMessageBox::information(this, "System Info", msg);
}

/**
 * @brief Slot invoked when the Exit action is triggered.
 */
void MainWindow::on_actionExit_triggered()
{
   close(); //trigger the closeEvent() method
}

void MainWindow:: closeEvent(QCloseEvent *event)
{
    // Get window geometry before closing
    QRect geometry = this->geometry();
    int width = geometry.width();
    int height = geometry.height();
    int x = geometry.x();
    int y = geometry.y();

    // qDebug() << "Window closing - Size:" << width << "x" << height
    //          << "Position: (" << x << ", " << y << ")";


    m_window_x=x;
    m_window_y=y;
    m_window_width=width;
    m_window_height=height;

    // Save window geometry to config before closing
    QSettings settings; // automatically uses the names from main.cpp
    settings.setValue("window_x", m_window_x);
    settings.setValue("window_y", m_window_y);
    settings.setValue("window_width", m_window_width);
    settings.setValue("window_height", m_window_height);


    QMainWindow::closeEvent(event);
}

/**
 * @brief Slot invoked when the Easter Calculator action is triggered.
 */
void MainWindow::on_actionEaster_Calculator_triggered()
{
    EasterDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // qDebug()<<"Easter calculator";
    }
}

void MainWindow::on_actionHome_triggered()
{
    // qDebug()<<"Goto current date";
    ui->mainCalendar->setSelectedDate(QDate::currentDate());
    onDateClicked(QDate::currentDate());
}

