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
