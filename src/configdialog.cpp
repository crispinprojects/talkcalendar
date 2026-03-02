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
#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(bool talk, bool startup, bool espeak, bool upcoming, int days, int tempo, int fontSize,
                           QColor eventCol, QColor priorityCol, QWidget *parent)
    : QDialog(parent), ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);

    // Store the colors passed from MainWindow
    m_currentEventColor = eventCol;
    m_currentPriorityColor = priorityCol;

    // Initialize UI check boxes and spin box
    ui->checkTalk->setChecked(talk);
    ui->checkTalkStartup->setChecked(startup);
    ui->checkDispatcher->setChecked(espeak);
    ui->checkUpcoming->setChecked(upcoming);
    ui->spinUpcomingDays->setValue(days);
    ui->spinTempo->setValue(tempo);
    ui->spinFontSize->setValue(fontSize);

    // Set the initial button colors so user sees the current choice
    ui->btnEventColor->setStyleSheet(QString("background-color: %1").arg(m_currentEventColor.name()));
    ui->btnPriorityColor->setStyleSheet(QString("background-color: %1").arg(m_currentPriorityColor.name()));
}

void ConfigDialog::on_btnSave_clicked()
{
    accept(); // Just close with "Accepted" result; MainWindow will read the UI values
}

// Add getter methods
bool ConfigDialog::talkEnabled() const {
    return ui->checkTalk->isChecked();
}

bool ConfigDialog::startupEnabled() const
{ return ui->checkTalkStartup->isChecked();
}

bool ConfigDialog::espeakEnabled() const
{ return ui->checkDispatcher->isChecked();
}

bool ConfigDialog::upcomingEnabled() const {
    return ui->checkUpcoming->isChecked();
}

int ConfigDialog::upcomingDays() const {
    return ui->spinUpcomingDays->value();
}

int ConfigDialog::fontSize() const {
    return ui->spinFontSize->value();
}

int ConfigDialog::tempo() const {
    return ui->spinTempo->value();
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_btnEventColor_clicked()
{
    QColor color = QColorDialog::getColor(m_currentEventColor, this, "Select Event Color");
    if (color.isValid()) {
        m_currentEventColor = color;
        // Set the button's background to the chosen color as a preview
        ui->btnEventColor->setStyleSheet(QString("background-color: %1").arg(color.name()));
    }
}
void ConfigDialog::on_btnPriorityColor_clicked()
{
    QColor color = QColorDialog::getColor(m_currentPriorityColor, this, "Select Priority Color");
    if (color.isValid()) {
        m_currentPriorityColor = color;
        // Set the button's background to the chosen color as a preview
        ui->btnPriorityColor->setStyleSheet(QString("background-color: %1").arg(color.name()));
    }
}


void ConfigDialog::on_btnReset_clicked()
{
    // Define original defaults
    m_currentEventColor = QColor("#ffff00");    // Yellow
    m_currentPriorityColor = QColor("#9370db"); // Purple

    // Update the button previews
    ui->btnEventColor->setStyleSheet(QString("background-color: %1").arg(m_currentEventColor.name()));
    ui->btnPriorityColor->setStyleSheet(QString("background-color: %1").arg(m_currentPriorityColor.name()));

    // Optional: Reset other settings too
    ui->checkTalk->setChecked(true);
    ui->checkTalkStartup->setChecked(true);
     ui->checkDispatcher->setChecked(false);
    ui->checkUpcoming->setChecked(true);
    ui->spinUpcomingDays->setValue(3);
    ui->spinTempo->setValue(17);
    ui->spinFontSize->setValue(14);
}

