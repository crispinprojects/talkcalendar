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
#include "calendarevent.h"
#include "synthesizer.h"

#define PROJECT_VERSION "0.6.0"

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

private:
    Ui::MainWindow *ui;
    Synthesizer *m_synthesizer;
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
    bool m_talk_location;
    bool m_upcoming;
    int m_upcoming_days;
    QColor m_eventColor;
    QColor m_priorityColor;

};
#endif // MAINWINDOW_H
