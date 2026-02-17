#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

QString SearchDialog::getSummary()
{
    return ui->editSummary->text();
}

// And this:
QString SearchDialog::getLocation()
{
    return ui->editLocation->text();
}

void SearchDialog::on_btnSearch_clicked()
{
     accept();
}

