#ifndef SHOWMONTH_H
#define SHOWMONTH_H

#include <QDialog>

namespace Ui {
  class showMonth;
}

class showMonth : public QDialog
{
    Q_OBJECT

  public:
    explicit showMonth(QWidget *parent = nullptr);
    ~showMonth();

  private:
    Ui::showMonth *ui;
};

#endif // SHOWMONTH_H
