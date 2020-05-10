#include "showmonth.h"
#include "ui_showmonth.h"

showMonth::showMonth(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::showMonth)
{
  ui->setupUi(this);
}

showMonth::~showMonth()
{
  delete ui;
}
