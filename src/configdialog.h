
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
    explicit ConfigDialog(bool talk, bool startup, bool location, bool upcoming, int days,
                          QColor eventCol, QColor priorityCol, QWidget *parent = nullptr);
    ~ConfigDialog();

    // Getters for MainWindow to read back the results
    bool talkEnabled() const;
    bool startupEnabled() const;
    bool locationEnabled() const;
    bool upcomingEnabled() const;
    int upcomingDays() const;
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
