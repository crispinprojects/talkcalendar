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
#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QColor>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(bool talk, bool startup, bool espeak, bool upcoming, int days, int tempo,
                          QColor eventCol, QColor priorityCol, QWidget *parent = nullptr);
    ~ConfigDialog();

    // Getters for MainWindow to read back the results
    bool talkEnabled() const;
    bool startupEnabled() const;
    bool espeakEnabled() const;
    bool upcomingEnabled() const;
    int upcomingDays() const;
    int tempo() const;
    QColor eventColor() const { return m_currentEventColor; }
    QColor priorityColor() const { return m_currentPriorityColor; }

private slots:
    void on_btnSave_clicked();
    void on_btnEventColor_clicked();
    void on_btnPriorityColor_clicked();

    void on_btnReset_clicked();

private:
    Ui::ConfigDialog *ui;
    QColor m_currentEventColor;
    QColor m_currentPriorityColor;
};

#endif // CONFIGDIALOG_H
