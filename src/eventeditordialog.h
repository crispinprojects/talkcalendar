#ifndef EVENTEDITORDIALOG_H
#define EVENTEDITORDIALOG_H

#include <QDialog>
#include <qdatetime.h>
#include "calendarevent.h"

namespace Ui {
class EventEditorDialog;
}

class EventEditorDialog : public QDialog
{
    Q_OBJECT

public:

    explicit EventEditorDialog(const QDate &date, CalendarEvent *existingEvent = nullptr, QWidget *parent = nullptr);
    ~EventEditorDialog();

    // The helper function
    void setTargetDate(const QDate &date) { m_selectedDate = date; }

private slots:

    void on_btnSave_clicked();

private:
    Ui::EventEditorDialog *ui;
    QDate m_date;
    CalendarEvent *m_editingEvent;
    QDate m_selectedDate;

};

#endif // EVENTEDITORDIALOG_H
