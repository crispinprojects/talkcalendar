#include "easterdialog.h"
#include "ui_easterdialog.h"
#include <qdatetime.h>

EasterDialog::EasterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EasterDialog)
{
    ui->setupUi(this);

    // Populate years from 2000 to 3000
    for (int year = 2000; year <= 3000; ++year) {
        ui->comboBoxYear->addItem(QString::number(year));
    }
    //limits of the Gregorian Easter algorithm (usually valid from 1583 to 4099)
    // for (int y = 1583; y <= 3000; ++y) {
    //     ui->comboBoxYear->addItem(QString::number(y));
    // }

    // Set the current year as default
    int currentYear = QDate::currentDate().year();
    int index = ui->comboBoxYear->findText(QString::number(currentYear));
    if (index != -1) {
        ui->comboBoxYear->setCurrentIndex(index);
    }
}

EasterDialog::~EasterDialog()
{
    delete ui;
}

QDate EasterDialog::calculateEaster(int year)
{
    //Meeus, Jones, Butcher algorithm for Gregorian Easter

    int Yr = year;
    int a = Yr % 19;
    int b = Yr / 100;
    int c = Yr % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int L = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * L) / 451;
    int month = (h + L - 7 * m + 114) / 31;
    int day = ((h + L - 7 * m + 114) % 31) + 1;


    QDate easter(year, month, day);
    if (!easter.isValid()) {
        qDebug() << "Calculation Error for year" << year;
    }
    return easter;

}

void EasterDialog::on_btnCalculate_clicked()
{    
    // Get the year from the combo box
    int selectedYear = ui->comboBoxYear->currentText().toInt();
    // Calculate the date
    QDate easterDate = calculateEaster(selectedYear);
    // Display it in the label
    // Use long date format (e.g., "Sunday, 5 April 2026")
    QString msg = "Easter " + QString::number(selectedYear) + " is on: " +
                  easterDate.toString("dddd, d MMMM");
    ui->labelEaster->setText(msg);
}

