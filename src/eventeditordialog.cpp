#include "eventeditordialog.h"
#include "ui_eventeditordialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

EventEditorDialog::EventEditorDialog(const QDate &date, CalendarEvent *existingEvent, QWidget *parent)
    : QDialog(parent), ui(new Ui::EventEditorDialog), m_date(date), m_editingEvent(existingEvent)
{
    ui->setupUi(this);

    if (m_editingEvent) {
        ui->lineSummary->setText(m_editingEvent->m_summary);
        ui->lineLocation->setText(m_editingEvent->m_location);
        ui->lineDescription->setText(m_editingEvent->m_description);
        ui->timeStart->setTime(QTime(m_editingEvent->m_startHour, m_editingEvent->m_startMin));
        ui->timeEnd->setTime(QTime(m_editingEvent->m_endHour, m_editingEvent->m_endMin));
        ui->btnSave->setText("Update Event");

        ui->checkAllDay->setChecked(m_editingEvent->m_isAllDay == 1);
        ui->timeStart->setEnabled(!ui->checkAllDay->isChecked());

        //Check if recurrence is 4 (Yearly)
        ui->chkYearly->setChecked(m_editingEvent->m_recurrenceType == 4);
        ui->chkPriority->setChecked(m_editingEvent->m_isPriority == 1);
    }

    connect(ui->checkAllDay, &QCheckBox::toggled, this, [this](bool checked) {
        ui->timeStart->setEnabled(!checked);
        ui->timeEnd->setEnabled(!checked);
    });
}

EventEditorDialog::~EventEditorDialog()
{
    delete ui;
}

void EventEditorDialog::on_btnSave_clicked() {
    QString summary = ui->lineSummary->text();
    if (summary.isEmpty()) return;

    QSqlQuery query;

    // Convert Checkbox state to recurrence integer
    int recValue = ui->chkYearly->isChecked() ? 4 : 0;

    if (m_editingEvent) {

        query.prepare("UPDATE events SET summary = :summary, location = :loc, description = :des,"
                      "start_hour = :shour, start_min = :smin, end_hour = :ehour, end_min = :emin,is_allday = :allday, "
                      "recurrence_type = :rec, is_priority = :priority "
                      "WHERE id = :id");
        query.bindValue(":id", m_editingEvent->m_id);
    } else {        
        query.prepare("INSERT INTO events (summary, location, description, start_day, start_month, start_year, "
                      "start_hour, start_min, end_hour, end_min,is_allday, recurrence_type, is_priority) "
                      "VALUES (:summary, :loc, :des, :d, :m, :y, :shour, :smin, :ehour, :emin, :allday, :rec, :priority)");
        query.bindValue(":d", m_date.day());
        query.bindValue(":m", m_date.month());
        query.bindValue(":y", m_date.year());
    }

    query.bindValue(":summary", summary);
    query.bindValue(":loc", ui->lineLocation->text());
    query.bindValue(":des", ui->lineDescription->text());
    query.bindValue(":shour", ui->timeStart->time().hour());
    query.bindValue(":smin", ui->timeStart->time().minute());
    query.bindValue(":ehour", ui->timeEnd->time().hour());
    query.bindValue(":emin", ui->timeEnd->time().minute());
    query.bindValue(":allday", ui->checkAllDay->isChecked() ? 1 : 0);
    query.bindValue(":rec", recValue); // 4 for yearly, 0 for none
    query.bindValue(":priority", ui->chkPriority->isChecked() ? 1 : 0);

    if (query.exec()) {
        accept();
    } else {
        qDebug() << "Save Error:" << query.lastError().text();
    }
}

