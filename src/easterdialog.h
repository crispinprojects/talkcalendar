#ifndef EASTERDIALOG_H
#define EASTERDIALOG_H

#include <QDialog>

namespace Ui {
class EasterDialog;
}

class EasterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EasterDialog(QWidget *parent = nullptr);
    ~EasterDialog();

private slots:
    void on_btnCalculate_clicked();

private:
    Ui::EasterDialog *ui;
    QDate calculateEaster(int year);
};

#endif // EASTERDIALOG_H
